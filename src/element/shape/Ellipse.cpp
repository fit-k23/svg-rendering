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
Ellipse::Ellipse(const Vector2D<double> &_position, const SVGColor& fillColor, const SVGColor& strokeColor, double strokeWidth,
                 const Vector2D<double> &radii) : Element(_position, fillColor, strokeColor, strokeWidth), radii(radii) {}

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
//void Ellipse::draw() {
//	if (this->strokeWidth != 0) {
//		DrawEllipseHQ(this->position.x, this->position.y, this->radii.x, this->radii.y, this->getStrokeColor().getRaylibColor());
//		DrawEllipseHQ(this->position.x, this->position.y, this->radii.x - this->strokeWidth, this->radii.y - strokeWidth, this->fillColor.getRaylibColor());
//	} else {
//		DrawEllipseHQ(this->position.x, this->position.y, this->radii.x, this->radii.y, this->fillColor.getRaylibColor());
//	}
//}

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
void Ellipse::setRadii(const Vector2D<double> &_radii) { this->radii = _radii; }

/**
 * @brief get radii
 * @return radii
* @note This function doesn't change any attributes
 */
Vector2D<double> Ellipse::getRadii() const { return radii; }
