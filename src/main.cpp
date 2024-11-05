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

// Function to draw a triangle given three vertices
void DrawFilledTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color) {
	DrawTriangle(v1, v2, v3, color);
}

float getSlope(const std::pair<Vector2, Vector2> &line) {
	return (float)(line.second.y - line.first.y) / (float)(line.second.x - line.first.x);
}

int coef(std::pair<Vector2, Vector2> line, float yInd) {
	int ret = 0;
	/// TODO: down
	if (line.first.y <= yInd && line.second.y >= yInd) ret = -1;
	/// TODO: up
	if (line.first.y >= yInd && line.second.y <= yInd) ret = 1;
	return ret;
}

//points = "850,75 958,137 958,262 850,325 742,262 742,137"
//points = "350,75 379,161 469,161 397,215 423,301 350,250 277,301 303,215 231,161 321,161" 
	//775, 183
	//859, 1000
	//170, 60
	//911, 407
	//520, 134
	//392, 408
	//37, 454

int main() {
	//std::vector<std::pair<Vector2, Vector2>> lines;
	////lines.push_back({ {200,200}, {300,400} });
	////lines.push_back({ {300,400}, {100,300} });
	////lines.push_back({ {100,300}, {140,270} });
	////lines.push_back({ {140,270}, {160,420} });
	////lines.push_back({ {160,420}, {300,280} });
	////lines.push_back({ {300,280}, {130,400} });
	////lines.push_back({ {130,400}, {200,200} });
	//
	////lines.push_back({ {850,75}, {958,137} });
	////lines.push_back({ {958,137}, {958,262} });
	////lines.push_back({ {958,262}, {850,325} });
	////lines.push_back({ {850,325}, {742,262} });
	////lines.push_back({ {742,262}, {742,137} });
	////lines.push_back({ {742,137}, {850,75} });
	//
	//lines.push_back({ {775,183}, {859,1000} });
	//lines.push_back({ {859,1000}, {170,60} });
	//lines.push_back({ {170,60}, {911,407} });
	//lines.push_back({ {911,407}, {520,134} });
	//lines.push_back({ {520,134}, {392,408} });
	//lines.push_back({ {392,408}, {37,454} });
	//lines.push_back({ {37,454}, {775,183} });


	///// TODO: find ymin, ymax
	//float ymin = 1000, ymax = -1;
	//for (int i = 0; i < (int)lines.size(); ++i) {
	//	ymin = std::min(ymin, std::min(lines[i].first.y, lines[i].second.y));
	//	ymax = std::max(ymax, std::max(lines[i].first.y, lines[i].second.y));
	//}

	//InitWindow(1000, 1050, "test");
	//SetTargetFPS(60);
	//
	//while (!WindowShouldClose()) {
	//	BeginDrawing();
	//	ClearBackground(WHITE);
	//	for (int i = 0; i < (int)lines.size(); ++i) {
	//		Vector2 sta = lines[i].first;
	//		Vector2 fin = lines[i].second;
	//		DrawLineV(sta, fin, BLUE);
	//	}
	//	/// TODO: Fill
	//	for (float yInd = ymax; yInd >= ymin; yInd -= 0.005f) {
	//		std::vector<std::pair<float, int>> intersects = {};
	//		/// TODO: Find all intersections within polygon edges
	//		for (int i = 0; i < (int)lines.size(); ++i) {
	//			if (lines[i].second.y == lines[i].first.y) continue;
	//			/// TODO: perpendicular case
	//			if (lines[i].second.x == lines[i].first.x) {
	//				/// TODO: perpendicular and has no intersects
	//				if (std::min(lines[i].first.y, lines[i].second.y) > yInd || std::max(lines[i].first.y, lines[i].second.y) < yInd) continue;
	//				/// TODO: Intersect point is (that x of the line, yInd)
	//				intersects.push_back({ lines[i].first.x, coef(lines[i], yInd) });
	//				continue;
	//			}
	//			float slope = getSlope(lines[i]);
	//			if (slope == 0) continue;
	//			Vector2 sta = lines[i].first;
	//			Vector2 fin = lines[i].second;
	//			float b = sta.y - slope * sta.x;
	//			float intersectX = (yInd - b) / slope;
	//			/// If intersect lies within the line (since it can also be outside)
	//			if (intersectX >= std::min(sta.x, fin.x) && intersectX <= std::max(sta.x, fin.x)) {
	//				/// TODO: has an intersect
	//				intersects.push_back({ intersectX, coef(lines[i], yInd)});
	//				//std::cout << yInd << " intersects line " << i << " at " << intersectX << '\n';
	//			}
	//		}
	//		/// TODO: sort intersect based on x coordinate
	//		std::sort(intersects.begin(), intersects.end(), [](std::pair<float, int> fi, std::pair<float, int> se) {
	//			return fi.first < se.first;
	//		});

	//		/*std::cout << "yInd = " << yInd << '\n';
	//		std::cout << "intersect: ";
	//		for (int i = 0; i < (int)intersects.size(); ++i) std::cout << intersects[i].first << " ";
	//		std::cout << '\n';*/

	//		/// TODO: traverse each coord and fill with non-zero rule
	//		int up = 0, down = 0;
	//		for (int i = 0; i < (int)intersects.size(); ++i) {
	//			float x = intersects[i].first;
	//			int coef = intersects[i].second;
	//			
	//			if (up != down && i > 0) {
	//				DrawLineV(Vector2{ intersects[i - 1].first, yInd }, Vector2{ x, yInd }, BLUE);
	//			}

	//			if (coef == 1) ++up;
	//			else if (coef == -1) ++down;
	//		}
	//		//DrawLineV(Vector2{ 0.0f, yInd }, Vector2{ 4000f, yInd }, BLUE);
	//		//if (yInd <= 400.0f) break;
	//	}
	//	EndDrawing();
	//	//break;
	//}

	/*int n;
	std::cin >> n;*/
	//CloseWindow();

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
		//std::cout << "New viewport\n";
		for (int i = 0; i < (int)v.size(); ++i) {
			if (v[i]->getTypeName() == ElementType::Text) {
				static_cast<Text*>(v[i])->setDataSize();
			}
			std::pair<Vector2D<float>, Vector2D<float>> boundingBox = v[i]->getBoundingBox(); 
			newViewPort.x = std::max(newViewPort.x, boundingBox.second.x);
			newViewPort.y = std::max(newViewPort.y, boundingBox.second.y);
			//std::cout << boundingBox.first.x << " " << boundingBox.first.y << " " << boundingBox.second.x << " " << boundingBox.second.y << '\n';
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
