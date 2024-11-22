#ifndef SVG_RENDERING_LINE_H
#define SVG_RENDERING_LINE_H

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "../Element.h"
#include <iostream>
#include "../utils/Vector2D.h"

/**
 * @brief Class that represents Line object in svg
 * @note This class inherits from Element class
 */

class SVGLine : public Element{
private:
	Vector2D<float> endPosition;
public:
	/** @brief Default constructor */
	SVGLine();

	/** @brief Parameterized constructor */
	SVGLine(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const Vector2D<float> &endPosition);

	/** @brief Copy constructor */
	SVGLine(const SVGLine &other);

	/**
	 * @brief get type SVGLine
	 * @return ElementType::SVGLine
	 * @note This function is override
	*/
	ElementType getTypeName() override;

	/** @brief print information of svgline */
	void dbg() override;

	/**
	* @brief Get bounding box of svgline
	* @return pair of top-left and bottom-right coordinate
	* @note This function doesn't change any attributes
	*/
	std::pair<Vector2D<float>, Vector2D<float>> getBoundingBox() const override;


	/** @brief set end position of svgline */
	void setEndPosition(const Vector2D<float> &endPosition);

	/**
	 * @brief get end position of a svgline
	 * @note This function does not change any attributes
	*/
	Vector2D<float> getEndPosition() const;

	/**
	 * @brief Get slope coefficient of the svgline
	 * @return slope
	*/
	float getSlope() const;

	/**
	 * @brief Check if two lines intersect each other
	 * @return bool
	*/
	bool isIntersect(const SVGLine &other) const;

	/**
	 * @brief Get intersected point
	 * @return intersected point
	*/
	Vector2D<float> getIntersected(const SVGLine &other) const;
};

#endif //SVG_RENDERING_LINE_H
