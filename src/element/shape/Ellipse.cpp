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
Ellipse::Ellipse(const Vector2D<double> &_position, const SVGColor& fillColor, const SVGColor& strokeColor, double strokeWidth, const Vector2D<double> &radii) : Element(_position, fillColor, strokeColor, strokeWidth), radii(radii) {}

/**
 * @brief get type of object
 * @return ElementType::Ellipse
 */
ElementType Ellipse::getTypeName() {
    return ElementType::Ellipse;
}

#include "../../../lib/raylib/rlgl.h"
#include "../../../lib/raylib/raymath.h"

void DrawEllipseHQ(int centerX, int centerY, float radiusH, float radiusV, Color color) {
	rlBegin(RL_TRIANGLES);
	int step = 1;
	for (int i = 0; i < 360; i += step) {
		rlColor4ub(color.r, (color.g + i) % 256, color.b, color.a);
		rlVertex2f((float)centerX, (float)centerY);
		rlVertex2f((float)centerX + cosf(DEG2RAD * (i + step)) *radiusH, (float)centerY + sinf(DEG2RAD * (i + step)) * radiusV);
		rlVertex2f((float)centerX + cosf(DEG2RAD * i) * radiusH, (float)centerY + sinf(DEG2RAD*i) * radiusV);
	}
	rlEnd();
}

/**
 * @brief draw Ellipse
 * @note override function
 */
void Ellipse::draw() {
	if (this->strokeWidth != 0) {
		DrawEllipseHQ(this->position.x, this->position.y, this->radii.x, this->radii.y, this->getStrokeColor().getRaylibColor());
		DrawEllipseHQ(this->position.x, this->position.y, this->radii.x - this->strokeWidth, this->radii.y - strokeWidth, this->fillColor.getRaylibColor());
	} else {
		DrawEllipseHQ(this->position.x, this->position.y, this->radii.x, this->radii.y, this->fillColor.getRaylibColor());
	}
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
void Ellipse::setRadii(const Vector2D<double> &_radii) {
    this->radii = _radii;
}

/**
 * @brief get radii
 * @return radii
 */
Vector2D<double> Ellipse::getRadii() {
    return this->radii;
}
