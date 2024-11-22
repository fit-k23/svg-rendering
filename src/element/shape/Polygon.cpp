#include "Polygon.h"

SVGPolygon::SVGPolygon() : SVGPolyline() {}
SVGPolygon::SVGPolygon(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const std::vector<Vector2D<float>> &points, FillRule fillRule) : SVGPolyline(position, fillColor, strokeColor, strokeWidth, points, fillRule) {}
ElementType SVGPolygon::getTypeName() { return ElementType::Polygon; }
