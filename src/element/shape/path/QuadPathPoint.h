#ifndef SVG_RENDERING_QUADPATHPOINT_H
#define SVG_RENDERING_QUADPATHPOINT_H

#include "PathPoint.h"

/**
 * @brief Class that represents the Quadratic Bezier Curve point in svg path
 * @note This class inherits from PathPoint class
*/

class QuadPathPoint : public PathPoint {
private:
	Vector2D<float> cen; 
public:
	QuadPathPoint();
	QuadPathPoint(char cmd, const Vector2D<float> &pos, const Vector2D<float> &cen = {});
	QuadPathPoint(const QuadPathPoint &other);
	void setCen(const Vector2D<float> &cen);
	Vector2D<float> getCen() const;
	void output() const override;
	std::string getPointType() const override;
};

#endif 