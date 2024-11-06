#ifndef SVG_RENDERING_POLYGON_H
#define SVG_RENDERING_POLYGON_H

#include "Polyline.h"
#include "../utils/FillRule.h"
#include "../utils/Vector2D.h"
#include <vector>
#include <string>

/**
 * @brief Polygon class
 * @note position vector2D in Polygon is the first point of polygon
 * @note lines describe all edges of Polygon
*/
class SVGPolygon : public SVGPolyline{
public:
	/** @brief Default constructor */
	SVGPolygon();

	/** @brief Parameterized constructor */
	SVGPolygon(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const std::vector<Vector2D<float>> &points);
	SVGPolygon(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const std::vector<Vector2D<float>> &points, FillRule fillRule);

	/** @brief Get type Polygon */
	ElementType getTypeName() override;
};

#endif //SVG_RENDERING_POLYGON_H
