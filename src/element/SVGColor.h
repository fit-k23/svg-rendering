#ifndef SVG_RENDERING_COLOR_H
#define SVG_RENDERING_COLOR_H

#include <iostream>
#include <map>
#include <string>
#include "../../lib/raylib/raylib.h"

class SVGColor {
public:
	unsigned char r, g, b, a;
	/**
     * @brief Default constructor
     * @note set all to zero -> black
     */
    SVGColor(); 
    
    /*
    * @brief Parameterized constructor with alpha
    */
    SVGColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

    /*
    * @brief Parameterized constructor without alpha
    */
    SVGColor(unsigned char r, unsigned char g, unsigned char b);

    /*
    * @brief Parameterized constructor (string-type)
    * @param string format
    */
    SVGColor(std::string param);

    /*
    * @brief Parameterized constructor for HSL color value without alpha
    */
	SVGColor(int h, int s, int l);// hsl
	
    /*
    * @brief Parameterized constructor for HSL color value 
    */
    SVGColor(int h, int s, int l, int a); //hsla

    /*
    * @brief Get raylib color
    */
	Color getRaylibColor() const;

	// Parameterized constructor
	// @param: fill the string format
	// @note: fill can be hex code, color name, rgb(..), rgba(...),
	// @note: hsl(...), hsla(...)

};

const static std::map<std::string, SVGColor> LABELED_COLOR = {
    {"aliceblue", SVGColor(240, 248, 255)},
    {"antiquewhite", SVGColor(250, 235, 215)},
    {"aqua", SVGColor(0, 255, 255)},
    {"aquamarine", SVGColor(127, 255, 212)},
    {"azure", SVGColor(240, 255, 255)},
    {"beige", SVGColor(245, 245, 220)},
    {"bisque", SVGColor(255, 228, 196)},
    {"black", SVGColor(0, 0, 0)},
    {"blanchedalmond", SVGColor(255, 235, 205)},
    {"blue", SVGColor(0, 0, 255)},
    {"blueviolet", SVGColor(138, 43, 226)},
    {"brown", SVGColor(165, 42, 42)},
    {"burlywood", SVGColor(222, 184, 135)},
    {"cadetblue", SVGColor(95, 158, 160)},
    {"chartreuse", SVGColor(127, 255, 0)},
    {"chocolate", SVGColor(210, 105, 30)},
    {"coral", SVGColor(255, 127, 80)},
    {"cornflowerblue", SVGColor(100, 149, 237)},
    {"cornsilk", SVGColor(255, 248, 220)},
    {"crimson", SVGColor(220, 20, 60)},
    {"cyan", SVGColor(0, 255, 255)},
    {"darkblue", SVGColor(0, 0, 139)},
    {"darkcyan", SVGColor(0, 139, 139)},
    {"darkgoldenrod", SVGColor(184, 134, 11)},
    {"darkgray", SVGColor(169, 169, 169)},
    {"darkgreen", SVGColor(0, 100, 0)},
    {"darkgrey", SVGColor(169, 169, 169)},
    {"darkkhaki", SVGColor(189, 183, 107)},
    {"darkmagenta", SVGColor(139, 0, 139)},
    {"darkolivegreen", SVGColor(85, 107, 47)},
    {"darkorange", SVGColor(255, 140, 0)},
    {"darkorchid", SVGColor(153, 50, 204)},
    {"darkred", SVGColor(139, 0, 0)},
    {"darksalmon", SVGColor(233, 150, 122)},
    {"darkseagreen", SVGColor(143, 188, 143)},
    {"darkslateblue", SVGColor(72, 61, 139)},
    {"darkslategray", SVGColor(47, 79, 79)},
    {"darkslategrey", SVGColor(47, 79, 79)},
    {"darkturquoise", SVGColor(0, 206, 209)},
    {"darkviolet", SVGColor(148, 0, 211)},
    {"deeppink", SVGColor(255, 20, 147)},
    {"deepskyblue", SVGColor(0, 191, 255)},
    {"dimgray", SVGColor(105, 105, 105)},
    {"dimgrey", SVGColor(105, 105, 105)},
    {"dodgerblue", SVGColor(30, 144, 255)},
    {"firebrick", SVGColor(178, 34, 34)},
    {"floralwhite", SVGColor(255, 250, 240)},
    {"forestgreen", SVGColor(34, 139, 34)},
    {"fuchsia", SVGColor(255, 0, 255)},
    {"gainsboro", SVGColor(220, 220, 220)},
    {"ghostwhite", SVGColor(248, 248, 255)},
    {"gold", SVGColor(255, 215, 0)},
    {"goldenrod", SVGColor(218, 165, 32)},
    {"gray", SVGColor(128, 128, 128)},
    {"grey", SVGColor(128, 128, 128)},
    {"green", SVGColor(0, 128, 0)},
    {"greenyellow", SVGColor(173, 255, 47)},
    {"honeydew", SVGColor(240, 255, 240)},
    {"hotpink", SVGColor(255, 105, 180)},
    {"indianred", SVGColor(205, 92, 92)},
    {"indigo", SVGColor(75, 0, 130)},
    {"ivory", SVGColor(255, 255, 240)},
    {"khaki", SVGColor(240, 230, 140)},
    {"lavender", SVGColor(230, 230, 250)},
    {"lavenderblush", SVGColor(255, 240, 245)},
    {"lawngreen", SVGColor(124, 252, 0)},
    {"lemonchiffon", SVGColor(255, 250, 205)},
    {"lightblue", SVGColor(173, 216, 230)},
    {"lightcoral", SVGColor(240, 128, 128)},
    {"lightcyan", SVGColor(224, 255, 255)},
    {"lightgoldenrodyellow", SVGColor(250, 250, 210)},
    {"lightgray", SVGColor(211, 211, 211)},
    {"lightgreen", SVGColor(144, 238, 144)},
    {"lightgrey", SVGColor(211, 211, 211)},
    {"lightpink", SVGColor(255, 182, 193)},
    {"lightsalmon", SVGColor(255, 160, 122)},
    {"lightseagreen", SVGColor(32, 178, 170)},
    {"lightskyblue", SVGColor(135, 206, 250)},
    {"lightslategray", SVGColor(119, 136, 153)},
    {"lightslategrey", SVGColor(119, 136, 153)},
    {"lightsteelblue", SVGColor(176, 196, 222)},
    {"lightyellow", SVGColor(255, 255, 224)},
    {"lime", SVGColor(0, 255, 0)},
    {"limegreen", SVGColor(50, 205, 50)},
    {"linen", SVGColor(250, 240, 230)},
    {"magenta", SVGColor(255, 0, 255)},
    {"maroon", SVGColor(128, 0, 0)},
    {"mediumaquamarine", SVGColor(102, 205, 170)},
    {"mediumblue", SVGColor(0, 0, 205)},
    {"mediumorchid", SVGColor(186, 85, 211)},
    {"mediumpurple", SVGColor(147, 112, 219)},
    {"mediumseagreen", SVGColor(60, 179, 113)},
    {"mediumslateblue", SVGColor(123, 104, 238)},
    {"mediumspringgreen", SVGColor(0, 250, 154)},
    {"mediumturquoise", SVGColor(72, 209, 204)},
    {"mediumvioletred", SVGColor(199, 21, 133)},
    {"midnightblue", SVGColor(25, 25, 112)},
    {"mintcream", SVGColor(245, 255, 250)},
    {"mistyrose", SVGColor(255, 228, 225)},
    {"moccasin", SVGColor(255, 228, 181)},
    {"navajowhite", SVGColor(255, 222, 173)},
    {"navy", SVGColor(0, 0, 128)},
    {"oldlace", SVGColor(253, 245, 230)},
    {"olive", SVGColor(128, 128, 0)},
    {"olivedrab", SVGColor(107, 142, 35)},
    {"orange", SVGColor(255, 165, 0)},
    {"orangered", SVGColor(255, 69, 0)},
    {"orchid", SVGColor(218, 112, 214)},
    {"palegoldenrod", SVGColor(238, 232, 170)},
    {"palegreen", SVGColor(152, 251, 152)},
    {"paleturquoise", SVGColor(175, 238, 238)},
    {"palevioletred", SVGColor(219, 112, 147)},
    {"papayawhip", SVGColor(255, 239, 213)},
    {"peachpuff", SVGColor(255, 218, 185)},
    {"peru", SVGColor(205, 133, 63)},
    {"pink", SVGColor(255, 192, 203)},
    {"plum", SVGColor(221, 160, 221)},
    {"powderblue", SVGColor(176, 224, 230)},
    {"purple", SVGColor(128, 0, 128)},
    {"red", SVGColor(255, 0, 0)},
    {"rosybrown", SVGColor(188, 143, 143)},
    {"royalblue", SVGColor(65, 105, 225)},
    {"saddlebrown", SVGColor(139, 69, 19)},
    {"salmon", SVGColor(250, 128, 114)},
    {"sandybrown", SVGColor(244, 164, 96)},
    {"seagreen", SVGColor(46, 139, 87)},
    {"seashell", SVGColor(255, 245, 238)},
    {"sienna", SVGColor(160, 82, 45)},
    {"silver", SVGColor(192, 192, 192)},
    {"skyblue", SVGColor(135, 206, 235)},
    {"slateblue", SVGColor(106, 90, 205)},
    {"slategray", SVGColor(112, 128, 144)},
    {"slategrey", SVGColor(112, 128, 144)},
    {"snow", SVGColor(255, 250, 250)},
    {"springgreen", SVGColor(0, 255, 127)},
    {"steelblue", SVGColor(70, 130, 180)},
    {"tan", SVGColor(210, 180, 140)},
    {"teal", SVGColor(0, 128, 128)},
    {"thistle", SVGColor(216, 191, 216)},
    {"tomato", SVGColor(255, 99, 71)},
    {"turquoise", SVGColor(64, 224, 208)},
    {"violet", SVGColor(238, 130, 238)},
    {"wheat", SVGColor(245, 222, 179)},
    {"white", SVGColor(255, 255, 255)},
    {"whitesmoke", SVGColor(245, 245, 245)},
    {"yellow", SVGColor(255, 255, 0)},
    {"yellowgreen", SVGColor(154, 205, 50)}
};

#endif //SVG_RENDERING_COLOR_H
