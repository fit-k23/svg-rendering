	#ifndef SVG_RENDERING_COLOR_H
#define SVG_RENDERING_COLOR_H

#include <iostream>
#include <string>

class SVGColor {
public:
    unsigned char r, g, b, a;
    /**
     * @brief Default constructor
     * @note set all to zero -> black
     */
    SVGColor(); // r,g,b,a = 0 -> black
    SVGColor(const std::string &param); // -> tên màu luôn, mã hex

	//
	// Parameterized constructor
	// @param: fill the string format
	// @note: fill can be hex code, color name, rgb(..), rgba(...),
	// @note: hsl(...), hsla(...)

};

#endif //SVG_RENDERING_COLOR_H
