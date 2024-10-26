#include "Ellipse.h"

/**
 * @brief Default Constructor
 * @note Only use class Element and Vector2D so 
 * reuse the default constructor of those 2 classes
 */
Ellipse::Ellipse() : Element(), radii() {}

/**
 * @brief Full-parameterized constructor of ellipse
 */
Ellipse::Ellipse(Vector2D<double> _position, const SVGColor& fillColor, const SVGColor& strokeColor, double strokeWidth, 
                 Vector2D<double>radii) : Element(_position, fillColor, strokeColor, strokeWidth), radii(radii) {}

/**
 * @brief get type of object
 * @return ElementType::Ellipse
 */
ElementType Ellipse::getTypeName() {
    return ElementType::Ellipse;
}

/**
 * @brief draw Ellipse
 * @note override function
 */
void Ellipse::draw() {

}

/**
 * @brief print all data of Ellipse
 */
void Ellipse::dbg() {

}

/**
 * @brief set radii
 * @param radii update radii
 */
void Ellipse::setRadii(const Vector2D<double>& radii) {
    this->radii = radii;
}

/**
 * @brief get radii
 * @return radii
 */
Vector2D<double> Ellipse::getRadii() {
    return this->radii;
}
