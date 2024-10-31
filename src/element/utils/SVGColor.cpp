#include "SVGColor.h"
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
	} else {
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


//hsl
SVGColor::SVGColor(int h, int s, int l) {
	float _r, _g, _b;
	float s_f = static_cast<float> (s) / 100.0f;
	float l_f = static_cast<float> (l) / 100.0f;

	auto hueToRgb = [](float p, float q, float t) {
		if (t < 0.0f) t += 1.0f;
		if (t > 1.0f) t -= 1.0f;
		if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
		if (t < 1.0f / 2.0f) return q;
		if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
		return p;
	};

	if (s == 0) {
		_r = _g = _b = l_f; // achromatic
	} else {
		float q = l_f < 0.5 ? l_f * (1.0f + s_f) : l_f + s_f - l_f * s_f;
		float p = 2.0f * l_f - q;
		float hf = static_cast<float> (h) / 360.f;
		_r = hueToRgb(p, q, hf + 1.0f / 3.0f);
		_g = hueToRgb(p, q, hf);
		_b = hueToRgb(p, q, hf - 1.0f / 3.0f);
	}

	this->r = static_cast<unsigned char>(_r * 255);
	this->g = static_cast<unsigned char>(_g * 255);
	this->b = static_cast<unsigned char>(_b * 255);
	this->a = 255;
}



//hsla
SVGColor::SVGColor(int h, int s, int l, int a) : SVGColor(h, s, l) {
	this->a = static_cast<unsigned char>(a);
}

SVGColor::operator Color() const {
	return Color{r, g, b, a};
}

#import <cmath>
SVGColor HSLToRGB(int h, float s, float l) {
	float r{}, g{}, b{};

	float c = (1.0f - fabsf(2.0f * l - 1.0f)) * s; // Chroma
	float x = c * (1.0f - fabsf(fmodf(static_cast<float> (h) / 60.0f, 2) - 1.0f));
	float m = l - c / 2.0f;

	if(h >= 0 && h < 60) {
		r = c;
		g = x;
	} else if(h >= 60 && h < 120) {
		r = x;
		g = c;
	} else if(h >= 120 && h < 180) {
		g = c;
		b = x;
	} else if(h >= 180 && h < 240) {
		g = x;
		b = c;
	} else if(h >= 240 && h < 300) {
		r = x;
		b = c;
	} else {
		r = c;
		b = x;
	}

	SVGColor rgb;
	rgb.r = static_cast<unsigned char>((r + m) * 255);
	rgb.g = static_cast<unsigned char>((g + m) * 255);
	rgb.b = static_cast<unsigned char>((b + m) * 255);

	return rgb;
}

SVGColor::SVGColor(const SVGColor &other) : r(other.r), g(other.g), b(other.b), a(other.b) {}

