#ifndef SVG_RENDERING_COLOR_H
#define SVG_RENDERING_COLOR_H

#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <map>

#include <objidl.h>
#include <gdiplus.h>

/**
 * @brief Supports reading SVG color and return Gdiplus::Color type
 * @note Can extract rgb, hex, percentage.
*/
class SVGColor{
public:
	unsigned char r, g, b, a;

	/** @brief Default constructor (transparent/none) */
	SVGColor(); // r,g,b = 0 -> black, a = 0 -> none
	SVGColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);

	SVGColor(int r, int g, int b, int a = 255);

	SVGColor(const SVGColor &other);

	SVGColor &operator=(const SVGColor &other);

	explicit SVGColor(std::string param);
	static SVGColor fromHSL(int h, int s, int l, int a = 255);

	operator Gdiplus::Color() const;

	void output() const;

	inline SVGColor alpha(unsigned char a) const;
	SVGColor alpha(int a) const;
	SVGColor alpha(float a) const;
	SVGColor sub(const SVGColor &other) const{
		return {(unsigned char) (other.r - r), (unsigned char) (other.g - g), (unsigned char) (other.b - b), (unsigned char) a};
	}

	SVGColor blend(const SVGColor &other) const;
	// Parameterized constructor
	// @param: fill the string format
	// @note: fill can be hex code, color name, rgb(..), rgba(...),
	// @note: hsl(...), hsla(...)

};

#define SVG_BLANK SVGColor(0, 0, 0, 0)
#define SVG_NONE SVGColor(0, 0, 0, 0)

#define SVG_ALICEBLUE SVGColor(240, 248, 255)
#define SVG_ANTIQUEWHITE SVGColor(250, 235, 215)
#define SVG_AQUA SVGColor(0, 255, 255)
#define SVG_AQUAMARINE SVGColor(127, 255, 212)
#define SVG_AZURE SVGColor(240, 255, 255)
#define SVG_BEIGE SVGColor(245, 245, 220)
#define SVG_BISQUE SVGColor(255, 228, 196)
#define SVG_BLACK SVGColor(0, 0, 0)
#define SVG_BLANCHEDALMOND SVGColor(255, 235, 205)
#define SVG_BLUE SVGColor(0, 0, 255)
#define SVG_BLUEVIOLET SVGColor(138, 43, 226)
#define SVG_BROWN SVGColor(165, 42, 42)
#define SVG_BURLYWOOD SVGColor(222, 184, 135)
#define SVG_CADETBLUE SVGColor(95, 158, 160)
#define SVG_CHARTREUSE SVGColor(127, 255, 0)
#define SVG_CHOCOLATE SVGColor(210, 105, 30)
#define SVG_CORAL SVGColor(255, 127, 80)
#define SVG_CORNFLOWERBLUE SVGColor(100, 149, 237)
#define SVG_CORNSILK SVGColor(255, 248, 220)
#define SVG_CRIMSON SVGColor(220, 20, 60)
#define SVG_CYAN SVGColor(0, 255, 255)
#define SVG_DARKBLUE SVGColor(0, 0, 139)
#define SVG_DARKCYAN SVGColor(0, 139, 139)
#define SVG_DARKGOLDENROD SVGColor(184, 134, 11)
#define SVG_DARKGRAY SVGColor(169, 169, 169)
#define SVG_DARKGREEN SVGColor(0, 100, 0)
#define SVG_DARKGREY SVGColor(169, 169, 169)
#define SVG_DARKKHAKI SVGColor(189, 183, 107)
#define SVG_DARKMAGENTA SVGColor(139, 0, 139)
#define SVG_DARKOLIVEGREEN SVGColor(85, 107, 47)
#define SVG_DARKORANGE SVGColor(255, 140, 0)
#define SVG_DARKORCHID SVGColor(153, 50, 204)
#define SVG_DARKRED SVGColor(139, 0, 0)
#define SVG_DARKSALMON SVGColor(233, 150, 122)
#define SVG_DARKSEAGREEN SVGColor(143, 188, 143)
#define SVG_DARKSLATEBLUE SVGColor(72, 61, 139)
#define SVG_DARKSLATEGRAY SVGColor(47, 79, 79)
#define SVG_DARKSLATEGREY SVGColor(47, 79, 79)
#define SVG_DARKTURQUOISE SVGColor(0, 206, 209)
#define SVG_DARKVIOLET SVGColor(148, 0, 211)
#define SVG_DEEPPINK SVGColor(255, 20, 147)
#define SVG_DEEPSKYBLUE SVGColor(0, 191, 255)
#define SVG_DIMGRAY SVGColor(105, 105, 105)
#define SVG_DIMGREY SVGColor(105, 105, 105)
#define SVG_DODGERBLUE SVGColor(30, 144, 255)
#define SVG_FIREBRICK SVGColor(178, 34, 34)
#define SVG_FLORALWHITE SVGColor(255, 250, 240)
#define SVG_FORESTGREEN SVGColor(34, 139, 34)
#define SVG_FUCHSIA SVGColor(255, 0, 255)
#define SVG_GAINSBORO SVGColor(220, 220, 220)
#define SVG_GHOSTWHITE SVGColor(248, 248, 255)
#define SVG_GOLD SVGColor(255, 215, 0)
#define SVG_GOLDENROD SVGColor(218, 165, 32)
#define SVG_GRAY SVGColor(128, 128, 128)
#define SVG_GREY SVGColor(128, 128, 128)
#define SVG_GREEN SVGColor(0, 128, 0)
#define SVG_GREENYELLOW SVGColor(173, 255, 47)
#define SVG_HONEYDEW SVGColor(240, 255, 240)
#define SVG_HOTPINK SVGColor(255, 105, 180)
#define SVG_INDIANRED SVGColor(205, 92, 92)
#define SVG_INDIGO SVGColor(75, 0, 130)
#define SVG_IVORY SVGColor(255, 255, 240)
#define SVG_KHAKI SVGColor(240, 230, 140)
#define SVG_LAVENDER SVGColor(230, 230, 250)
#define SVG_LAVENDERBLUSH SVGColor(255, 240, 245)
#define SVG_LAWNGREEN SVGColor(124, 252, 0)
#define SVG_LEMONCHIFFON SVGColor(255, 250, 205)
#define SVG_LIGHTBLUE SVGColor(173, 216, 230)
#define SVG_LIGHTCORAL SVGColor(240, 128, 128)
#define SVG_LIGHTCYAN SVGColor(224, 255, 255)
#define SVG_LIGHTGOLDENRODYELLOW SVGColor(250, 250, 210)
#define SVG_LIGHTGRAY SVGColor(211, 211, 211)
#define SVG_LIGHTGREEN SVGColor(144, 238, 144)
#define SVG_LIGHTGREY SVGColor(211, 211, 211)
#define SVG_LIGHTPINK SVGColor(255, 182, 193)
#define SVG_LIGHTSALMON SVGColor(255, 160, 122)
#define SVG_LIGHTSEAGREEN SVGColor(32, 178, 170)
#define SVG_LIGHTSKYBLUE SVGColor(135, 206, 250)
#define SVG_LIGHTSLATEGRAY SVGColor(119, 136, 153)
#define SVG_LIGHTSLATEGREY SVGColor(119, 136, 153)
#define SVG_LIGHTSTEELBLUE SVGColor(176, 196, 222)
#define SVG_LIGHTYELLOW SVGColor(255, 255, 224)
#define SVG_LIME SVGColor(0, 255, 0)
#define SVG_LIMEGREEN SVGColor(50, 205, 50)
#define SVG_LINEN SVGColor(250, 240, 230)
#define SVG_MAGENTA SVGColor(255, 0, 255)
#define SVG_MAROON SVGColor(128, 0, 0)
#define SVG_MEDIUMAQUAMARINE SVGColor(102, 205, 170)
#define SVG_MEDIUMBLUE SVGColor(0, 0, 205)
#define SVG_MEDIUMORCHID SVGColor(186, 85, 211)
#define SVG_MEDIUMPURPLE SVGColor(147, 112, 219)
#define SVG_MEDIUMSEAGREEN SVGColor(60, 179, 113)
#define SVG_MEDIUMSLATEBLUE SVGColor(123, 104, 238)
#define SVG_MEDIUMSPRINGGREEN SVGColor(0, 250, 154)
#define SVG_MEDIUMTURQUOISE SVGColor(72, 209, 204)
#define SVG_MEDIUMVIOLETRED SVGColor(199, 21, 133)
#define SVG_MIDNIGHTBLUE SVGColor(25, 25, 112)
#define SVG_MINTCREAM SVGColor(245, 255, 250)
#define SVG_MISTYROSE SVGColor(255, 228, 225)
#define SVG_MOCCASIN SVGColor(255, 228, 181)
#define SVG_NAVAJOWHITE SVGColor(255, 222, 173)
#define SVG_NAVY SVGColor(0, 0, 128)
#define SVG_OLDLACE SVGColor(253, 245, 230)
#define SVG_OLIVE SVGColor(128, 128, 0)
#define SVG_OLIVEDRAB SVGColor(107, 142, 35)
#define SVG_ORANGE SVGColor(255, 165, 0)
#define SVG_ORANGERED SVGColor(255, 69, 0)
#define SVG_ORCHID SVGColor(218, 112, 214)
#define SVG_PALEGOLDENROD SVGColor(238, 232, 170)
#define SVG_PALEGREEN SVGColor(152, 251, 152)
#define SVG_PALETURQUOISE SVGColor(175, 238, 238)
#define SVG_PALEVIOLETRED SVGColor(219, 112, 147)
#define SVG_PAPAYAWHIP SVGColor(255, 239, 213)
#define SVG_PEACHPUFF SVGColor(255, 218, 185)
#define SVG_PERU SVGColor(205, 133, 63)
#define SVG_PINK SVGColor(255, 192, 203)
#define SVG_PLUM SVGColor(221, 160, 221)
#define SVG_POWDERBLUE SVGColor(176, 224, 230)
#define SVG_PURPLE SVGColor(128, 0, 128)
#define SVG_RED SVGColor(255, 0, 0)
#define SVG_ROSYBROWN SVGColor(188, 143, 143)
#define SVG_ROYALBLUE SVGColor(65, 105, 225)
#define SVG_SADDLEBROWN SVGColor(139, 69, 19)
#define SVG_SALMON SVGColor(250, 128, 114)
#define SVG_SANDYBROWN SVGColor(244, 164, 96)
#define SVG_SEAGREEN SVGColor(46, 139, 87)
#define SVG_SEASHELL SVGColor(255, 245, 238)
#define SVG_SIENNA SVGColor(160, 82, 45)
#define SVG_SILVER SVGColor(192, 192, 192)
#define SVG_SKYBLUE SVGColor(135, 206, 235)
#define SVG_SLATEBLUE SVGColor(106, 90, 205)
#define SVG_SLATEGRAY SVGColor(112, 128, 144)
#define SVG_SLATEGREY SVGColor(112, 128, 144)
#define SVG_SNOW SVGColor(255, 250, 250)
#define SVG_SPRINGGREEN SVGColor(0, 255, 127)
#define SVG_STEELBLUE SVGColor(70, 130, 180)
#define SVG_TAN SVGColor(210, 180, 140)
#define SVG_TEAL SVGColor(0, 128, 128)
#define SVG_THISTLE SVGColor(216, 191, 216)
#define SVG_TOMATO SVGColor(255, 99, 71)
#define SVG_TURQUOISE SVGColor(64, 224, 208)
#define SVG_VIOLET SVGColor(238, 130, 238)
#define SVG_WHEAT SVGColor(245, 222, 179)
#define SVG_WHITE SVGColor(255, 255, 255)
#define SVG_WHITESMOKE SVGColor(245, 245, 245)
#define SVG_YELLOW SVGColor(255, 255, 0)
#define SVG_YELLOWGREEN SVGColor(154, 205, 50)

#endif //SVG_RENDERING_COLOR_H
