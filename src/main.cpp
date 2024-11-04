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
	
	/// Temporary comment. Only for debugging
	//std::cout << (int)v.size() << '\n';
	//for (auto & i : v)
	//	i->dbg();

	/// TODO: If no viewport specifed, gain information from bounding box of all
	/// shapes to get default viewport that display all elements
	if (parser.getViewPort().x == 0 && parser.getViewPort().y == 0) {
		Vector2D<float> newViewPort = Vector2D<float>();
		std::cout << "New viewport\n";
		for (int i = 0; i < (int)v.size(); ++i) {
			if (v[i]->getTypeName() == ElementType::Text) {
				static_cast<Text*>(v[i])->setDataSize();
			}
			std::pair<Vector2D<float>, Vector2D<float>> boundingBox = v[i]->getBoundingBox(); 
			newViewPort.x = std::max(newViewPort.x, boundingBox.second.x);
			newViewPort.y = std::max(newViewPort.y, boundingBox.second.y);
			std::cout << boundingBox.first.x << " " << boundingBox.first.y << " " << boundingBox.second.x << " " << boundingBox.second.y << '\n';
		}
		parser.setViewPort(newViewPort);
	}

	Vector2D<float> screenSize = parser.getViewPort();
	std::cout << "screenx screeny = " << screenSize.x << " " << screenSize.y << '\n';
	Renderer render(parser.getViewPort(), v, screenSize);
	render.draw();

//	Renderer render({900, 700}, {}, {900, 700});
//
////	render.addShape(new Ellipse({100, 50}, SVG_AQUA.alpha(200), SVG_BLUE.alpha(150), 100.0f, {150,300}));
//	Rect *rect = new Rect({100, 50}, SVG_BLACK.alpha(255), SVG_GREEN.alpha(220), 40, 500.0f, 350.0f, {50,20});
//	render.addShape(rect);
//	render.draw();
	return 0;
}
