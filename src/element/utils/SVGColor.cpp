#include "SVGColor.h"

const static std::map<std::string, SVGColor> LABELED_COLOR = {
	{"aliceblue",            SVG_ALICEBLUE},
	{"antiquewhite",         SVG_ANTIQUEWHITE},
	{"aqua",                 SVG_AQUA},
	{"aquamarine",           SVG_AQUAMARINE},
	{"azure",                SVG_AZURE},
	{"beige",                SVG_BEIGE},
	{"bisque",               SVG_BISQUE},
	{"black",                SVG_BLACK},
	{"blanchedalmond",       SVG_BLANCHEDALMOND},
	{"blue",                 SVG_BLUE},
	{"blueviolet",           SVG_BLUEVIOLET},
	{"brown",                SVG_BROWN},
	{"burlywood",            SVG_BURLYWOOD},
	{"cadetblue",            SVG_CADETBLUE},
	{"chartreuse",           SVG_CHARTREUSE},
	{"chocolate",            SVG_CHOCOLATE},
	{"coral",                SVG_CORAL},
	{"cornflowerblue",       SVG_CORNFLOWERBLUE},
	{"cornsilk",             SVG_CORNSILK},
	{"crimson",              SVG_CRIMSON},
	{"cyan",                 SVG_CYAN},
	{"darkblue",             SVG_DARKBLUE},
	{"darkcyan",             SVG_DARKCYAN},
	{"darkgoldenrod",        SVG_DARKGOLDENROD},
	{"darkgray",             SVG_DARKGRAY},
	{"darkgreen",            SVG_DARKGREEN},
	{"darkgrey",             SVG_DARKGREY},
	{"darkkhaki",            SVG_DARKKHAKI},
	{"darkmagenta",          SVG_DARKMAGENTA},
	{"darkolivegreen",       SVG_DARKOLIVEGREEN},
	{"darkorange",           SVG_DARKORANGE},
	{"darkorchid",           SVG_DARKORCHID},
	{"darkred",              SVG_DARKRED},
	{"darksalmon",           SVG_DARKSALMON},
	{"darkseagreen",         SVG_DARKSEAGREEN},
	{"darkslateblue",        SVG_DARKSLATEBLUE},
	{"darkslategray",        SVG_DARKSLATEGRAY},
	{"darkslategrey",        SVG_DARKSLATEGREY},
	{"darkturquoise",        SVG_DARKTURQUOISE},
	{"darkviolet",           SVG_DARKVIOLET},
	{"deeppink",             SVG_DEEPPINK},
	{"deepskyblue",          SVG_DEEPSKYBLUE},
	{"dimgray",              SVG_DIMGRAY},
	{"dimgrey",              SVG_DIMGREY},
	{"dodgerblue",           SVG_DODGERBLUE},
	{"firebrick",            SVG_FIREBRICK},
	{"floralwhite",          SVG_FLORALWHITE},
	{"forestgreen",          SVG_FORESTGREEN},
	{"fuchsia",              SVG_FUCHSIA},
	{"gainsboro",            SVG_GAINSBORO},
	{"ghostwhite",           SVG_GHOSTWHITE},
	{"gold",                 SVG_GOLD},
	{"goldenrod",            SVG_GOLDENROD},
	{"gray",                 SVG_GRAY},
	{"grey",                 SVG_GREY},
	{"green",                SVG_GREEN},
	{"greenyellow",          SVG_GREENYELLOW},
	{"honeydew",             SVG_HONEYDEW},
	{"hotpink",              SVG_HOTPINK},
	{"indianred",            SVG_INDIANRED},
	{"indigo",               SVG_INDIGO},
	{"ivory",                SVG_IVORY},
	{"khaki",                SVG_KHAKI},
	{"lavender",             SVG_LAVENDER},
	{"lavenderblush",        SVG_LAVENDERBLUSH},
	{"lawngreen",            SVG_LAWNGREEN},
	{"lemonchiffon",         SVG_LEMONCHIFFON},
	{"lightblue",            SVG_LIGHTBLUE},
	{"lightcoral",           SVG_LIGHTCORAL},
	{"lightcyan",            SVG_LIGHTCYAN},
	{"lightgoldenrodyellow", SVG_LIGHTGOLDENRODYELLOW},
	{"lightgray",            SVG_LIGHTGRAY},
	{"lightgreen",           SVG_LIGHTGREEN},
	{"lightgrey",            SVG_LIGHTGREY},
	{"lightpink",            SVG_LIGHTPINK},
	{"lightsalmon",          SVG_LIGHTSALMON},
	{"lightseagreen",        SVG_LIGHTSEAGREEN},
	{"lightskyblue",         SVG_LIGHTSKYBLUE},
	{"lightslategray",       SVG_LIGHTSLATEGRAY},
	{"lightslategrey",       SVG_LIGHTSLATEGREY},
	{"lightsteelblue",       SVG_LIGHTSTEELBLUE},
	{"lightyellow",          SVG_LIGHTYELLOW},
	{"lime",                 SVG_LIME},
	{"limegreen",            SVG_LIMEGREEN},
	{"linen",                SVG_LINEN},
	{"magenta",              SVG_MAGENTA},
	{"maroon",               SVG_MAROON},
	{"mediumaquamarine",     SVG_MEDIUMAQUAMARINE},
	{"mediumblue",           SVG_MEDIUMBLUE},
	{"mediumorchid",         SVG_MEDIUMORCHID},
	{"mediumpurple",         SVG_MEDIUMPURPLE},
	{"mediumseagreen",       SVG_MEDIUMSEAGREEN},
	{"mediumslateblue",      SVG_MEDIUMSLATEBLUE},
	{"mediumspringgreen",    SVG_MEDIUMSPRINGGREEN},
	{"mediumturquoise",      SVG_MEDIUMTURQUOISE},
	{"mediumvioletred",      SVG_MEDIUMVIOLETRED},
	{"midnightblue",         SVG_MIDNIGHTBLUE},
	{"mintcream",            SVG_MINTCREAM},
	{"mistyrose",            SVG_MISTYROSE},
	{"moccasin",             SVG_MOCCASIN},
	{"navajowhite",          SVG_NAVAJOWHITE},
	{"navy",                 SVG_NAVY},
	{"oldlace",              SVG_OLDLACE},
	{"olive",                SVG_OLIVE},
	{"olivedrab",            SVG_OLIVEDRAB},
	{"orange",               SVG_ORANGE},
	{"orangered",            SVG_ORANGERED},
	{"orchid",               SVG_ORCHID},
	{"palegoldenrod",        SVG_PALEGOLDENROD},
	{"palegreen",            SVG_PALEGREEN},
	{"paleturquoise",        SVG_PALETURQUOISE},
	{"palevioletred",        SVG_PALEVIOLETRED},
	{"papayawhip",           SVG_PAPAYAWHIP},
	{"peachpuff",            SVG_PEACHPUFF},
	{"peru",                 SVG_PERU},
	{"pink",                 SVG_PINK},
	{"plum",                 SVG_PLUM},
	{"powderblue",           SVG_POWDERBLUE},
	{"purple",               SVG_PURPLE},
	{"red",                  SVG_RED},
	{"rosybrown",            SVG_ROSYBROWN},
	{"royalblue",            SVG_ROYALBLUE},
	{"saddlebrown",          SVG_SADDLEBROWN},
	{"salmon",               SVG_SALMON},
	{"sandybrown",           SVG_SANDYBROWN},
	{"seagreen",             SVG_SEAGREEN},
	{"seashell",             SVG_SEASHELL},
	{"sienna",               SVG_SIENNA},
	{"silver",               SVG_SILVER},
	{"skyblue",              SVG_SKYBLUE},
	{"slateblue",            SVG_SLATEBLUE},
	{"slategray",            SVG_SLATEGRAY},
	{"slategrey",            SVG_SLATEGREY},
	{"snow",                 SVG_SNOW},
	{"springgreen",          SVG_SPRINGGREEN},
	{"steelblue",            SVG_STEELBLUE},
	{"tan",                  SVG_TAN},
	{"teal",                 SVG_TEAL},
	{"thistle",              SVG_THISTLE},
	{"tomato",               SVG_TOMATO},
	{"turquoise",            SVG_TURQUOISE},
	{"violet",               SVG_VIOLET},
	{"wheat",                SVG_WHEAT},
	{"white",                SVG_WHITE},
	{"whitesmoke",           SVG_WHITESMOKE},
	{"yellow",               SVG_YELLOW},
	{"yellowgreen",          SVG_YELLOWGREEN}
};

SVGColor::SVGColor() : r(0), g(0), b(0), a(0) {}

SVGColor::SVGColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) : r(_r), g(_g), b(_b), a(_a) {}

SVGColor::SVGColor(int _r, int _g, int _b, int _a) : r(_r), g(_g), b(_b), a(_a) {}

SVGColor::SVGColor(std::string param) {
	r = 0;
	g = 0;
	b = 0;
	a = 0;
	// #RRGGBB or #RGB
	if (param[0] == '#') {
		unsigned int pSize = param.size();
		if (pSize == 4) {
			std::string newParam = "#";
			for (int i = 1; i < 4; ++i) {
				newParam += param[i];
				newParam += param[i];
			}
			param = newParam;
			pSize = param.size();
		}

		if (pSize != 7 && pSize != 9) {
			return;
		}
		for (int i = 1; i < pSize; ++i) {
			if (((param[i] >= '0' && param[i] <= '9') || (param[i] >= 'a' && param[i] <= 'f')) || (param[i] >= 'A' && param[i] <= 'F')) {
				continue;
			}
			std::cout << "Wrong string input to SVG Color \n";
			return;
		}
		if (!param.substr(1, 2).empty())
			r = std::stoi(param.substr(1, 2), nullptr, 16);
		if (!param.substr(3, 2).empty())
			g = std::stoi(param.substr(3, 2), nullptr, 16);
		if (!param.substr(5, 2).empty())
			b = std::stoi(param.substr(5, 2), nullptr, 16);
		if (pSize == 9 && !param.substr(7, 2).empty()) // // Assuming the format is #RRGGBBAA
			a = std::stoi(param.substr(7, 2), nullptr, 16);
	} else {
		//Assuming the form of string input is rgb(r,g,b)
		bool isPercent[3] = { false, false, false };
		int idPercent = 0;
		if (param[0] == 'r' && (param[1] == 'g' && param[2] == 'b')) {
			for (char & i : param) {
				if (i == 'r' || i == 'g' || i == 'b' || i == '(' || i == ')' || i == ',' || i == '%') {
					if (i == '%') isPercent[idPercent++] = true;
					i = ' ';
				}
			}
			std::stringstream buffer(param);
			float R, G, B;
			buffer >> R >> G >> B;
			r = (unsigned char) R;
			if (isPercent[0]) r = (unsigned char) (255.0f * (R / 100.0f));
			g = (unsigned char) G;
			if (isPercent[1]) g = (unsigned char) (255.0f * (G / 100.0f));
			b = (unsigned char) B;
			if (isPercent[2]) b = (unsigned char) (255.0f * (B / 100.0f));
		} else {
			//Assuming the string input is color name
			for (int i = 0; param[i]; i++) if (param[i] <= 'Z' && param[i] >= 'A') param[i] -= 32;
			auto it = LABELED_COLOR.find(param);
			if (it != LABELED_COLOR.end()) {
				SVGColor lc = it->second;
				r = lc.r;
				g = lc.g;
				b = lc.b;
				a = lc.a;
			} else {
				std::cout << "String input does not start with '#' nor supported\n";
			}
		}
	}
}

SVGColor::operator Gdiplus::Color() const {
	return Gdiplus::Color{a, r, g, b};
}

SVGColor::SVGColor(const SVGColor &other) = default;

SVGColor SVGColor::alpha(unsigned char _a) const {
	return {r, g, b, _a};
}

SVGColor SVGColor::fromHSL(int h, int s, int l, int _a) {
	float _r{}, _g{}, _b{};

	float c = (1.0f - fabsf(2.0f * (float) l - 1.0f)) * (float) s; // Chroma
	float x = c * (1.0f - fabsf(fmodf(static_cast<float> (h) / 60.0f, 2) - 1.0f));
	float m = (float) l - c / 2.0f;

	if (h >= 0 && h < 60) {
		_r = c;
		_g = x;
	} else if (h >= 60 && h < 120) {
		_r = x;
		_g = c;
	} else if (h >= 120 && h < 180) {
		_g = c;
		_b = x;
	} else if (h >= 180 && h < 240) {
		_g = x;
		_b = c;
	} else if (h >= 240 && h < 300) {
		_r = x;
		_b = c;
	} else {
		_r = c;
		_b = x;
	}

	return {static_cast<unsigned char>((_r + m) * 255), static_cast<unsigned char>((_g + m) * 255), static_cast<unsigned char>((_b + m) * 255), static_cast<unsigned char>(_a),};
}

void SVGColor::output() const {
	std::cout << "{" << (int) r << " " << (int) g << " " << (int) b << " " << (int) a << "}";
}

SVGColor &SVGColor::operator=(const SVGColor &other) {
	if (this == &other) return *this;
	r = other.r;
	g = other.g;
	b = other.b;
	a = other.a;
	return *this;
}

SVGColor SVGColor::alpha(float _a) const { return alpha((unsigned char) (_a * 255.f)); }

SVGColor SVGColor::blend(const SVGColor &other) const {
	return {(other.r + r) / 2, (other.g + g) / 2, (other.b + b) / 2, (other.a + a) / 2};
}

SVGColor SVGColor::alpha(int _a) const {
	return alpha(static_cast<unsigned char>(_a));
}
