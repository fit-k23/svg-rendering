#include "Renderer.h"

Renderer *Renderer::instance = new Renderer();

Renderer::Renderer() : viewPort{Vector2D<float>()} {}

Renderer* Renderer::getInstance() { return instance == nullptr ? instance = new Renderer() : instance; }

void Renderer::draw(Gdiplus::Graphics &graphics, const Group *parent) {
	if (parent == nullptr) {
		std::cout << "Parent is NULL\n";
		return;
	}
	for (auto &shape: parent->getElements()) {
		if (shape == nullptr) { // Fail-safe, ensuring no nullptr calling
			continue;
		}
		// shape->dbg();
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

void Renderer::applyTransformation(Gdiplus::Graphics &graphics, const vector<string> &transformations) {
	// Matrix in gdiplus is the transpose of matrix in svg
	std::stringstream buffer;
	string cmd;
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

Gdiplus::SolidBrush *Renderer::getBrush(const SVGColor &color) {
	return new Gdiplus::SolidBrush(color);
}

Gdiplus::Brush *Renderer::getBrush(Gdiplus::RectF boundingBox, Gradient *gradient, const SVGColor &color) {
	if (gradient == nullptr)
		return new Gdiplus::SolidBrush(color);

	const vector<Stop> stops = gradient->getStops();
	if (stops.size() == 1)
		return new Gdiplus::SolidBrush(stops.begin()->getStopColor());

	vector<float> offsets;
	vector<Gdiplus::Color> colors;
	int stopAmount = 0;

	if (!Application::doSRGBGradient) {
		if (stops.front().getOffset() != 0.0f) {
			offsets.push_back(0.0f);
			++stopAmount;
			colors.push_back(stops.begin()->getStopColor());
		}
		for (auto &stop : stops) {
			offsets.push_back(stop.getOffset());
			++stopAmount;
			colors.push_back(stop.getStopColor());
		}
		if (stops.back().getOffset() != 1.0f) {
			offsets.push_back(1.0f);
			++stopAmount;
			colors.push_back(stops.back().getStopColor());
		}
	}

	if (gradient->getType() == GradientType::Linear) {
		auto linearGradient = static_cast<LinearGradient *>(gradient); // NOLINT(*-pro-type-static-cast-downcast)
		if (linearGradient->getPos(0) == linearGradient->getPos(1)) {
			return new Gdiplus::SolidBrush(stops.back().getStopColor());
		}

		if (Application::doSRGBGradient) {
			return getSRGBLinearGradientBrush(boundingBox, static_cast<const LinearGradient *>(gradient));
		}

		Vector2D p1 = linearGradient->getPos(0);
		Vector2D p2 = linearGradient->getPos(1);

		Vector2D diff = p2 - p1;

		// if (diff.x != 0) {
		// 	boundingBox.X -= p1.x * boundingBox.Width;
		// 	boundingBox.Width *= diff.x;
		// }
		// if (diff.y != 0) {
		// 	boundingBox.Y -= p1.y * boundingBox.Height;
		// 	boundingBox.Height *= diff.y;
		// }

		float angle = atan2f(diff.y, diff.x);

		auto *lBrush = new Gdiplus::LinearGradientBrush(boundingBox, SVG_BLANK, SVG_BLANK, RAD2DEG(angle), false);
		lBrush->SetInterpolationColors(colors.data(), offsets.data(), stopAmount);
		return lBrush;
	}
	auto radialGradient = static_cast<RadialGradient *>(gradient); // NOLINT(*-pro-type-static-cast-downcast)
	if (Application::doSRGBGradient) {
		return getSRGBRadialGradientBrush(boundingBox, radialGradient);
	}
	Gdiplus::GraphicsPath path;
	Gdiplus::RectF pBox = boundingBox;
	// pBox.X = 0;
	// pBox.Y = 0;
	path.AddEllipse(pBox);

	auto rBrush = new Gdiplus::PathGradientBrush(&path);
	Vector2D size = {boundingBox.X + boundingBox.Width, boundingBox.Y + boundingBox.Height};
	Vector2D<float> focus = radialGradient->getFocal() * size;

	Vector2D pos = {boundingBox.X, boundingBox.Y};
	rBrush->SetCenterPoint(static_cast<Gdiplus::PointF>(focus));
	rBrush->SetInterpolationColors(colors.data(), offsets.data(), stopAmount);
	return rBrush;
}

void Renderer::drawRect(Gdiplus::Graphics &graphics, const SVGRect *element) {
	if (element == nullptr) return;
	Vector2D<float> position = element->getPosition();
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	vector<string> transformations = element->getTransformation();
	
	float width = element->getWidth();
	float height = element->getHeight();
	Vector2D<float> radii = element->getRadii();

	Gdiplus::RectF rect;
	rect.X = position.x;
	rect.Y = position.y;
	rect.Width = width;
	rect.Height = height;

	Gdiplus::Pen pen(strokeColor, strokeWidth);
	Gdiplus::Brush *strokeBrush = getBrush(rect, element->getStrokeGradient(), element->getStrokeColor());
	if (element->getStrokeGradient() != nullptr) {
		pen.SetBrush(strokeBrush);
	}

	Gdiplus::GraphicsPath path;

	// Draw a color-filled Rectangle with normal corners
	if (radii.x == 0 && radii.y == 0) {
		path.AddRectangle(Gdiplus::RectF(position.x, position.y, width, height));
	} else { // <--- Rounded corner
		path.AddArc(position.x, position.y, radii.x * 2.0f, radii.y * 2.0f, 180.0, 90.0); // top-left
		path.AddArc(position.x + width - radii.x * 2.0f, position.y, radii.x * 2.0f, radii.y * 2.0f, 270.0, 90.0); // top-right
		path.AddArc(position.x + width - radii.x * 2.0f, position.y + height - radii.y * 2.0f, radii.x * 2.0f, radii.y * 2.0f, 0.0, 90.0); // bot-right
		path.AddArc(position.x, position.y + height - radii.y * 2.0f, radii.x * 2.0f, radii.y * 2.0f, 90.0, 90.0); // bot-left
		path.CloseFigure(); // close to form a closed loop
	}
	Gdiplus::Brush *fillBrush = getBrush(rect, element->getFillGradient(), element->getFillColor());

	graphics.FillPath(fillBrush, &path);
	delete fillBrush;
	if (element->getStrokeGradient() != nullptr) {
		delete strokeBrush;
	}
	graphics.DrawPath(&pen, &path);
}

void Renderer::drawEllipse(Gdiplus::Graphics &graphics, const SVGEllipse *element) {
	if (element == nullptr) return;
	Vector2D<float> position = element->getPosition();
	Vector2D<float> radius = element->getRadii();

	SVGColor fillColor = element->getFillColor();

	Gdiplus::Pen pen(element->getStrokeColor(), element->getStrokeWidth());
	Gdiplus::RectF rect;
	rect.X = position.x - radius.x;
	rect.Y = position.y - radius.y;
	rect.Width = 2.0f * radius.x;
	rect.Height = 2.0f * radius.y;
	Gdiplus::GraphicsPath path;
	path.AddEllipse(rect);
	Gdiplus::Brush *brush = getBrush(rect, element->getFillGradient(), fillColor);
	graphics.FillPath(brush, &path);
	delete brush;
	graphics.DrawPath(&pen, &path);
}

void Renderer::drawCircle(Gdiplus::Graphics &graphics, SVGCircle *element) { drawEllipse(graphics, element); }

void Renderer::drawLine(Gdiplus::Graphics &graphics, const SVGLine *element) {
	if (element == nullptr) return;
	Vector2D<float> position = element->getPosition();
	Vector2D<float> endPosition = element->getEndPosition();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();

	Gdiplus::Pen pen(strokeColor, strokeWidth);
	graphics.DrawLine(&pen, position.x, position.y, endPosition.x, endPosition.y);
}

void Renderer::drawPolyline(Gdiplus::Graphics &graphics, const SVGPolyline *element) {
	if (element == nullptr) return;
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	vector<Vector2D<float>> points = element->getPoints();

	Gdiplus::Pen pen(strokeColor, strokeWidth);

	// Since polyline is open-formed, cannot use DrawPolygon() function to draw
	// Draw multiple offset lines to create a filled effect (default: winding mode)
	Gdiplus::GraphicsPath path(FillRuleHelper::getGdiplusFillMode(element->getFillRule()));
	path.StartFigure();
	const size_t last = points.size() - 1;
	for (size_t i = 0; i < last; ++i) {
		path.AddLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
	}
	Gdiplus::RectF boundingBox;
	path.GetBounds(&boundingBox);

	Gdiplus::Brush *brush = getBrush(boundingBox, element->getFillGradient(), fillColor);
	graphics.FillPath(brush, &path);
	delete brush;
	graphics.DrawPath(&pen, &path);
}

void Renderer::drawPolygon(Gdiplus::Graphics &graphics, const SVGPolygon *element) {
	if (element == nullptr) return;
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	vector<Vector2D<float>> points = element->getPoints();

	int size = static_cast<int>(points.size());
	auto pointsArr = new Gdiplus::Point[size];

	for (int i = 0; i < size; ++i)
		pointsArr[i] = points[i];

	Gdiplus::Pen pen(strokeColor, strokeWidth);
	Gdiplus::GraphicsPath path(FillRuleHelper::getGdiplusFillMode(element->getFillRule()));
	path.StartFigure();
	const size_t last = points.size();
	path.AddPolygon(pointsArr, size);
	path.CloseFigure();

	Gdiplus::RectF boundingBox;
	path.GetBounds(&boundingBox);

	Gdiplus::Brush *brush = getBrush(boundingBox, element->getFillGradient(), fillColor);
	graphics.FillPath(brush, &path);
	graphics.DrawPath(&pen, &path);
	delete[] pointsArr;
	delete brush;
}

void Renderer::drawText(Gdiplus::Graphics &graphics, const SVGText *element) {
	if (element == nullptr) return;
	string data = element->getData();
	std::wstring wData(data.begin(), data.end());

	float fontSize = element->getFontSize();
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();

	Gdiplus::FontFamily fontFamily(L"Times New Roman");
	int fontStyle = Gdiplus::FontStyleRegular;
	if (element->getFontStyle() == FontStyle::ITALIC) {
		fontStyle = Gdiplus::FontStyleItalic;
	}
	Gdiplus::Font font(&fontFamily, fontSize, fontStyle, Gdiplus::UnitPixel);
	Vector2D<float> position = element->getPosition();
	Gdiplus::RectF boundingBox;
	// Measure the text width
	Gdiplus::RectF layoutRect;
	graphics.MeasureString(wData.c_str(), -1, &font, layoutRect, Gdiplus::StringFormat::GenericTypographic(), &boundingBox);
//	graphics.MeasureString(wData.c_str(), -1, &font, layoutRect, Gdiplus::StringFormat::GenericDefault(), &boundingBox);

	float textWidth = boundingBox.Width;
	if (element->getTextAnchor() == TextAnchor::MIDDLE) {
		position.x -= textWidth / 2.0f;
	} else if (element->getTextAnchor() == TextAnchor::END) {
		position.x -= textWidth;
	}

	// TODO: Research to https://learn.microsoft.com/en-us/dotnet/api/system.drawing.fontfamily.getemheight?view=windowsdesktop-8.0
	// float padding = fontFamily.GetEmHeight(font.GetStyle()) / font.GetSize() / 6.0f + 1.0f;
	float bHeight = font.GetHeight(graphics.GetDpiY());
	float padding = bHeight / 6.0f + 0.5f;

	position.y -= bHeight - padding - 1; // GDI+ draw text with padding = 1/6 em on all sides, this however can expand to 1 em, but I don't bother or even know to fix it :l
	boundingBox.Height = bHeight;
	boundingBox.X = position.x;
	boundingBox.Y = position.y;

	Gdiplus::Pen pen({255, 0, 0, 0}, 1.0 / Camera::zoom);
	graphics.DrawRectangle(&pen, boundingBox);

	Gdiplus::GraphicsPath path;
	path.AddString(wData.c_str(), -1, &fontFamily, font.GetStyle(), font.GetSize(), static_cast<Gdiplus::PointF>(position), Gdiplus::StringFormat::GenericTypographic());

	Gdiplus::Brush *brush = getBrush(boundingBox, element->getFillGradient(), element->getFillColor());
	graphics.FillPath(brush, &path);
	delete brush;
	Gdiplus::Pen pen2(strokeColor, strokeWidth);
	graphics.DrawPath(&pen2, &path);
}

void Renderer::drawPath(Gdiplus::Graphics &graphics, const SVGPath *element) {
	if (element == nullptr) return;
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	FillRule fillRule = element->getFillRule();

	Gdiplus::Pen pen(strokeColor, strokeWidth);

	vector<PathPoint *> points = element->getPoints();

	Vector2D<float> start;
	Vector2D<float> cur;
	Gdiplus::GraphicsPath path(fillRule == FillRule::NON_ZERO ? Gdiplus::FillModeWinding : Gdiplus::FillModeAlternate);

	const PathPoint *pre = nullptr;
	for (const auto &point : points) {
		const char ins = static_cast<char>(tolower(point->getCMD()));
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
				start = pos;
				// std::cout << "Start a path at point (" << pos.x << ", " << pos.y << ")\n";
			}
		} else if (ins == 'l' || ins == 'h' || ins == 'v' || ins == 'z') {
			if (ins == 'z') { // <-- Close the path by drawing a line from current point to start point
				path.CloseFigure();
				cur = start;
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

	Gdiplus::RectF boundingBox;
	path.GetBounds(&boundingBox);
	Gdiplus::Brush *brush = getBrush(boundingBox, element->getFillGradient(), fillColor);
	graphics.FillPath(brush, &path);
	graphics.DrawPath(&pen, &path);
	delete brush;
}

void Renderer::configGraphic(Gdiplus::Graphics &graphics) {
	graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	// graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias8x8);
	graphics.SetTextContrast(100);
	graphics.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
	graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
	graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQuality);
}

void Renderer::configCamera(Gdiplus::Graphics &graphics) {
	graphics.TranslateTransform(Camera::startPosition.x, Camera::startPosition.y);
	graphics.TranslateTransform(Camera::mousePosition.x, Camera::mousePosition.y);
	graphics.ScaleTransform(Camera::zoom, Camera::zoom);
	graphics.RotateTransform(Camera::rotation);
	// graphics.TranslateTransform(-Camera::mousePosition.x, -Camera::mousePosition.y);
	graphics.TranslateTransform(-Camera::mousePosition.x, -Camera::mousePosition.y);
}

sRGBLinearGradientBrush *Renderer::getSRGBLinearGradientBrush(Gdiplus::RectF boundingBox, const LinearGradient *gradient) {
	return new sRGBLinearGradientBrush(sRGBLinearGradientBrushHelper::createBitmap(boundingBox, gradient));
}

sRGBRadialGradientBrush *Renderer::getSRGBRadialGradientBrush(Gdiplus::RectF boundingBox, const RadialGradient *gradient) {
	return new sRGBRadialGradientBrush(sRGBRadialGradientBrushHelper::createBitmap(boundingBox, gradient));
}
