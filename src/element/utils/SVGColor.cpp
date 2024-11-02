#include "SVGColor.h"
#include <sstream>
SVGColor::SVGColor() : r(0), g(0), b(0), a(0) {}

SVGColor::SVGColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {}

SVGColor::SVGColor(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b), a(255) {}

SVGColor::SVGColor(std::string param) {
	if (param[0] == '#') {
		for (int i = 1; i < 7; i++) {
			if (((param[i] >= '0' && param[i] <= '9') || (param[i] >= 'a' && param[i] <= 'f')) || (param[i] >= 'A' && param[i] <= 'F')) {
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
		// Assuming the format is #RRGGBBAA
		else if (param.length() == 9) {
			if (!param.substr(1, 2).empty())
				r = std::stoi(param.substr(1, 2), nullptr, 16);
			if (!param.substr(3, 2).empty())
				g = std::stoi(param.substr(3, 2), nullptr, 16);
			if (!param.substr(5, 2).empty())
				b = std::stoi(param.substr(5, 2), nullptr, 16);
			if (!param.substr(7, 2).empty())
				a = std::stoi(param.substr(7, 2), nullptr, 16);
		}
	} else {
		 //Assuming the form of string input is rgb(r,g,b)
		if (param[0]==r && (param[1]==g && param[2]==b)) {
			std::stringstream buffer(param);
			char temp;
			for (int i=0;i<4;i++) {
				buffer >> temp;
			}
			buffer>>r>>temp>>g>>temp>>b;
		}
		else {
			//Assuming the string input is color name
			for (int i = 0; param[i]; i++) if (param[i] <= 'Z' && param[i] >= 'A') param[i] -= 32;
			auto it = LABELED_COLOR.find(param);
			if (it != LABELED_COLOR.end()) {
				SVGColor lc = it->second;
				r = lc.r;
				g = lc.g;
				b = lc.b;
				a = 255;
			}
			std::cout << "String input does not start with '#' nor supported\n";
		}
	}
}

//hsl
SVGColor::SVGColor(int h, int s, int l) {
	float _r{}, _g{}, _b{};

	float c = (1.0f - fabsf(2.0f * l - 1.0f)) * s; // Chroma
	float x = c * (1.0f - fabsf(fmodf(static_cast<float> (h) / 60.0f, 2) - 1.0f));
	float m = l - c / 2.0f;

	if(h >= 0 && h < 60) {
		_r = c;
		_g = x;
	} else if(h >= 60 && h < 120) {
		_r = x;
		_g = c;
	} else if(h >= 120 && h < 180) {
		_g = c;
		_b = x;
	} else if(h >= 180 && h < 240) {
		_g = x;
		_b = c;
	} else if(h >= 240 && h < 300) {
		_r = x;
		_b = c;
	} else {
		_r = c;
		_b = x;
	}

	r = static_cast<unsigned char>((_r + m) * 255);
	g = static_cast<unsigned char>((_g + m) * 255);
	b = static_cast<unsigned char>((_b + m) * 255);
	a = 255;
}



//hsla
SVGColor::SVGColor(int h, int s, int l, int a) : SVGColor(h, s, l) {
	this->a = static_cast<unsigned char>(a);
}

SVGColor::operator Color() const {
	return Color{r, g, b, a};
}

SVGColor::SVGColor(const SVGColor &other) : r(other.r), g(other.g), b(other.b), a(other.b) {}

