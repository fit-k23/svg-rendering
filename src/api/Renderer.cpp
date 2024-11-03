#include "Renderer.h"
#include "../utils/Raylibex.h"
#include "conio.h"
/*
* @brief Default constructor
*/
Renderer::Renderer() {
	viewPort = Vector2D<float>();
	shapes.clear();
}

/*
* @brief Parameterized constructor
* @param vector of pointers to Element abstract type
*/
Renderer::Renderer(const Vector2D<float>& viewPort, const std::vector<Element*>& shapes) : viewPort(viewPort), shapes(shapes) {}

/*
* @brief Destructor
* @note Delete all pointers in shapes vector
*/
Renderer::~Renderer() {
	for (auto &shape : shapes)
		delete shape;
}

/*
* @brief Traverse and draw all elements
*/
void Renderer::draw() {
	InitWindow(viewPort.x, viewPort.y, "SVG-Renderer");
	std::cout << viewPort.x << " " << viewPort.y << '\n';
	RenderTexture2D renderTexture = LoadRenderTexture(viewPort.x, viewPort.y);
	ClearBackground(WHITE);
	while (!WindowShouldClose()) {
		BeginDrawing();

<<<<<<< Updated upstream
		for (auto &shape : shapes) {
			switch (shape->getTypeName()) {
				case ElementType::Rect: {
					drawRect(dynamic_cast<Rect *>(shape), renderTexture);
					break;
				}
				case ElementType::Ellipse: {
					drawEllipse(dynamic_cast<Ellipse *>(shape));
					break;
				}
				case ElementType::Circle: {
					drawCircle(dynamic_cast<Circle *>(shape));
					break;
				}
				case ElementType::Line: {
					drawLine(dynamic_cast<Line *>(shape));
					break;
				}
				case ElementType::Polyline: {
					drawPolyline(dynamic_cast<Polyline *>(shape));
					break;
				}
				case ElementType::Polygon: {
					drawPolygon(dynamic_cast<Polygon *>(shape));
					break;
				}
				case ElementType::Text: {
					drawText(dynamic_cast<Text *>(shape));
					break;
				}
				case ElementType::Path: {
					drawPath(dynamic_cast<Path *>(shape));
					break;
				}
				default:
					break;
			}
		}
=======
<<<<<<< HEAD
		for (int i = 0; i < (int)shapes.size(); ++i) {
			if (shapes[i]->getTypeName() == ElementType::Rect) {
				std::cout << "yay\n";
				drawRect(shapes[i], renderTexture);
				//break;
			}
			else if (shapes[i]->getTypeName() == ElementType::Ellipse) {
				drawEllipse(shapes[i]);
			}
			else if (shapes[i]->getTypeName() == ElementType::Circle) {
				drawCircle(shapes[i]);
			}
			else if (shapes[i]->getTypeName() == ElementType::Line) {
				drawLine(shapes[i]);
			}
			else if (shapes[i]->getTypeName() == ElementType::Polyline) {
				drawPolyline(shapes[i]);
			}
			else if (shapes[i]->getTypeName() == ElementType::Polygon) {
				drawPolygon(shapes[i]);
			}
			else if (shapes[i]->getTypeName() == ElementType::Text) {
				drawText(shapes[i]);
			}
			else if (shapes[i]->getTypeName() == ElementType::Path) {
				drawPath(shapes[i]);
			}
		}
		//DrawRectangle(100, 100, 50, 50, BLACK);
=======
		for (auto &shape : shapes) {
			switch (shape->getTypeName()) {
				case ElementType::Rect: {
					drawRect(dynamic_cast<Rect *>(shape), renderTexture);
					break;
				}
				case ElementType::Ellipse: {
					drawEllipse(dynamic_cast<Ellipse *>(shape));
					break;
				}
				case ElementType::Circle: {
					drawCircle(dynamic_cast<Circle *>(shape));
					break;
				}
				case ElementType::Line: {
					drawLine(dynamic_cast<Line *>(shape));
					break;
				}
				case ElementType::Polyline: {
					drawPolyline(dynamic_cast<Polyline *>(shape));
					break;
				}
				case ElementType::Polygon: {
					drawPolygon(dynamic_cast<Polygon *>(shape));
					break;
				}
				case ElementType::Text: {
					drawText(dynamic_cast<Text *>(shape));
					break;
				}
				case ElementType::Path: {
					drawPath(dynamic_cast<Path *>(shape));
					break;
				}
				default:
					break;
			}
		}
>>>>>>> c5827fd72586cae62913d9e34108d16fd4aba27a
>>>>>>> Stashed changes
		EndDrawing();
		break;
	}

	char c = _getch();
	CloseWindow();
}

/*
* @brief Draw a rectangle
*/
void Renderer::drawRect(Rect *element, RenderTexture2D &renderTexture) {
	Vector2D<float> position = element->getPosition();
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	float width = element->getWidth();
	float height = element->getHeight();
	Vector2D<float> radii = element->getRadii();
	/// Draw a color-filled Rectangle with normal corner (Vector version)
	if (radii.x == 0 && radii.y == 0) {
		//std::cout << "Drawing a normal rect\n";
		//std::cout << "Position: " << position.x << " " << position.y << '\n';
		//std::cout << "Fill color: "; fillColor.output(); std::cout << '\n';
		//std::cout << "Stroke color: "; strokeColor.output(); std::cout << '\n';
		//std::cout << "Stroke width: " << strokeWidth << '\n';
		//std::cout << "Width: " << width << " Height: " << height << '\n';
		//std::cout << "Radii: " << radii.x << " " << radii.y << '\n';
		DrawRectangleV(Vector2{ position.x, position.y }, Vector2{ width, height }, fillColor.operator Color());
		if (strokeWidth > 0) /// <-- Draw outline if strokeWidth > 0
			DrawRectangleLinesEx(Rectangle{ position.x, position.y, width, height }, strokeWidth, strokeColor.operator Color());
<<<<<<< Updated upstream
	} else { /// <--- Rounded corner
		float posX = position.x, posY = position.y, radiusx = radii.x, radiusy = radii.y;
		DrawRectangleRoundedStrokeRLEX({posX, posY, 300, 200}, {130, 100}, 4, ColorAlpha(RED, 0.8), ColorAlpha(BLUE, 0.9), renderTexture);
=======
<<<<<<< HEAD
	}
	else { /// <--- Rounded corner
		DrawRectangleRoundedStrokeRLEX(Rectangle{ position.x, position.y, width, height }, { radii.x, radii.y }, strokeWidth, 
		fillColor.operator Color(), strokeColor.operator Color(), renderTexture);
=======
	} else { /// <--- Rounded corner
		float posX = position.x, posY = position.y, radiusx = radii.x, radiusy = radii.y;
		DrawRectangleRoundedStrokeRLEX({posX, posY, 300, 200}, {130, 100}, 4, ColorAlpha(RED, 0.8), ColorAlpha(BLUE, 0.9), renderTexture);
>>>>>>> c5827fd72586cae62913d9e34108d16fd4aba27a
>>>>>>> Stashed changes
	}
}

/*
* @brief Draw an ellipse
*/
void Renderer::drawEllipse(Ellipse *element) {
	if (element->getStrokeWidth() != 0) {
		DrawEllipseVRLEX(element->getPosition(), element->getRadii(), element->getStrokeColor(), 1);
		DrawEllipseVRLEX(element->getPosition(), Vector2Subtract(element->getRadii(), {element->getStrokeWidth(), element->getStrokeWidth()}), element->getFillColor(), 1);
	} else {
		DrawEllipseVRLEX(element->getPosition(), element->getRadii(), element->getFillColor(), 1);
	}
}

/*
* @brief Draw a circle
*/
void Renderer::drawCircle(Circle *element) {

}

/*
* @brief Draw a line
*/
void Renderer::drawLine(Line *element) {

}

/*
* @brief Draw polyline
*/
void Renderer::drawPolyline(Polyline *element) {

}

/*
* @brief Draw a polygon
*/
void Renderer::drawPolygon(Polygon *element) {

}

/*
* @brief Draw text
*/
void Renderer::drawText(Text *element) {

}

/*
* @brief Draw path
*/
void Renderer::drawPath(Path *element) {

}
