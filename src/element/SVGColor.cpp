#include "SVGColor.h"

SVGColor::SVGColor() {
	r = 0;
	g = 0;
	b = 0;
	a = 0;
}

SVGColor::SVGColor(const std::string &param) {
	for (int i = 1; i < 7; i++) {
		if (((param[i] >= '0' && param[i] <= '9') || (param[i] >= 'a' && param[i] <= 'f')) || (
			    param[i] >= 'A' && param[i] <= 'F')) {
			continue;
		}
		SVGColor();
		std::cout << "Wrong string input to SVG Color \n";
		return;
	}
	if (param[0] == '#') {
		// Assuming the format is #RRGGBB
		if (param.length() == 7) {
			if (!param.substr(1, 2).empty())
				r = std::stoi(param.substr(1, 2), nullptr, 16);
			if (!param.substr(3, 2).empty())
				g = std::stoi(param.substr(3, 2), nullptr, 16);
			if (!param.substr(5, 2).empty())
				b = std::stoi(param.substr(5, 2), nullptr, 16);
		}
	}
	else {
		std::cout<<"String input does not start with '#'\n";
	}
	a = 255;
}
