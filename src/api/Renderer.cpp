#include "Renderer.h"
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
	for (int i = 0; i < (int)shapes.size(); ++i)
		delete shapes[i];
}

/*
* @brief Traverse and draw all elements
*/
void Renderer::draw() {
	InitWindow(viewPort.x, viewPort.y, "SVG-Renderer");
	RenderTexture2D renderTexture = LoadRenderTexture(viewPort.x, viewPort.y);
	while (!WindowShouldClose()) {
		BeginDrawing();

		for (int i = 0; i < (int)shapes.size(); ++i) {
			if (shapes[i]->getTypeName() == ElementType::Rect) {
				drawRect(shapes[i], renderTexture);
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

		EndDrawing();
	}

	CloseWindow();
}

/*
* @brief Draw a rounded rectangle
* @note Draw 5 rectangle and 4 ellipse .-.
*/
void Renderer::drawRoundedRect(float posX, float posY, float width, float height, float radiusx, float radiusy, SVGColor color, 
	RenderTexture2D renderTexture) {
	BeginTextureMode(renderTexture);
	ClearBackground(BLANK);

	Color pureColor = color.pureColor();

	// Draw the central part of the rectangle
	DrawRectangle(posX + radiusx, posY + radiusy, width - 2 * radiusx, height - 2 * radiusy, pureColor);
	// Draw the side rectangles (top, bottom, left, right)
	DrawRectangle(posX + radiusx, posY, width - 2 * radiusx, radiusy, pureColor);                   // Top
	DrawRectangle(posX + radiusx, posY + height - radiusy, width - 2 * radiusx, radiusy, pureColor); // Bottom
	DrawRectangle(posX, posY + radiusx, radiusx, height - 2 * radiusy, pureColor);                  // Left
	DrawRectangle(posX + width - radiusx, posY + radiusy, radiusx, height - 2 * radiusy, pureColor); // Right

	DrawEllipse(posX + radiusx, posY + radiusy, radiusx, radiusy, pureColor);                      // Top-left corner
	DrawEllipse(posX + width - radiusx, posY + radiusy, radiusx, radiusy, pureColor);              // Top-right corner
	DrawEllipse(posX + radiusx, posY + height - radiusy, radiusx, radiusy, pureColor);             // Bottom-left corner
	DrawEllipse(posX + width - radiusx, posY + height - radiusy, radiusx, radiusy, pureColor);     // Bottom-right corner

	EndTextureMode();

	DrawTextureV(renderTexture.texture, { 0, 0 }, ColorAlpha(pureColor, (float)color.a / 255.0f));
}

/*
* @brief Draw a rectangle
*/
void Renderer::drawRect(Element* element, RenderTexture2D& renderTexture) {
	Vector2D<float> position = element->getPosition();
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	float width = static_cast<Rect*>(element)->getWidth();
	float height = static_cast<Rect*>(element)->getHeight();
	Vector2D<float> radii = static_cast<Rect*>(element)->getRadii();
	/// Draw a color-filled Rectangle with normal corner (Vector version)
	if (radii.x == 0 && radii.y == 0) {
		DrawRectangleV(Vector2{ position.x, position.y }, Vector2{ width, height }, fillColor.operator Color());
		if (strokeWidth > 0) /// <-- Draw outline if strokeWidth > 0
			DrawRectangleLinesEx(Rectangle{ position.x, position.y, width, height }, strokeWidth, strokeColor.operator Color());
	}
	else { /// <--- Rounded corner
		float posX = position.x, posY = position.y, radiusx = radii.x, radiusy = radii.y;
		drawRoundedRect(posX - strokeWidth, posY - strokeWidth, width + 2 * strokeWidth, height + 2 * strokeWidth, radiusx + strokeWidth, 
						radiusy + strokeWidth, strokeColor, renderTexture);
		drawRoundedRect(posX, posY, width, height, radiusx, radiusy, fillColor, renderTexture);
	}
}

/*
* @brief Draw an ellipse
*/
void Renderer::drawEllipse(Element* element) {

}

/*
* @brief Draw a circle
*/
void Renderer::drawCircle(Element* element) {

}

/*
* @brief Draw a line
*/
void Renderer::drawLine(Element* element) {

}

/*
* @brief Draw polyline
*/
void Renderer::drawPolyline(Element* element) {

}

/*
* @brief Draw a polygon
*/
void Renderer::drawPolygon(Element* element) {

}

/*
* @brief Draw text
*/
void Renderer::drawText(Element* element) {

}

/*
* @brief Draw path
*/
void Renderer::drawPath(Element* element) {

}
