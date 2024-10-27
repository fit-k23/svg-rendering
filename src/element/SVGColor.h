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
    SVGColor(std::string param); // -> tên màu luôn, mã hex
};

#endif //SVG_RENDERING_COLOR_H
