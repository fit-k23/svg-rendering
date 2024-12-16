#ifndef SVG_RENDERING_CIRCLE_H
#define SVG_RENDERING_CIRCLE_H

#include "Ellipse.h"
#include "../utils/SVGColor.h"

/**
 * @brief Class that represents circle in svg
 * @note Circle class is inherited from Ellipse class
 */
class SVGCircle final : public SVGEllipse{
public:
	SVGCircle() = default;

	/** @brief Full-parameterized constructor */
	SVGCircle(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, float radius);

	/** @brief Get type of SVGCircle */
	ElementType getTypeName() override;

	/** @brief print information of SVGCircle */
	void dbg() override;

	/**
	 * @brief Get bounding box of the circle
	 * @return pair of top-left and bottom-right coordinate
	 */
	std::pair<Vector2D<float>, Vector2D<float>> getBoundingBox() const override;
};

#endif //SVG_RENDERING_CIRCLE_H
