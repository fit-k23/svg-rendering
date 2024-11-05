#ifndef SVG_RENDERING_LINE_H
#define SVG_RENDERING_LINE_H

#include "../Element.h"
#include "../utils/Vector2D.h"

class Line : public Element{
private:
	Vector2D<float> endPosition;
public:
	/** @brief Default constructor */
	Line();

	/** @brief Parameterized constructor */
	Line(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const Vector2D<float> &endPosition);

	/** @brief Copy constructor */
	Line(const Line &other);

	/**
	 * @brief get type Line
	 * @return ElementType::Line
	 * @note This function is override
	*/
	ElementType getTypeName() override;

	/** @brief print information of line */
	void dbg() override;

	/**
	* @brief Get bounding box of line
	* @return pair of top-left and bottom-right coordinate
	* @note This function doesn't change any attributes
	*/
	std::pair<Vector2D<float>, Vector2D<float>> getBoundingBox() const override;


	/** @brief set end position of line */
	void setEndPosition(const Vector2D<float> &endPosition);

	/**
	 * @brief get end position of a line
	 * @note This function does not change any attributes
	*/
	Vector2D<float> getEndPosition() const;

	/**
	 * @brief Get slope coefficient of the line
	 * @return slope
	*/
	float getSlope() const;

	/**
	 * @brief Check if two lines intersect each other
	 * @return bool
	*/
	bool isIntersect(const Line &other) const;

	/**
	 * @brief Get intersected point
	 * @return intersected point
	*/
	Vector2D<float> getIntersected(const Line &other) const;
};

#endif //SVG_RENDERING_LINE_H
