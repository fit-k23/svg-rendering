#ifndef SVG_RENDERING_LINE_H
#define SVG_RENDERING_LINE_H

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <iostream>
#include "../Element.h"
#include "../utils/Vector2D.h"

/**
 * @brief Class that represents Line object in svg
 * @note This class inherits from Element class
 */
class SVGLine final : public Element{
	Vector2D<float> endPosition;
public:
	SVGLine();
	SVGLine(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const Vector2D<float> &endPosition);
	SVGLine(const SVGLine &other) = default;

	/**
	 * @brief get type of the object
	 * @return ElementType::SVGLine
	 */
	ElementType getTypeName() override;

	/** @brief print information of line */
	void dbg() override;

	/**
	 * @brief Get bounding box of line
	 * @return pair of top-left and bottom-right coordinate
	 */
	std::pair<Vector2D<float>, Vector2D<float>> getBoundingBox() const override;


	/** @brief set end position of line */
	void setEndPosition(const Vector2D<float> &endPosition);

	/** @brief get end position of a line */
	Vector2D<float> getEndPosition() const;

	/**
	 * @brief Get slope coefficient of the line
	 * @return slope
	 */
	float getSlope() const;

	/** @brief Check if two lines intersect each other */
	bool isIntersect(const SVGLine &other) const;

	/**
	 * @brief Get intersected point
	 * @return intersected point
	 */
	Vector2D<float> getIntersected(const SVGLine &other) const;
};

#endif //SVG_RENDERING_LINE_H
