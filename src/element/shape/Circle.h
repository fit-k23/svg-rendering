#ifndef SVG_RENDERING_CIRCLE_H
#define SVG_RENDERING_CIRCLE_H

#include "Ellipse.h"
#include "../utils/SVGColor.h"

/**
 * @brief Class that represents circle in svg
 * @note Circle class is inherited from Ellipse class
*/

class SVGCircle : public SVGEllipse{
public:
	/**
	 * @brief Default constructor
	 * @note TODO: change to not default
	*/
	SVGCircle() = default;

	/**
	 * @brief Full-parameterized constructor
	 * @param inherits all from Ellipse
	*/
	SVGCircle(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, float radius);

	/** @brief Get type of SVGCircle */
	ElementType getTypeName() override;

	/** @brief print information of SVGCircle */
	void dbg() override;

	/**
	 * @brief Get bounding box of svgcircle
	 * @return pair of top-left and bottom-right coordinate
	 * @note This function doesn't change any attributes
	*/
	std::pair<Vector2D<float>, Vector2D<float>> getBoundingBox() const override;
};

#endif //SVG_RENDERING_CIRCLE_H
