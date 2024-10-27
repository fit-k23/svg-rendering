#include "SVGColor.h"
#include <map>
#include <string>
SVGColor::SVGColor() : r(0), g(0), b(0), a(0) {}

SVGColor::SVGColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {}

SVGColor::SVGColor(unsigned char r, unsigned char g, unsigned char b) : SVGColor(r, g, b, 255) {}

std::map<std::string, int> m;

SVGColor::SVGColor(std::string param) {
	if (param[0] == '#') {
		for (int i = 1; i < 7; i++) {
			if (((param[i] >= '0' && param[i] <= '9') || (param[i] >= 'a' && param[i] <= 'f')) || (
					param[i] >= 'A' && param[i] <= 'F')) {
				continue;
					}
			SVGColor();
			std::cout << "Wrong string input to SVG Color \n";
			return;
		}
		// Assuming the format is #RRGGBB
		if (param.length() == 7) {
			if (!param.substr(1, 2).empty())
				r = std::stoi(param.substr(1, 2), nullptr, 16);
			if (!param.substr(3, 2).empty())
				g = std::stoi(param.substr(3, 2), nullptr, 16);
			if (!param.substr(5, 2).empty())
				b = std::stoi(param.substr(5, 2), nullptr, 16);
		}
	} else {
		for (int i = 0; param[i]; i++) if (param[i] <= 'Z' && param[i] >= 'A') param[i] -= 32;
		auto it = LABELED_COLOR.find(param);
		if (it!=LABELED_COLOR.end()) {
			SVGColor lc = it->second;
			r = lc.r;
			g = lc.g;
			b = lc.b;
		}
		std::cout<<"String input does not start with '#' nor supported\n";
	}
	a = 255;
}

