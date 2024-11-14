#include "Renderer.h"

/** @brief Default constructor */
Renderer::Renderer() : screenSize{}, viewPort{Vector2D < float > {}} {
	shapes.clear();
}

/**
 * @brief Parameterized constructor
 * @param vector of pointers to Element abstract type
*/
Renderer::Renderer(const Vector2D<float> &_viewPort, const std::vector<Element *> &_shapes) : viewPort(_viewPort), shapes(_shapes), screenSize{_viewPort} {}
Renderer::Renderer(const Vector2D<float> &_viewPort, const std::vector<Element *> &_shapes, const Vector2D<float> &_screenSize) : viewPort(_viewPort), shapes(_shapes), screenSize(_screenSize) {}

/**
 * @brief Destructor
 * @note Delete all pointers in shapes vector
*/
Renderer::~Renderer() {
	for (auto &shape: shapes) delete shape;
}

/** @brief Traverse and draw all elements */
void Renderer::draw(Gdiplus::Graphics &graphics) {
	for (auto &shape: shapes) {
		switch (shape->getTypeName()) {
			case ElementType::Rectangle: {
				drawRect(graphics, static_cast<SVGRect *>(shape));
				break;
			}
			case ElementType::Ellipse: {
				drawEllipse(graphics, static_cast<SVGEllipse *>(shape));
				//shape->dbg();
				break;
			}
			case ElementType::Circle: {
				drawCircle(graphics, static_cast<SVGCircle *>(shape));
				//shape->dbg();
				break;
			}
			case ElementType::Line: {
				drawLine(graphics, static_cast<SVGLine *>(shape));
				//shape->dbg();
				break;
			}
			case ElementType::Polyline: {
				drawPolyline(graphics, static_cast<SVGPolyline *>(shape));
				break;
			}
			case ElementType::Polygon: {
				drawPolygon(graphics, static_cast<SVGPolygon *>(shape));
				break;
			}
			case ElementType::Text: {
				drawText(graphics, static_cast<SVGText *>(shape));
				//shape->dbg();
				break;
			}
			case ElementType::Path: {
				drawPath(graphics, static_cast<SVGPath *>(shape));
				break;
			}
			default:
				break;
		}
	}
}

/** @brief Draw a rectangle */
void Renderer::drawRect(Gdiplus::Graphics &graphics, SVGRect *element) {
	Vector2D<float> position = element->getPosition();
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	float width = element->getWidth();
	float height = element->getHeight();
	Vector2D<float> radii = element->getRadii();
	// Draw a color-filled Rectangle with normal corners
	if (radii.x == 0 && radii.y == 0) {
		// Draw stroke of rectangle
		Gdiplus::Pen pen(strokeColor, strokeWidth);
		graphics.DrawRectangle(&pen, position.x, position.y, width, height);
		Gdiplus::SolidBrush brush(fillColor);
		graphics.FillRectangle(&brush, position.x, position.y, width, height);
		//graphics.DrawArc(&pen, 100.0f, 100.0f, 50.0f, 50.0f, 0, 9)
	} else { /// <--- Rounded corner
		Gdiplus::Pen strokePen(strokeColor, strokeWidth);
		Gdiplus::SolidBrush brush(fillColor);
		Gdiplus::GraphicsPath path; // path for rounded rectangle
		// Top-left corner
		path.AddArc(position.x, position.y, radii.x * 2.0f, radii.y * 2.0f, 180, 90);
		// Top-right corner
		path.AddArc(position.x + width - radii.x * 2.0f, position.y, radii.x * 2.0f, radii.y * 2.0f, 270, 90);
		// Bottom-left corner
		path.AddArc(position.x, position.y + height - radii.y * 2.0f, radii.x * 2.0f, radii.y * 2.0f, 90, 90);
		// Bottom-right corner
		path.AddArc(position.x + width - radii.x * 2.0f, position.y + height - radii.y * 2.0f, radii.x * 2.0f, radii.y * 2.0f, 0, 90);
		// Close to form the final shape
		path.CloseFigure();
		graphics.FillPath(&brush, &path);
		graphics.DrawPath(&strokePen, &path);
		Gdiplus::Pen pen(strokeColor, strokeWidth);
	 }
}

/** @brief Draw an ellipse */
void Renderer::drawEllipse(Gdiplus::Graphics &graphics, SVGEllipse *element) {
	if (element == nullptr) return;
	Vector2D<float> position = element->getPosition();
	Vector2D<float> radius = element->getRadii();
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	Gdiplus::SolidBrush brush(fillColor);
	graphics.FillEllipse(&brush, position.x - radius.x, position.y - radius.y, radius.x * 2.0f, radius.y * 2.0f);
	if (strokeWidth != 0) {
		Gdiplus::Pen pen(strokeColor, strokeWidth);
		graphics.DrawEllipse(&pen, position.x - radius.x, position.y - radius.y, radius.x * 2.0f, radius.y * 2.0f);
	}
}

/** @brief Draw a circle */
void Renderer::drawCircle(Gdiplus::Graphics &graphics, SVGCircle *element) {
	Vector2D<float> radius = element->getRadii();
	radius.y = radius.x;
	element->setRadii(radius);
	drawEllipse(graphics, element);
}

/** @brief Draw a line */
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
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	std::vector<Vector2D < float>> points = element->getPoints();

	Gdiplus::SolidBrush brush(fillColor.operator Gdiplus::Color());
	Gdiplus::Pen pen(strokeColor.operator Gdiplus::Color(), strokeWidth);

	// Since polyline is open-formed, cannot use DrawPolygon() function to draw
	// Draw multiple offset lines to create a filled effect (default: winding mode)
	Gdiplus::GraphicsPath path(Gdiplus::FillModeWinding);
	path.StartFigure();
	for (int i = 0; i + 1 < (int) points.size(); ++i) {
		path.AddLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
	}
	graphics.FillPath(&brush, &path);
	graphics.DrawPath(&pen, &path);
}

/** @brief Draw a polygon */
void Renderer::drawPolygon(Gdiplus::Graphics &graphics, SVGPolygon *element) {
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	std::vector<Vector2D<float>> points = element->getPoints();

	Gdiplus::Point *pointsArr = new Gdiplus::Point[(int) points.size()];
	for (int i = 0; i < (int) points.size(); ++i)
		pointsArr[i] = Gdiplus::Point(points[i].x, points[i].y);

	Gdiplus::SolidBrush brush(fillColor.operator Gdiplus::Color());
	Gdiplus::Pen pen(strokeColor.operator Gdiplus::Color(), strokeWidth);
	// Fill the polygon
	graphics.FillPolygon(&brush, pointsArr, (int) points.size(), Gdiplus::FillModeWinding);
	// Draw stroke
	graphics.DrawPolygon(&pen, pointsArr, (int) points.size());

	delete[]pointsArr;
}

/** @brief Draw text */
void Renderer::drawText(Gdiplus::Graphics &graphics, SVGText *element) {
	if (element == nullptr) return;
	std::string data = element->getData();
	// convert string to wstring
//	std::wstring wData(data.size(), L'#');
//	mbstowcs(&wData[0], data.c_str(), data.size());
	std::wstring wData(data.begin(), data.end());

	float fontSize = element->getFontSize();
	SVGColor fillColor = element->getFillColor();

//	graphics.SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintAntiAlias);
//	Gdiplus::FontFamily fontFamily(L"Arial");
	Gdiplus::FontFamily fontFamily(L"Times New Roman");
	Gdiplus::Font font(&fontFamily, fontSize, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);

	Vector2D<float> actualPosition = element->getPosition();
	Gdiplus::SolidBrush solidBrush(fillColor);

	Gdiplus::RectF boundingBox;

	// Measure the text widthformat
	Gdiplus::RectF layoutRect;
	graphics.MeasureString(wData.c_str(), -1, &font, layoutRect, Gdiplus::StringFormat::GenericTypographic(), &boundingBox);
	float textWidth = boundingBox.Width;
	float x = actualPosition.x;
	if (element->getTextAnchor() == TextAnchor::MIDDLE) {
		x -= textWidth / 2.0f;
	} else if (element->getTextAnchor() == TextAnchor::END) {
		x -= textWidth;
	}

	// TODO: Research to https://learn.microsoft.com/en-us/dotnet/api/system.drawing.fontfamily.getemheight?view=windowsdesktop-8.0
//	float padding = fontFamily.GetEmHeight(Gdiplus::FontStyleRegular) / font.GetSize() / 6.0;
	float padding = font.GetHeight(graphics.GetDpiY()) / 6.0 + 0.5;
	actualPosition.y -= boundingBox.Height;
	actualPosition.y += padding; // GDI+ draw text with padding = 1/6 em on all sides, this however can expand to 1 em but I don't bother to fix it :l
	boundingBox.X = x;
	boundingBox.Y = actualPosition.y + padding;
	boundingBox.Height -= padding * 2;

	Gdiplus::Pen pen({255, 0, 0, 0});
//	graphics.DrawLine(&pen, x + 30, actualPosition.y, x + 30, actualPosition.y + size);
	graphics.DrawEllipse(&pen, boundingBox.X - 1.5f, boundingBox.Y - 1.5f, 3.0f, 3.0f);
	pen.SetColor(SVG_BLUE.alpha(200));
	graphics.DrawEllipse(&pen, element->getPosition().x - 3.0f, element->getPosition().y - 3.0f, 6.0f, 6.0f);
	graphics.DrawRectangle(&pen, boundingBox);
	graphics.DrawString(wData.c_str(), -1, &font, Gdiplus::PointF(x, actualPosition.y), Gdiplus::StringFormat::GenericTypographic(), &solidBrush);
}

/** @brief Draw path */
void Renderer::drawPath(Gdiplus::Graphics &graphics, SVGPath *element) {
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	FillRule fillRule = element->getFillRule();

	Gdiplus::Pen pen(strokeColor.operator Gdiplus::Color(), strokeWidth);
	Gdiplus::SolidBrush brush(fillColor.operator Gdiplus::Color());

	std::vector<PathPoint *> points = element->getPoints();

	Vector2D<float> sta;
	Vector2D<float> cur;
	Gdiplus::GraphicsPath path(fillRule == FillRule::NON_ZERO ? Gdiplus::FillModeWinding : Gdiplus::FillModeAlternate);

	for (int i = 0; i < (int)points.size(); ++i) {
		char ins = tolower(points[i]->getCMD());
		Vector2D<float> pos = points[i]->getPos();
		if (ins == 'm') { // Move-to command
			// Starting point of a path
			sta = pos;
			cur = pos;
			path.StartFigure();
		}
		else if (ins == 'l' || ins == 'h' || ins == 'v' || ins == 'z') {
			if (ins == 'z') { // <-- Close the path by drawing a line from current point to start point
				path.CloseFigure();
				cur = sta;
			}
			else {
				path.AddLine(cur.x, cur.y, pos.x, pos.y); // <-- Add a line from previous point to current point
				cur = pos;
			}
		}
		else if (ins == 'a') { // Drawing arc
			ArcPathPoint* pArc = static_cast<ArcPathPoint*>(points[i]);
			Vector2D<float> radii = pArc->getRadii();
			float xRotation = pArc->getXRotation();
			bool largeArcFlag = pArc->getLargeArcFlag();
			bool sweepFlag = pArc->getSweepFlag();

			// TODO: do research on how to draw arc in svg path
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
			float cFactor = (largeArcFlag != sweepFlag ? 1 : -1) * sqrt(radicant);

			float cxp = cFactor * ((radii.x * y1p) / radii.y);
			float cyp = cFactor * (-(radii.y * x1p) / radii.x);

			// Convert center point back to original coordinate system
			float cx = cosRotation * cxp - sinRotation * cyp + (cur.x + pos.x) / 2.0f;
			float cy = sinRotation * cxp + cosRotation * cyp + (cur.y + pos.y) / 2.0f;

			// Calculate start and sweep angles
			float startAngle = atan2((y1p - cyp) / radii.y, (x1p - cxp) / radii.x);
			float endAngle = atan2((-y1p - cyp) / radii.y, (-x1p - cxp) / radii.x);

			float sweepAngle = endAngle - startAngle;
			if (sweepFlag && sweepAngle < 0) sweepAngle += 2 * 3.14159265359f;
			if (!sweepFlag && sweepAngle > 0) sweepAngle -= 2 * 3.14159265359f;

			startAngle = startAngle * (180.0f / 3.14159265359f);
			sweepAngle = sweepAngle * (180.0f / 3.14159265359f);

			// Define bounding rectangle
			Gdiplus::RectF rect(cx - radii.x, cy - radii.y, radii.x * 2.0f, radii.y * 2.0f);
			path.AddArc(rect, startAngle, sweepAngle);
			cur = pos;
		}
		else if (ins == 'q' || ins == 't') { // Drawing Quadratic Bezier Curve
			QuadPathPoint *pQuad = static_cast<QuadPathPoint *>(points[i]);
			Vector2D<float> cen = pQuad->getCen();
			// normal quadratic bezier curve
			Gdiplus::PointF curvePoints[4] = { Gdiplus::PointF(cur.x, cur.y), Gdiplus::PointF((cur.x + cen.x * 2.0f) / 3.0f, (cur.y + cen.y * 2.0f) / 3.0f), Gdiplus::PointF((pos.x + cen.x * 2.0f) / 3.0f, (pos.y + cen.y * 2.0f) / 3.0f), Gdiplus::PointF(pos.x, pos.y)};
			path.AddBeziers(curvePoints, 4);
			cur = pos;
		}
		else if (ins == 'c' || ins == 's') { // Drawing Cubic Bezier Curve
			CubicPathPoint *pCubic = static_cast<CubicPathPoint *>(points[i]);
			Vector2D<float> cen1 = pCubic->getCen(0);
			Vector2D<float> cen2 = pCubic->getCen(1);
			Gdiplus::PointF curvePoints[4] = { Gdiplus::PointF(cur.x, cur.y), Gdiplus::PointF(cen1.x, cen1.y), Gdiplus::PointF(cen2.x, cen2.y), Gdiplus::PointF(pos.x, pos.y) };
			path.AddBeziers(curvePoints, 4);
			cur = pos;
		}
	}

	graphics.DrawPath(&pen, &path);
	graphics.FillPath(&brush, &path);
}
