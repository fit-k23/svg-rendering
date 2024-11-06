#ifndef SVG_RENDERING_POLYGON_H
#define SVG_RENDERING_POLYGON_H

#include "Polyline.h"
#include "../../api/Graphic.h"
#include "../utils/FillRule.h"
#include <vector>
#include <string>

/**
 * @brief Polygon class
 * @note position vector2D in Polygon is the first point of polygon
 * @note lines describe all edges of Polygon
*/
class Polygon : public Polyline{
private:
	std::vector<Vector2D<float>> points;
	FillRule fillRule;
public:
	/** @brief Default constructor */
	Polygon();

	/** @brief Parameterized constructor */
	Polygon(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const std::vector<Vector2D<float>> &points, FillRule fillRule = FillRule::NON_ZERO);


	/** @brief Get type Polygon */
	ElementType getTypeName() override;

	/** @brief Print all information of Polygon */
	void dbg() override;

	/**
	 * @brief Get bounding box of polygon
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
	void setFillRule(FillRule fillRule);

	/**
	 * @brief Get fill rule
	 * @return fill rule
	*/
	FillRule getFillRule() const;
};

#endif //SVG_RENDERING_POLYGON_H
