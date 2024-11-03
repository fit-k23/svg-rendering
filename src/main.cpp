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

int main() {
	XMLParser parser;
	std::vector<Element*> v;
	parser.traverseXML("sample.svg", v);
	std::cout << (int)v.size() << '\n';

	for (auto & i : v)
		i->dbg();

	Renderer render(parser.getViewPort(), v, {900, 700});
	render.draw();

//	Renderer render({900, 700}, {}, {900, 700});
//
////	render.addShape(new Ellipse({100, 50}, SVG_AQUA.alpha(200), SVG_BLUE.alpha(150), 100.0f, {150,300}));
//	Rect *rect = new Rect({100, 50}, SVG_BLACK.alpha(255), SVG_GREEN.alpha(220), 40, 500.0f, 350.0f, {50,20});
//	render.addShape(rect);
//	render.draw();
	return 0;
}
