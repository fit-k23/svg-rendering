#ifndef SVG_RENDERING_QUADPATHPOINT_H
#define SVG_RENDERING_QUADPATHPOINT_H

#include "PathPoint.h"

/** @brief Class that represents the Quadratic Bezier Curve point in svg path */
class QuadPathPoint final : public PathPoint {
	Vector2D<float> cen;
public:
	QuadPathPoint() = default;
	QuadPathPoint(char cmd, const Vector2D<float> &pos, const Vector2D<float> &cen = {});
	QuadPathPoint(const QuadPathPoint &other) = default;
	void setCen(const Vector2D<float> &cen);
	Vector2D<float> getCen() const;
	void output() const override;
	std::string getPointType() const override;
};

#endif 