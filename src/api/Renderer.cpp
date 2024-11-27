#include "Renderer.h"

Renderer *Renderer::instance = new Renderer();

Renderer::Renderer() : viewPort{Vector2D<float>()} {}

Renderer* Renderer::getInstance() { return instance == nullptr ? instance = new Renderer() : instance; }

void Renderer::draw(Gdiplus::Graphics &graphics, Group *parent) {
	if (parent == nullptr) {
		std::cout << "Parent is NULL\n";
		return;
	}
	for (auto &shape: parent->getElements()) {
		if (shape == nullptr) { // Fail-safe, ensuring no nullptr calling
			continue;
		}
		Gdiplus::Matrix orgMatrix;
		graphics.GetTransform(&orgMatrix); // <-- save original matrix to later restore it
		applyTransformation(graphics, shape->getTransformation()); // <-- apply current transformation for current shape
		switch (shape->getTypeName()) {
			case ElementType::Rectangle: {
				drawRect(graphics, static_cast<SVGRect *>(shape)); // NOLINT(*-pro-type-static-cast-downcast)
				break;
			}
			case ElementType::Ellipse: {
				drawEllipse(graphics, static_cast<SVGEllipse *>(shape));  // NOLINT(*-pro-type-static-cast-downcast)
				break;
			}
			case ElementType::Circle: {
				drawCircle(graphics, static_cast<SVGCircle *>(shape)); // NOLINT(*-pro-type-static-cast-downcast)
				break;
			}
			case ElementType::Line: {
				drawLine(graphics, static_cast<SVGLine *>(shape)); // NOLINT(*-pro-type-static-cast-downcast)
				break;
			}
			case ElementType::Polyline: {
				drawPolyline(graphics, static_cast<SVGPolyline *>(shape)); // NOLINT(*-pro-type-static-cast-downcast)
				break;
			}
			case ElementType::Polygon: {
				drawPolygon(graphics, static_cast<SVGPolygon *>(shape)); // NOLINT(*-pro-type-static-cast-downcast)
				break;
			}
			case ElementType::Text: {
				drawText(graphics, static_cast<SVGText *>(shape)); // NOLINT(*-pro-type-static-cast-downcast)
				break;
			}
			case ElementType::Path: {
				drawPath(graphics, static_cast<SVGPath *>(shape)); // NOLINT(*-pro-type-static-cast-downcast)
				break;
			}
			case ElementType::Group: {
				draw(graphics, dynamic_cast<Group *>(shape));
				break;
			}
			default:
				break;
		}
		graphics.SetTransform(&orgMatrix); // <-- restore to original matrix
	}
}

void Renderer::setViewPort(const Vector2D<float> &_viewPort) { viewPort = _viewPort; }

Vector2D<float> Renderer::getViewPort() const { return viewPort; }

void Renderer::applyTransformation(Gdiplus::Graphics &graphics, const std::vector<std::string> &transformations) {
	// Matrix in gdiplus is the transpose of matrix in svg
	std::stringstream buffer;
	std::string cmd;
	for (const auto &transformation : transformations) {
		buffer.clear();
		buffer.str(transformation);
		buffer >> cmd;
		if (cmd == "matrix") {
			float a, b, c, d, e, f;
			buffer >> a >> b >> c >> d >> e >> f;
			Gdiplus::Matrix matrix(a, b, c, d, e, f);
			graphics.MultiplyTransform(&matrix);
		} else if (cmd == "translate") {
			float dx = 0, dy = 0;
			buffer >> dx;
			if (!(buffer >> dy)) dy = 0;
			graphics.TranslateTransform(dx, dy);
		} else if (cmd == "scale") {
			float dx = 0, dy = 0;
			buffer >> dx;
			if (!(buffer >> dy)) dy = dx;
			graphics.ScaleTransform(dx, dy);	
		} else if (cmd == "rotate") {
			float a, x = 0, y = 0;
			buffer >> a;
			if (!(buffer >> x >> y)) {
				x = 0;
				y = 0;
			}
			graphics.RotateTransform(a);
		}
	}
}

Gdiplus::Brush *Renderer::getBrush(const Gdiplus::RectF &rect, Gradient *gradient, const SVGColor &color) const {
	Gdiplus::Brush *brush = nullptr;
	if (gradient == nullptr) {
		return new Gdiplus::SolidBrush(color);
	}
	std::vector<Stop> stops = gradient->getStops();
	// TODO: Process linear and radial brush
	if (gradient->getType() == "linear") {
		auto linearGradient = static_cast<LinearGradient *>(gradient); // NOLINT(*-pro-type-static-cast-downcast)
		float *position = new float[stops.size()];
		for (int i = 0; i < stops.size(); ++i) {
			position[i] = rect.X + stops[i].getOffset() * (linearGradient.getX2()  * rect.Width);
		}
	} else if (gradient->getType() == "radial") {
		auto radialGradient = static_cast<RadialGradient *>(gradient); // NOLINT(*-pro-type-static-cast-downcast)
	}
	return brush;
}

void Renderer::drawRect(Gdiplus::Graphics &graphics, SVGRect *element) {
	if (element == nullptr) return;
	Vector2D<float> position = element->getPosition();
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	std::vector<std::string> transformations = element->getTransformation();
	
	float width = element->getWidth();
	float height = element->getHeight();
	Vector2D<float> radii = element->getRadii();

	Gdiplus::Pen pen(strokeColor, strokeWidth);
	Gdiplus::SolidBrush brush(fillColor);
	Gdiplus::GraphicsPath path;

	// Draw a color-filled Rectangle with normal corners
	if (radii.x == 0 && radii.y == 0) {
		path.AddRectangle(Gdiplus::RectF(position.x, position.y, width, height));
	} else { // <--- Rounded corner
		// Top-left corner
		path.AddArc(position.x, position.y, radii.x * 2.0f, radii.y * 2.0f, 180.0, 90.0);
		// Top-right corner
		path.AddArc(position.x + width - radii.x * 2.0f, position.y, radii.x * 2.0f, radii.y * 2.0f, 270.0, 90.0);
		// Bottom-left corner
		path.AddArc(position.x, position.y + height - radii.y * 2.0f, radii.x * 2.0f, radii.y * 2.0f, 90.0, 90.0);
		// Bottom-right corner
		path.AddArc(position.x + width - radii.x * 2.0f, position.y + height - radii.y * 2.0f, radii.x * 2.0f, radii.y * 2.0f, 0.0, 90.0);
		// Close to form the final shape
		path.CloseFigure();
	}

	graphics.FillPath(&brush, &path);
	graphics.DrawPath(&pen, &path);
}

void Renderer::drawEllipse(Gdiplus::Graphics &graphics, SVGEllipse *element) {
	if (element == nullptr) return;
	Vector2D<float> position = element->getPosition();
	Vector2D<float> radius = element->getRadii();

	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	
	std::vector<std::string> transformations = element->getTransformation();
	
	Gdiplus::Pen pen(strokeColor, strokeWidth);
	Gdiplus::SolidBrush brush(fillColor);
	Gdiplus::GraphicsPath path;

	path.AddEllipse(position.x - radius.x, position.y - radius.y, radius.x * 2.0f, radius.y * 2.0f);

	graphics.FillPath(&brush, &path);
	graphics.DrawPath(&pen, &path);
}

void Renderer::drawCircle(Gdiplus::Graphics &graphics, SVGCircle *element) {
	if (element == nullptr) return;
	Vector2D<float> radius = element->getRadii();
	radius.y = radius.x;
	element->setRadii(radius);
	drawEllipse(graphics, element);
}

void Renderer::drawLine(Gdiplus::Graphics &graphics, SVGLine *element) {
	if (element == nullptr) return;
	Vector2D<float> position = element->getPosition();
	Vector2D<float> endPosition = element->getEndPosition();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();

	Gdiplus::Pen pen(strokeColor, strokeWidth);
	graphics.DrawLine(&pen, position.x, position.y, endPosition.x, endPosition.y);
}

/** @brief Draw polyline */
void Renderer::drawPolyline(Gdiplus::Graphics &graphics, SVGPolyline *element) {
	if (element == nullptr) return;
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	std::vector<Vector2D<float>> points = element->getPoints();

	Gdiplus::SolidBrush brush(fillColor);
	Gdiplus::Pen pen(strokeColor, strokeWidth);

	// Since polyline is open-formed, cannot use DrawPolygon() function to draw
	// Draw multiple offset lines to create a filled effect (default: winding mode)
	Gdiplus::GraphicsPath path(FillRuleHelper::getGdiplusFillMode(element->getFillRule()));
	path.StartFigure();
	int last = (int) points.size() - 1;
	for (int i = 0; i < last; ++i) {
		path.AddLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
	}
	graphics.FillPath(&brush, &path);
	graphics.DrawPath(&pen, &path);
}

/** @brief Draw a polygon */
void Renderer::drawPolygon(Gdiplus::Graphics &graphics, SVGPolygon *element) {
	if (element == nullptr) return;
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	std::vector<Vector2D<float>> points = element->getPoints();

	int size = (int) points.size();
	auto pointsArr = new Gdiplus::Point[size];

	for (int i = 0; i < size; ++i)
		pointsArr[i] = points[i];

	Gdiplus::SolidBrush brush(fillColor);
	Gdiplus::Pen pen(strokeColor, strokeWidth);
	// Fill the polygon
	graphics.FillPolygon(&brush, pointsArr, size, FillRuleHelper::getGdiplusFillMode(element->getFillRule()));
	// Draw stroke
	graphics.DrawPolygon(&pen, pointsArr, size);

	delete[] pointsArr;
}

/** @brief Draw text */
void Renderer::drawText(Gdiplus::Graphics &graphics, SVGText *element) {
	if (element == nullptr) return;
	std::string data = element->getData();
	std::wstring wData(data.begin(), data.end());

	float fontSize = element->getFontSize();
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();

	Gdiplus::FontFamily fontFamily(L"Times New Roman");
	Gdiplus::Font font(&fontFamily, fontSize, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);

	Vector2D<float> position = element->getPosition();

	Gdiplus::RectF boundingBox;

	// Measure the text width
	Gdiplus::RectF layoutRect;
	graphics.MeasureString(wData.c_str(), -1, &font, layoutRect, Gdiplus::StringFormat::GenericTypographic(), &boundingBox);
	float textWidth = boundingBox.Width;
	float x = position.x;
	if (element->getTextAnchor() == TextAnchor::MIDDLE) {
		x -= textWidth / 2.0f;
	} else if (element->getTextAnchor() == TextAnchor::END) {
		x -= textWidth;
	}

	// TODO: Research to https://learn.microsoft.com/en-us/dotnet/api/system.drawing.fontfamily.getemheight?view=windowsdesktop-8.0
    //float padding = fontFamily.GetEmHeight(font.GetStyle()) / font.GetSize() / 6.0f;
	float padding = font.GetHeight(graphics.GetDpiY()) / 6.0f + 0.5f;
	position.y -= boundingBox.Height;
	position.y += padding; // GDI+ draw text with padding = 1/6 em on all sides, this however can expand to 1 em, but I don't bother to fix it :l
	boundingBox.X = x;
	boundingBox.Y = position.y + padding;
	boundingBox.Height -= padding * 2.0f;

	//Gdiplus::Pen pen({255, 0, 0, 0}, 1);
	//graphics.DrawEllipse(&pen, boundingBox.X - 1.5f, boundingBox.Y - 1.5f, 3.0f, 3.0f);
	//pen.SetColor(SVG_BLUE.alpha(200));
	//graphics.DrawEllipse(&pen, element->getPosition().x - 3.0f, element->getPosition().y - 3.0f, 6.0f, 6.0f);
	//graphics.DrawRectangle(&pen, boundingBox);
	//Gdiplus::SolidBrush solidBrush(fillColor);
	//graphics.DrawString(wData.c_str(), -1, &font, Gdiplus::PointF(x, position.y), Gdiplus::StringFormat::GenericTypographic(), &solidBrush);

	Gdiplus::GraphicsPath path;
	path.AddString(wData.c_str(), -1, &fontFamily, font.GetStyle(), font.GetSize(), Gdiplus::PointF(x, position.y), Gdiplus::StringFormat::GenericTypographic());
	Gdiplus::SolidBrush brush(fillColor);
	graphics.FillPath(&brush, &path);
	Gdiplus::Pen pen2(strokeColor, strokeWidth);
	graphics.DrawPath(&pen2, &path);
}

/** @brief Draw path */
void Renderer::drawPath(Gdiplus::Graphics &graphics, SVGPath *element) {
	if (element == nullptr) return;
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	FillRule fillRule = element->getFillRule();
	
	Gdiplus::Pen pen(strokeColor, strokeWidth);
	Gdiplus::SolidBrush brush(fillColor);

	std::vector<PathPoint *> points = element->getPoints();

	Vector2D<float> sta;
	Vector2D<float> cur;
	Gdiplus::GraphicsPath path(fillRule == FillRule::NON_ZERO ? Gdiplus::FillModeWinding : Gdiplus::FillModeAlternate);

	PathPoint* pre = nullptr;
	for (auto &point : points) {
		char ins = (char) tolower(point->getCMD());
		Vector2D<float> pos = point->getPos();
		if (ins == 'm') { // Move-to command
			bool startPath = true;
			if (pre != nullptr) {
				if (pre->getCMD() == point->getCMD()) {
					// Any subsequent coordinate pair(s) are interpreted as parameter(s) for implicit absolute L/l command(s)
					path.AddLine(cur.x, cur.y, pos.x, pos.y);
					startPath = false;
				}
			}
			cur = pos;
			// Starting point of a path
			if (startPath) {
				path.StartFigure();
				sta = pos;
			}
		} else if (ins == 'l' || ins == 'h' || ins == 'v' || ins == 'z') {
			if (ins == 'z') { // <-- Close the path by drawing a line from current point to start point
				path.CloseFigure();
				cur = sta;
			} else {
				path.AddLine(cur.x, cur.y, pos.x, pos.y); // <-- Add a line from previous point to current point
				cur = pos;
			}
		} else if (ins == 'a') { // Drawing arc
			auto *pArc = static_cast<ArcPathPoint *>(point); // NOLINT(*-pro-type-static-cast-downcast)
			Vector2D<float> radii = pArc->getRadii();
			float xRotation = pArc->getXRotation();
			bool largeArcFlag = pArc->getLargeArcFlag();
			bool sweepFlag = pArc->getSweepFlag();

			// get cos and sin rotation
			float cosRotation = cos(xRotation);
			float sinRotation = sin(xRotation);

			// applying rotation to endpoints
			float x1p = cosRotation * (cur.x - pos.x) / 2.0f + sinRotation * (cur.y - pos.y) / 2.0f;
			float y1p = -sinRotation * (cur.x - pos.x) / 2.0f + cosRotation * (cur.y - pos.y) / 2.0f;

			// calculate arc center point
			float rxSq = radii.x * radii.x;
			float rySq = radii.y * radii.y;
			float x1pSq = x1p * x1p;
			float y1pSq = y1p * y1p;

			float radicant = ((rxSq * rySq) - (rxSq * y1pSq) - (rySq * x1pSq)) / ((rxSq * y1pSq) + (rySq * x1pSq));
			radicant = radicant < 0 ? 0 : radicant;
			float cFactor = (largeArcFlag != sweepFlag ? 1.0f : -1.0f) * sqrtf(radicant);

			float cxp = cFactor * ((radii.x * y1p) / radii.y);
			float cyp = cFactor * (-(radii.y * x1p) / radii.x);

			// Convert center point back to original coordinate system
			float cx = cosRotation * cxp - sinRotation * cyp + (cur.x + pos.x) / 2.0f;
			float cy = sinRotation * cxp + cosRotation * cyp + (cur.y + pos.y) / 2.0f;

			// Calculate start and sweep angles
			float startAngle = atan2((y1p - cyp) / radii.y, (x1p - cxp) / radii.x);
			float endAngle = atan2((-y1p - cyp) / radii.y, (-x1p - cxp) / radii.x);

			float sweepAngle = endAngle - startAngle;
			if (sweepFlag && sweepAngle < 0) sweepAngle += 2.0f * 3.14159265359f;
			if (!sweepFlag && sweepAngle > 0) sweepAngle -= 2.0f * 3.14159265359f;

			startAngle = startAngle * (180.0f / 3.14159265359f);
			sweepAngle = sweepAngle * (180.0f / 3.14159265359f);

			// Define bounding rectangle
			Gdiplus::RectF rect(cx - radii.x, cy - radii.y, radii.x * 2.0f, radii.y * 2.0f);
			path.AddArc(rect, startAngle, sweepAngle);
			cur = pos;
		} else if (ins == 'q' || ins == 't') { // Drawing Quadratic Bezier Curve
			auto *pQuad = static_cast<QuadPathPoint *>(point); // NOLINT(*-pro-type-static-cast-downcast)
			Vector2D<float> cen = pQuad->getCen();
			// draw bezier curve by bezier splines:
			// research: https://groups.google.com/g/microsoft.public.win32.programmer.gdi/c/f46zo9NyIzA 
			Gdiplus::PointF curvePoints[4] = {cur, Gdiplus::PointF((cur.x + cen.x * 2.0f) / 3.0f, (cur.y + cen.y * 2.0f) / 3.0f), Gdiplus::PointF((pos.x + cen.x * 2.0f) / 3.0f, (pos.y + cen.y * 2.0f) / 3.0f), pos};
			path.AddBeziers(curvePoints, 4);
			cur = pos;
		} else if (ins == 'c' || ins == 's') { // Drawing Cubic Bezier Curve
			auto *pCubic = static_cast<CubicPathPoint *>(point); // NOLINT(*-pro-type-static-cast-downcast)
			Vector2D<float> cen1 = pCubic->getCen(0);
			Vector2D<float> cen2 = pCubic->getCen(1);
			Gdiplus::PointF curvePoints[4] = {cur, cen1, cen2, pos};
			path.AddBeziers(curvePoints, 4);
			cur = pos;
		}
		pre = point;
	}

	graphics.FillPath(&brush, &path);
	graphics.DrawPath(&pen, &path);
}
