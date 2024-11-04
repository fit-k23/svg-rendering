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
	Font font = LoadFont("asset/font/arial.ttf");

	//Camera2D camera;
	//camera.target = Vector2Scale(screenSize, 0.5f);
	//camera.offset = camera.target;
	//camera.rotation = 0.0f;
	//camera.zoom = 1.0f;

	//Image icon = LoadImageFromMemory(".png", ICON_DATA, ICON_LEN);

	//if (icon.data != nullptr) {
	//	// Set the window icon
	//	SetWindowIcon(icon);
	//	// We no longer need the image in memory once the icon is set
	//	UnloadImage(icon);
	//} else {
	//	printf("Failed to load icon.\n");
	//}

	//bool maximumWindow = false;
	//Vector2 previousScreenSize = screenSize;
	//bool rotateMode = false;
	while (!WindowShouldClose()) {
		/*float wheel = GetMouseWheelMove();
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
		if (IsKeyDown(KEY_S)) camera.rotation -= 0.5f;*/

		BeginDrawing();
		ClearBackground(RAYWHITE);

		/*if (!IsKeyDown(KEY_B)) {
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

		DrawText("Hold right click to rotate camera", 0, 50, 20, YELLOW);*/

		for (auto &shape : shapes) {
			switch (shape->getTypeName()) {
				case ElementType::Rect: {
					drawRect(static_cast<Rect *>(shape), renderTexture);
					shape->dbg();
					break;
				}
				case ElementType::Ellipse: {
					drawEllipse(static_cast<Ellipse *>(shape), renderTexture);
					shape->dbg();
					break;
				}
				case ElementType::Circle: {
					drawCircle(static_cast<Circle *>(shape), renderTexture);
					shape->dbg();
					break;
				}
				case ElementType::Line: {
					drawLine(static_cast<Line *>(shape), renderTexture);
					shape->dbg();
					break;
				}
				case ElementType::Polyline: {
					drawPolyline(static_cast<Polyline *>(shape));
					break;
				}
				case ElementType::Polygon: {
					drawPolygon(static_cast<Polygon *>(shape));
					break;
				}
				case ElementType::Text: {
					drawText(static_cast<Text *>(shape), font, 10);
					shape->dbg();
					break;
				}
				case ElementType::Path: {
					drawPath(static_cast<Path *>(shape));
					break;
				}
				default:
					break;
			}
		}

		//EndMode2D();
		EndDrawing();
		break;
	}
	for (auto &rt : RenderTexturePool::getPools()) UnloadRenderTexture(rt);
	UnloadFont(font);
	char c = _getch();
	CloseWindow();
}

/*
* @brief Draw a rectangle
*/
void Renderer::drawRect(Rect *element, RenderTexture2D renderTexture) {
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
void Renderer::drawEllipse(Ellipse *element, RenderTexture2D renderTexture) {
	Vector2D<float> position = element->getPosition();
	Vector2D<float> radii = element->getRadii(); 
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();
	// Draw outer outline and inner outline
	BeginTextureMode(renderTexture);
	ClearBackground(BLANK);
	BeginBlendMode(BLEND_SUBTRACT_COLORS);
	DrawEllipse(position.x, position.y, radii.x + strokeWidth / 2.0f, radii.y + strokeWidth / 2.0f, strokeColor.pureColor());
	DrawEllipse(position.x, position.y, radii.x - strokeWidth / 2.0f, radii.y - strokeWidth / 2.0f, strokeColor.pureColor());
	EndBlendMode();
	EndTextureMode();
	DrawTextureRec(renderTexture.texture, { 0, 0, (float)renderTexture.texture.width, (float)-renderTexture.texture.height }, { 0, 0 }, 
		ColorAlpha(WHITE, (float)strokeColor.a / 255.0f));
	/** Draw inner ellipse **/ 
	BeginTextureMode(renderTexture);
	ClearBackground(BLANK);
	DrawEllipse(position.x, position.y, radii.x - strokeWidth / 2.0f, radii.y - strokeWidth / 2.0f, fillColor.pureColor());
	EndTextureMode();
	DrawTextureRec(renderTexture.texture, { 0, 0, (float)renderTexture.texture.width, (float)-renderTexture.texture.height }, { 0, 0 },
		ColorAlpha(WHITE, (float)fillColor.a / 255.0f));
}

/*
* @brief Draw a circle
*/
void Renderer::drawCircle(Circle *element, RenderTexture2D renderTexture) {
	drawEllipse(static_cast<Ellipse*>(element), renderTexture);
}

/*
* @brief Draw a line
*/
void Renderer::drawLine(Line *element, RenderTexture2D renderTexture) {
	Vector2D<float> position = element->getPosition();
	Vector2D<float> endPosition = element->getEndPosition();
	SVGColor strokeColor = element->getStrokeColor();
	float strokeWidth = element->getStrokeWidth();

	DrawLineEx({ position.x, position.y }, { endPosition.x, endPosition.y }, strokeWidth, strokeColor.operator Color());
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
void Renderer::drawText(Text *element, Font font, float offset) {
	std::string data = element->getData();
	Vector2D<float> position = element->getPosition();
	float fontSize = element->getFontSize();
	SVGColor fillColor = element->getFillColor();
	std::string textAnchor = element->getTextAnchor();


	float actualY = position.y - fontSize + offset;
	float actualX = position.x;
	Vector2 dataSize = MeasureTextEx(font, &data[0], fontSize, 1.0);
	element->setDataSize(dataSize);

	if (textAnchor == "middle" || textAnchor == "end") {
		if (textAnchor == "middle") dataSize.x /= 2.0f;
		actualX -= dataSize.x;
	}
	DrawTextEx(font, &data[0], { position.x, actualY }, fontSize, 1, fillColor.operator Color());
}

/*
* @brief Draw path
*/
void Renderer::drawPath(Path *element) {

}
