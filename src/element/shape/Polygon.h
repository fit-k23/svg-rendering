#ifndef SVG_RENDERING_POLYGON_H
#define SVG_RENDERING_POLYGON_H

#include "Polyline.h"

/**
 * @brief Class that represents polygon in svg
 * @param position the first point of polygon
 * @note This class inherits from SVGPolyline class
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
