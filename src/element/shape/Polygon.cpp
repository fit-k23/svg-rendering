#include "Polygon.h"

/** @brief Default constructor */
SVGPolygon::SVGPolygon() : SVGPolyline() {}

/** @brief Parameterized constructor with fill rule parameter */
SVGPolygon::SVGPolygon(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const std::vector<Vector2D<float>> &points) : SVGPolyline(position, fillColor, strokeColor, strokeWidth, points, FillRule::NON_ZERO) {}
SVGPolygon::SVGPolygon(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const std::vector<Vector2D<float>> &points, FillRule fillRule) : SVGPolyline(position, fillColor, strokeColor, strokeWidth, points, fillRule) {}

/** @brief Get type Polygon */
ElementType SVGPolygon::getTypeName() { return ElementType::Polygon; }
