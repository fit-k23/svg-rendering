#include "Renderer.h"

/** @brief Default constructor */
Renderer::Renderer() : screenSize{}, viewPort{Vector2D<float>{}} {
	shapes.clear();
}

/**
 * @brief Parameterized constructor
 * @param vector of pointers to Element abstract type
*/
Renderer::Renderer(const Vector2D<float> &_viewPort, const std::vector<Element*> &_shapes) : viewPort(_viewPort), shapes(_shapes), screenSize{viewPort} {}

Renderer::Renderer(const Vector2D<float> &_viewPort, const std::vector<Element*> &_shapes, const Vector2D<float> &_screenSize) : viewPort(_viewPort), shapes(_shapes), screenSize(_screenSize) {}

/**
 * @brief Destructor
 * @note Delete all pointers in shapes vector
*/
Renderer::~Renderer() {
	for (auto &shape: shapes) delete shape;
}

/** @brief Traverse and draw all elements */
void Renderer::draw(Gdiplus::Graphics& graphics) {
	for (auto &shape: shapes) {
		switch (shape->getTypeName()) {
			case ElementType::Rectangle: {
				drawRect(graphics, static_cast<SVGRect*>(shape));
				//shape->dbg();
				break;
			}
			case ElementType::Ellipse: {
				drawEllipse(graphics, static_cast<SVGEllipse*>(shape));
				//shape->dbg();
				break;
			}
			case ElementType::Circle: {
				drawCircle(graphics, static_cast<SVGCircle*>(shape));
				//shape->dbg();
				break;
			}
			case ElementType::Line: {
				drawLine(graphics, static_cast<SVGLine*>(shape));
				//shape->dbg();
				break;
			}
			case ElementType::Polyline: {
				drawPolyline(graphics, static_cast<SVGPolyline*>(shape));
				break;
			}
			case ElementType::Polygon: {
				drawPolygon(graphics, static_cast<SVGPolygon*>(shape));
				break;
			}
			case ElementType::Text: {
				drawText(graphics, static_cast<SVGText*>(shape));
				//shape->dbg();
				break;
			}
			case ElementType::Path: {
				drawPath(graphics, static_cast<SVGPath*>(shape));
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
void Renderer::drawPolyline(Gdiplus::Graphics &graphics, SVGPolyline* element) {
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	std::vector<Vector2D<float>> points = element->getPoints();

	Gdiplus::SolidBrush brush(fillColor.operator Gdiplus::Color());
	Gdiplus::Pen pen(strokeColor.operator Gdiplus::Color(), strokeWidth);

	// Since polyline is open-formed, cannot use DrawPolygon() function to draw
	// Draw multiple offset lines to create a filled effect (default: winding mode)
	Gdiplus::GraphicsPath path(Gdiplus::FillModeWinding);
	path.StartFigure();
	for (int i = 0; i + 1 < (int)points.size(); ++i) {
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

	Gdiplus::Point* pointsArr = new Gdiplus::Point[(int)points.size()];
	for (int i = 0; i < (int)points.size(); ++i)
		pointsArr[i] = Gdiplus::Point(points[i].x, points[i].y);

	Gdiplus::SolidBrush brush(fillColor.operator Gdiplus::Color());
	Gdiplus::Pen pen(strokeColor.operator Gdiplus::Color(), strokeWidth);
	// Fill the polygon
	graphics.FillPolygon(&brush, pointsArr, (int)points.size(), Gdiplus::FillModeWinding);
	// Draw stroke
	graphics.DrawPolygon(&pen, pointsArr, (int)points.size());

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

	Gdiplus::FontFamily fontFamily(L"Times New Roman");
	Gdiplus::Font font(&fontFamily, fontSize - 13); //, Gdiplus::FontStyleBold, Gdiplus::UnitPoint);
//	Gdiplus::Font font(&fontFamily, fontSize); //, Gdiplus::FontStyleBold, Gdiplus::UnitPoint);

	Gdiplus::RectF layoutRect;
	Gdiplus::StringFormat format;
	format.SetAlignment(TextAnchorHelper::getStringAlignment(element->getTextAnchor()));
	Gdiplus::RectF boundRect;
	// Measure the string.
	graphics.MeasureString(wData.c_str(), -1, &font, layoutRect, &format, &boundRect);

//	Vector2D<float> actualPosition = element->getActualPosition({boundRect.Width, boundRect.Height});
	Vector2D<float> actualPosition = element->getPosition();
	boundRect.X = actualPosition.x;
	boundRect.Y = actualPosition.y;
	Gdiplus::SolidBrush solidBrush(fillColor);

	graphics.DrawString(wData.c_str(), -1, &font, boundRect, nullptr, &solidBrush);
	Gdiplus::Pen pen({255, 0, 0, 0});
	graphics.DrawEllipse(&pen, actualPosition.x, actualPosition.y, 3.0f, 3.0f);
	graphics.DrawRectangle(&pen, boundRect);
	pen.SetColor({255, 255, 0, 0});
	graphics.DrawRectangle(&pen, layoutRect);
}

/** @brief Draw path */
void Renderer::drawPath(Gdiplus::Graphics &graphics, SVGPath *element) {
	
}
