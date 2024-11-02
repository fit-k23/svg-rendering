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
Ellipse::Ellipse(const Vector2D<float> &_position, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth,
                 const Vector2D<float> &radii) : Element(_position, fillColor, strokeColor, strokeWidth), radii(radii) {}

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
    std::cout << "[DEBUG ELLIPSE]\n";
    std::cout << "Position: (" << position.x << ", " << position.y << ")\n";
    std::cout << "Radiix = " << radii.x << ", Radiiy = " << radii.y << '\n';
    std::cout << "Stroke width = " << strokeWidth << '\n';
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
