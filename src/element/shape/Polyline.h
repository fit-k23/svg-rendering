#ifndef SVG_RENDERING_POLYLINE_H
#define SVG_RENDERING_POLYLINE_H

#include "../Element.h"
#include "../../api/Graphic.h"
#include "../utils/FillRule.h"
#include <vector>
#include <string>

/**
 * @brief Polyline class
 * @note position is the first point of the polygon (first point of the first line)
*/
class SVGPolyline : public Element{
protected:
	std::vector<Vector2D<float>> points;
	FillRule fillRule;
public:
	/** @brief Default constructor */
	SVGPolyline();

	/** @brief Parameterized constructor */
	SVGPolyline(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const std::vector<Vector2D<float>> &points);
	SVGPolyline(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const std::vector<Vector2D<float>> &points, FillRule fillRule);

	/** @brief Copy constructor */
	SVGPolyline(const SVGPolyline &other);

	/** @brief Get type Line */
	ElementType getTypeName() override;

	/** @brief Print all information of Line */
	void dbg() override;

	/**
	 * @brief Get bounding box of polyline
	 * @return pair of top-left and bottom-right coordinate
	 * @note This function doesn't change any attributes
	*/
	std::pair<Vector2D<float>, Vector2D<float>> getBoundingBox() const override;


	/** @brief Set the vector of lines */
	void setPoints(const std::vector<Vector2D<float>> &points);

	/** @brief Add a line to vector */
	void addPoints(const Vector2D<float> &point);

	/**
	 * @brief Get vector of lines
	 * @note This function doesn't change any attributes
	*/
	std::vector<Vector2D<float>> getPoints() const;

	/**
	 * @brief Set fill rule
	 * @param fillRule new fill rule
	*/
	void setFillRule(const FillRule &fillRule);

	/**
	 * @brief Get fill rule
	 * @return fill rule
	*/
	FillRule getFillRule() const;
};

#endif //SVG_RENDERING_POLYLINE_H
