#ifndef SVG_RENDERING_CIRCLE_H
#define SVG_RENDERING_CIRCLE_H

#include "Ellipse.h"
#include "../utils/SVGColor.h"

class Circle : public Ellipse{
public:
	/**
	 * @brief Default constructor
	 * @note TODO: change to not default
	*/
	Circle() = default;

	/**
	 * @brief Full-parameterized constructor
	 * @param inherits all from Ellipse
	*/
	Circle(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, float radius);

	/** @brief Get type of Circle */
	ElementType getTypeName() override;

	/** @brief print information of Circle */
	void dbg() override;

	/**
	 * @brief Get bounding box of circle
	 * @return pair of top-left and bottom-right coordinate
	 * @note This function doesn't change any attributes
	*/
	std::pair<Vector2D<float>, Vector2D<float>> getBoundingBox()
	const override;
};


#endif //SVG_RENDERING_CIRCLE_H
