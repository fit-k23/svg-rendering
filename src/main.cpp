#include <iostream>
#include "conio.h"
#include "api/XMLParser.h"
#include "api/Renderer.h"

/// Raylib
#include "../lib/raylib/raylib.h"
#include "../lib/raylib/rlgl.h"
#include "../lib/raylib/raymath.h"
/// Raylib Ex
#include "utils/Raylibex.h"

#include "api/Renderer.h"

//void test() {
//	InitWindow(900, 900);
//	Vector2D<float> position = { 500, 100 };
//	Vector2D<float> radii = { 100, 50 };
//	SVGColor fillColor = {};
//	SVGColor strokeColor = element->getStrokeColor();
//	float strokeWidth = element->getStrokeWidth();
//	// Draw outer outline and inner outline
//	RenderTexture2D renderTexture2 = RenderTexturePool::getRenderTexture(screenSize.x, screenSize.y);
//	BeginTextureMode(renderTexture2);
//	ClearBackground(BLANK);
//	BeginBlendMode(BLEND_SUBTRACT_COLORS);
//	DrawEllipse(position.x, position.y, radii.x + strokeWidth / 2.0f, radii.y + strokeWidth / 2.0f, BLUE);
//	DrawEllipse(position.x, position.y, radii.x - strokeWidth / 2.0f, radii.y - strokeWidth / 2.0f, BLUE);
//	EndBlendMode();
//	EndTextureMode();
//	DrawTextureRec(renderTexture2.texture, { 0, 0, (float)renderTexture2.texture.width, (float)renderTexture2.texture.height }, { 0, 0 },
//		ColorAlpha(WHITE, 1));
//}

int main() {
	XMLParser parser;
	std::vector<Element*> v;
	parser.traverseXML("sample.svg", v);
	std::cout << (int)v.size() << '\n';

	for (auto & i : v)
		i->dbg();

	Renderer render(parser.getViewPort(), v);
	render.draw();

//	Renderer render({900, 700}, {}, {900, 700});
//
////	render.addShape(new Ellipse({100, 50}, SVG_AQUA.alpha(200), SVG_BLUE.alpha(150), 100.0f, {150,300}));
//	Rect *rect = new Rect({100, 50}, SVG_BLACK.alpha(255), SVG_GREEN.alpha(220), 40, 500.0f, 350.0f, {50,20});
//	render.addShape(rect);
//	render.draw();
	return 0;
}
