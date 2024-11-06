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
void Renderer::draw() {
	for (auto &shape: shapes) {
		switch (shape->getTypeName()) {
			case ElementType::Rectangle: {
				drawRect(static_cast<SVGRect*>(shape));
				//shape->dbg();
				break;
			}
			case ElementType::Ellipse: {
				drawEllipse(static_cast<SVGEllipse*>(shape));
				//shape->dbg();
				break;
			}
			case ElementType::Circle: {
				drawCircle(static_cast<SVGCircle*>(shape));
				//shape->dbg();
				break;
			}
			case ElementType::Line: {
				drawLine(static_cast<SVGLine*>(shape));
				//shape->dbg();
				break;
			}
			case ElementType::Polyline: {
				drawPolyline(static_cast<SVGPolyline*>(shape));
				break;
			}
			case ElementType::Polygon: {
				//std::cout << "hey\n";
				drawPolygon(static_cast<SVGPolygon*>(shape));
				//shape->dbg();
				break;
			}
			case ElementType::Text: {
				drawText(static_cast<SVGText*>(shape), 10);
				//shape->dbg();
				break;
			}
			case ElementType::Path: {
				drawPath(static_cast<SVGPath*>(shape));
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
void Renderer::drawRect(SVGRect *element) {
	Vector2D<float> position = element->getPosition();
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	float width = element->getWidth();
	float height = element->getHeight();
	Vector2D<float> radii = element->getRadii();
	/// Draw a color-filled Rectangle with normal corner (Vector version)
	// if (radii.x == 0 && radii.y == 0) {
	// 	DrawRectangleV(POINT{position.x, position.y}, POINT{width, height}, fillColor.operator Color());
	// 	if (strokeWidth > 0) /// <-- Draw outline if strokeWidth > 0
	// 		DrawRectangleLinesEx(Rectangle{position.x, position.y, width, height}, strokeWidth, strokeColor.operator Color());
	// } else { /// <--- Rounded corner
	// 	float posX = position.x, posY = position.y, radiusx = radii.x, radiusy = radii.y;
	// 	DrawRectangleRoundedStrokeRLEX({posX, posY, width, height}, radii, strokeWidth, fillColor, strokeColor, renderTexture);
	// }
}

/** @brief Draw an ellipse */
void Renderer::drawEllipse(SVGEllipse *element) {
	// Vector2D<float> position = element->getPosition();
	// Vector2D<float> radii = element->getRadii();
	// SVGColor fillColor = element->getFillColor();
	// SVGColor strokeColor = element->getStrokeColor();
	// 	// float strokeWidth = element->getStrokeWidth();
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
void Renderer::drawPolyline(SVGPolyline *element) {}

/*
* @brief Draw a polygon
* @note Using scan fill algorithm
*/
void Renderer::drawPolygon(SVGPolygon *element) {}

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
