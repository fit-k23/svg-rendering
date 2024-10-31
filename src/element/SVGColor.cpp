#include "SVGColor.h"
#include <map>
#include <string>

/*
* @brief Default constructor
* @note If nothing is defined => no color
* transparent <=> a = 0
*/
SVGColor::SVGColor() : r(0), g(0), b(0), a(0) {}

/*
* @brief Parameterized constructor with alpha
*/
SVGColor::SVGColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {}

/*
* @brief Parameterized constructor without alpha
*/
SVGColor::SVGColor(unsigned char r, unsigned char g, unsigned char b)  {
	this->r=r;
	this->g=g;
	this->b=b;
	this->a=255;
}

/*
* @brief Parameterized constructor (string-type)
* @param string format
*/
std::map<std::string, int> m;
SVGColor::SVGColor(std::string param) {
	r = 0;
	g = 0;
	b = 0;
	a = 255;
	if (param[0] == '#') {
		/*
		for (int i = 1; i < 7; i++) {
			if ((param[i] >= '0' && param[i] <= '9') || (param[i] >= 'a' && param[i] <= 'f') || 
				(param[i] >= 'A' && param[i] <= 'F')) 
				continue;
			SVGColor();
			std::cout << "Wrong string input to SVG Color \n";
			return;
		}
		*/
		/// TODO: Format is #RRGGBB
		if (param.length() == 7) {
			if (!param.substr(1, 2).empty()) r = std::stoi(param.substr(1, 2), nullptr, 16);
			if (!param.substr(3, 2).empty()) g = std::stoi(param.substr(3, 2), nullptr, 16);
			if (!param.substr(5, 2).empty()) b = std::stoi(param.substr(5, 2), nullptr, 16);
		}
	} else {
		for (int i = 0; param[i]; i++) if (param[i] <= 'Z' && param[i] >= 'A') param[i] -= 32;
		auto it = LABELED_COLOR.find(param);
		/// Format is rgb(r, g, b, (a))
		if (it!=LABELED_COLOR.end()) {
			SVGColor lc = it->second;
			r = lc.r;
			g = lc.g;
			b = lc.b;
		}
		else std::cout<<"String input does not start with '#' nor supported\n";
	}
	a = 255;
}

//hsl
SVGColor::SVGColor(int h, int s, int l) {
	float r, g, b;
	float s_f = s / 100.0f;
	float l_f = l / 100.0f;

	auto hueToRgb = [](float p, float q, float t) {
		if (t < 0.0f) t += 1.0f;
		if (t > 1.0f) t -= 1.0f;
		if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
		if (t < 1.0f / 2.0f) return q;
		if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
		return p;
	};

	if (s == 0) {
		r = g = b = l_f; // achromatic
	} else {
		float q = l_f < 0.5 ? l_f * (1.0f + s_f) : l_f + s_f - l_f * s_f;
		float p = 2.0f * l_f - q;
		r = hueToRgb(p, q, h / 360.0f + 1.0f / 3.0f);
		g = hueToRgb(p, q, h / 360.0f);
		b = hueToRgb(p, q, h / 360.0f - 1.0f / 3.0f);
	}

	this->r = static_cast<unsigned char>(r * 255);
	this->g = static_cast<unsigned char>(g * 255);
	this->b = static_cast<unsigned char>(b * 255);

	this->a = 255;
}
//hsla
SVGColor::SVGColor(int h, int s, int l, int a) : SVGColor(h, s, l) {
	this->a = static_cast<unsigned char>(a);
}
Color SVGColor::getRaylibColor() const {
	return {this->r, this->g, this->b, this->a};
}

