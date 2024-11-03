#include "Renderer.h"
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
Renderer::Renderer(const Vector2D<float> &_viewPort, const std::vector<Element *> &_shapes) : viewPort(_viewPort), shapes(_shapes), screenSize{} {}
Renderer::Renderer(const Vector2D<float> &_viewPort, const std::vector<Element *> &_shapes, Vector2 _screenSize) : viewPort(_viewPort), shapes(_shapes), screenSize(_screenSize){}

/*
* @brief Destructor
* @note Delete all pointers in shapes vector
*/
Renderer::~Renderer() {
	for (auto &shape : shapes) delete shape;
}

/// LOGO
#include "../utils/Icon.h"

#define APPLICATION_NAME "SVG RENDERING"

/*
* @brief Traverse and draw all elements
*/
void Renderer::draw() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	//Enable MSAA 4X anti-aliasing
	SetConfigFlags(FLAG_MSAA_4X_HINT);

	//Better image but blurry text...
	//SetConfigFlags(FLAG_WINDOW_HIGHDPI);

	InitWindow(screenSize.x, screenSize.y, APPLICATION_NAME);
	SetTargetFPS(60);

	RenderTexture2D renderTexture = RenderTexturePool::getRenderTexture(screenSize.x, screenSize.y);

	Camera2D camera;
	camera.target = Vector2Scale(screenSize, 0.5f);
	camera.offset = camera.target;
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	Image icon = LoadImageFromMemory(".png", ICON_DATA, ICON_LEN);

	if (icon.data != nullptr) {
		// Set the window icon
		SetWindowIcon(icon);
		// We no longer need the image in memory once the icon is set
		UnloadImage(icon);
	} else {
		printf("Failed to load icon.\n");
	}

	bool maximumWindow = false;
	Vector2 previousScreenSize = screenSize;
	bool rotateMode = false;
	while (!WindowShouldClose()) {
		float wheel = GetMouseWheelMove();
		if (wheel != 0) {
			camera.zoom += (GetMouseWheelMove() * 0.05f);
			if (camera.zoom > 3.0f) camera.zoom = 3.0f;
			else if (camera.zoom < 0.1f) camera.zoom = 0.1f;
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			Vector2 delta = Vector2Scale(GetMouseDelta(), -1.0f / camera.zoom);
			camera.target = Vector2Add(camera.target, delta);
		}



		if (IsKeyPressed(KEY_F)) {
			if (maximumWindow) {
				previousScreenSize = screenSize;
				MaximizeWindow();
			} else {
				SetWindowSize(previousScreenSize.x, previousScreenSize.y);
			}
			maximumWindow = !maximumWindow;
		}

		Vector2 currentScreenSize = {static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())};

		if (screenSize.x != currentScreenSize.x || screenSize.y != currentScreenSize.y) {
			previousScreenSize = screenSize;
			screenSize = currentScreenSize;
		}

		if (IsKeyPressed(KEY_R)) {
			camera.target = Vector2Scale(screenSize, 0.5f);
			camera.offset = camera.target;
			camera.rotation = 0.0f;
			camera.zoom = 1.0f;
		}

		if (IsKeyDown(KEY_RIGHT)) camera.target.x -= 5;
		if (IsKeyDown(KEY_LEFT)) camera.target.x += 5;
		if (IsKeyDown(KEY_UP)) camera.target.y += 5;
		if (IsKeyDown(KEY_DOWN)) camera.target.y -= 5;
		if (IsKeyPressed(KEY_EQUAL)) camera.zoom += 0.05f;
		if (IsKeyPressed(KEY_MINUS)) camera.zoom -= 0.05f;
		if (IsKeyDown(KEY_W)) camera.rotation += 0.5f;
		if (IsKeyDown(KEY_S)) camera.rotation -= 0.5f;

		BeginDrawing();
		ClearBackground(BLANK);

		if (!IsKeyDown(KEY_B)) {
			int sx = GetScreenWidth() / 10;
			int sy = GetScreenHeight() / 10;

			for (int i = 0; i < sx; i++) {
				for (int j = 0; j < sy; j++) {
					if ((i + j) % 2 == 0) {
						DrawRectangle(i * 10, j * 10, 10, 10, GRAY);
					}
				}
			}
		} else {
			ClearBackground(WHITE);
		}


		DrawRectangle(0, 0, 350, 75, ColorAlpha({20, 20, 20}, 0.75));
		DrawText("Hold left click to move camera", 0, 0, 20, YELLOW);
		DrawText("Scroll mouse wheel to zoom in/out", 0, 25, 20, YELLOW);

		BeginMode2D(camera);

		DrawText("Hold right click to rotate camera", 0, 50, 20, YELLOW);

		for (auto &shape : shapes) {
			switch (shape->getTypeName()) {
				case ElementType::Rect: {
					drawRect(dynamic_cast<Rect *>(shape), renderTexture);
					break;
				}
				case ElementType::Ellipse: {
					drawEllipse(dynamic_cast<Ellipse *>(shape), renderTexture, camera);
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

		EndMode2D();
		EndDrawing();
	}
	for (auto &rt : RenderTexturePool::getPools()) UnloadRenderTexture(rt);

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
		DrawRectangleV(Vector2{ position.x, position.y }, Vector2{ width, height }, fillColor.operator Color());
		if (strokeWidth > 0) /// <-- Draw outline if strokeWidth > 0
			DrawRectangleLinesEx(Rectangle{ position.x, position.y, width, height }, strokeWidth, strokeColor.operator Color());
	} else { /// <--- Rounded corner
		float posX = position.x, posY = position.y, radiusx = radii.x, radiusy = radii.y;
		DrawRectangleRoundedStrokeRLEX({posX, posY, width, height}, radii, strokeWidth, fillColor, strokeColor, renderTexture);
	}
}

/*
* @brief Draw an ellipse
*/
void Renderer::drawEllipse(Ellipse *element, RenderTexture2D renderTexture, Camera2D camera) {
	if (element->getStrokeWidth() != 0) {
		DrawEllipseStrokeRLEX(element->getPosition(), element->getRadii(), element->getStrokeWidth(), element->getFillColor(), element->getStrokeColor(), 1, renderTexture, camera);
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
