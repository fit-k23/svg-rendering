#include "Renderer.h"
#include "conio.h"

/*
* @brief Default constructor
*/
Renderer::Renderer() : screenSize{}, viewPort{Vector2D<float>{}} {
	shapes.clear();
}

/*
* @brief Parameterized constructor
* @param vector of pointers to Element abstract type
*/
Renderer::Renderer(const Vector2D<float> &_viewPort, const std::vector<Element*> &_shapes) : viewPort(_viewPort),
	shapes(_shapes), screenSize{} {}

Renderer::Renderer(const Vector2D<float> &_viewPort, const std::vector<Element*> &_shapes,
	Vector2D<float> _screenSize) : viewPort(_viewPort), shapes(_shapes), screenSize(_screenSize) {}

/*
* @brief Destructor
* @note Delete all pointers in shapes vector
*/
Renderer::~Renderer() {
	for (auto &shape: shapes) delete shape;
}

#define APPLICATION_NAME "SVG RENDERING"

/*
* @brief Traverse and draw all elements
*/
void Renderer::draw(Gdiplus::Graphics& graphics) {
	for (auto &shape: shapes) {
		switch (shape->getTypeName()) {
			case ElementType::Rectangle: {
				drawRect(graphics, static_cast<SVGRect*>(shape));
				//shape->dbg();
				//Gdiplus::REAL x = 50.0f, y = 50.0f, width = 200.0f, height = 100.0f;
				//Gdiplus::Pen pen(Gdiplus::Color(220, 255, 0, 0), 10);  // Red color, 3 pixel width
				//graphics.DrawRectangle(&pen, x, y, width, height);
				break;
			}
			case ElementType::Ellipse: {
				//drawEllipse(static_cast<SVGEllipse*>(shape));
				//shape->dbg();
				break;
			}
			case ElementType::Circle: {
				//drawCircle(static_cast<SVGCircle*>(shape));
				//shape->dbg();
				break;
			}
			case ElementType::Line: {
				//drawLine(static_cast<SVGLine*>(shape));
				//shape->dbg();
				break;
			}
			case ElementType::Polyline: {
				drawPolyline(graphics, static_cast<SVGPolyline*>(shape));
				break;
			}
			case ElementType::Polygon: {
				drawPolygon(graphics, static_cast<SVGPolygon*>(shape));
				//shape->dbg();
				//Gdiplus::SolidBrush fillBrush(Gdiplus::Color(255, 255, 0, 0)); // Red fill color

				// Define the points for the polygon.
				/*Gdiplus::Point* points = new Gdiplus::Point[5];
				points[0] = Gdiplus::Point(50, 50);
				points[1] = Gdiplus::Point(100, 100);
				points[2] = Gdiplus::Point(150, 50);
				points[3] = Gdiplus::Point(200, 100);
				points[4] = Gdiplus::Point(250, 50);*/


				//Gdiplus::Point points[5] = {
				//	Gdiplus::Point(50, 50),
				//	Gdiplus::Point(100, 100),
				//	Gdiplus::Point(150, 50),
				//	Gdiplus::Point(200, 100),
				//	Gdiplus::Point(250, 50)
				//};

				// Fill the polygon defined by the points.
				//graphics.FillPolygon(&fillBrush, points, 5); // '5' is the number of points
				//delete[] points;
				break;
			}
			case ElementType::Text: {
				//drawText(static_cast<SVGText*>(shape), 10);
				//shape->dbg();
				break;
			}
			case ElementType::Path: {
				//drawPath(static_cast<SVGPath*>(shape));
				break;
			}
			default:
				break;
		}
	}
}

/*
* @brief Draw a rectangle
*/
void Renderer::drawRect(Gdiplus::Graphics& graphics, SVGRect *element) {
	Vector2D<float> position = element->getPosition();
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	float width = element->getWidth();
	float height = element->getHeight();
	Vector2D<float> radii = element->getRadii();
	/// Draw a color-filled Rectangle with normal corners 
	 if (radii.x == 0 && radii.y == 0) {
		 // Draw stroke of rectangle
		 Gdiplus::Pen pen(strokeColor.operator Gdiplus::Color(), strokeWidth);
		 graphics.DrawRectangle(&pen, position.x, position.y, width, height);
		 Gdiplus::SolidBrush brush(fillColor.operator Gdiplus::Color());
		 graphics.FillRectangle(&brush, position.x, position.y, width, height);
		 //graphics.DrawArc(&pen, 100.0f, 100.0f, 50.0f, 50.0f, 0, 9)
	 } else { /// <--- Rounded corner
		 Gdiplus::Pen strokePen(strokeColor.operator Gdiplus::Color(), strokeWidth);
		 Gdiplus::SolidBrush brush(fillColor.operator Gdiplus::Color());
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
	 }
}

/** @brief Draw an ellipse */
void Renderer::drawEllipse(SVGEllipse *element) {
	Vector2D<float> position = element->getPosition();
	Vector2D<float> radius = element->getRadii();
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();


	// 	// /// TODO: Draw outer outline and inner outline
	// 	// BeginTextureMode(renderTexture);
	// 	// ClearBackground(BLANK);
	// 	// BeginBlendMode(BLEND_SUBTRACT_COLORS);
	// 	// DrawEllipse(position
	// 	// .x, position.y, radii.x + strokeWidth / 2.0f, radii.y + strokeWidth / 2.0f, strokeColor.
	// 	//
	// 	// pureColor()
	//
	// );
	// DrawEllipse(position
	// .x, position.y, radii.x - strokeWidth / 2.0f, radii.y - strokeWidth / 2.0f, strokeColor.
	//
	// pureColor()
	//
	// );
	//
	// EndBlendMode();
	//
	// EndTextureMode();
	//
	// DrawTextureRec(renderTexture
	// .texture, {
	// 0, 0, (float)renderTexture.texture.width, (float)-renderTexture.texture.height }, {
	// 0, 0 },
	// ColorAlpha(WHITE,
	// (float)strokeColor.a / 255.0f));
	// /// TODO: Draw inner ellipse
	// BeginTextureMode(renderTexture);
	// ClearBackground(BLANK);
	// DrawEllipse(position
	// .x, position.y, radii.x - strokeWidth / 2.0f, radii.y - strokeWidth / 2.0f, fillColor.
	//
	// pureColor()
	//
	// );
	//
	// EndTextureMode();
	//
	// DrawTextureRec(renderTexture
	// .texture, {
	// 0, 0, (float)renderTexture.texture.width, (float)-renderTexture.texture.height }, {
	// 0, 0 },
	// ColorAlpha(WHITE,
	// (float)fillColor.a / 255.0f));
}

/*
* @brief Draw a circle
*/
void Renderer::drawCircle(SVGCircle *element) {
	drawEllipse(static_cast<SVGEllipse*>(element));
}

/*
* @brief Draw a line
*/
void Renderer::drawLine(SVGLine *element) {
	Vector2D<float> position = element->getPosition();
	Vector2D<float> endPosition = element->getEndPosition();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();

	// DrawLineEx({position.x, position.y}, {endPosition.x, endPosition.y}, strokeWidth, strokeColor.operator Color());
}

/*
* @brief Draw polyline
*/
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

/*
* @brief Draw a polygon
*/
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

/*
* @brief Draw text
*/
void Renderer::drawText(SVGText *element, float offset) {
	std::string data = element->getData();
	Vector2D<float> position = element->getPosition();
	float fontSize = element->getFontSize();
	SVGColor fillColor = element->getFillColor();
	std::string textAnchor = element->getTextAnchor();

	float actualY = position.y - fontSize + offset;
	float actualX = position.x;
	// POINT dataSize = MeasureTextEx(font, &data[0], fontSize, 1.0);
	// element->setDataSize(dataSize);

	if (textAnchor == "middle" || textAnchor == "end") {
		// if (textAnchor == "middle") dataSize.x /= 2.0f;
		// actualX -= dataSize.x;
	}
	// DrawTextEx(font, &data[0], {position.x, actualY}, fontSize, 1, fillColor.operator Color());
}

/*
* @brief Draw path
*/
void Renderer::drawPath(SVGPath *element) {}
