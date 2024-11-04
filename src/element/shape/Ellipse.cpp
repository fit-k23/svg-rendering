#include "Ellipse.h"
#include "../../utils/Raylibex.h"
/**
 * @brief Default Constructor
 * @note Only use class Element and Vector2D so 
 * reuse the default constructor of those 2 classes
 */
Ellipse::Ellipse() : Element(), radii() {}

/**
 * @brief Full-parameterized constructor of ellipse
 */
Ellipse::Ellipse(const Vector2D<float> &_position, const SVGColor &_fillColor, const SVGColor &_strokeColor, float strokeWidth,
                 const Vector2D<float> &_radii) : Element(_position, _fillColor, _strokeColor, strokeWidth), radii(_radii) {}

/**
 * @brief get type of object
 * @return ElementType::Ellipse
 */
ElementType Ellipse::getTypeName() {
    return ElementType::Ellipse;
}


/**
 * @brief print all data of Ellipse
 */
void Ellipse::dbg() {
    Element::dbg();
    std::cout << "Stroke Width: " << strokeWidth << '\n';
}

/*
* @brief Get bounding box of ellipse
* @return pair of top-left and bottom-right coordinate
* @note This function doesn't change any attributes
*/
std::pair<Vector2D<float>, Vector2D<float>> Ellipse::getBoundingBox() const {
    Vector2D<float> topLeft = Vector2D<float>(position.x - radii.x - strokeWidth / 2.0f, position.y - radii.y - strokeWidth / 2.0f);
    Vector2D<float> bottomRight = Vector2D<float>(position.x + radii.x + strokeWidth / 2.0f, position.y + radii.y + strokeWidth / 2.0f);
    return {topLeft, bottomRight};
}

/**
 * @brief set radii
 * @param radii update radii
 */
void Ellipse::setRadii(const Vector2D<float> &_radii) { this->radii = _radii; }

/**
 * @brief get radii
 * @return radii
* @note This function doesn't change any attributes
 */
Vector2D<float> Ellipse::getRadii() const { return radii; }
