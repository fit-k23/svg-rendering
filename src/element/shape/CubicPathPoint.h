#ifndef SVG_RENDERING_CUBICPATHPOINT_H
#define SVG_RENDERING_CUBICPATHPOINT_H

#include "PathPoint.h"

class CubicPathPoint : public PathPoint {
private:
	Vector2D<float> cen[2];
public:
	CubicPathPoint();
	CubicPathPoint(char cmd, const Vector2D<float>& pos);
	CubicPathPoint(char cmd, const Vector2D<float>& pos, const Vector2D<float>& cen);
	CubicPathPoint(char cmd, const Vector2D<float>& pos, const Vector2D<float>& cen1, const Vector2D<float>& cen2);
	CubicPathPoint(const CubicPathPoint& other);
	void setCen(const Vector2D<float>& cen, int id);
	Vector2D<float> getCen(int id) const;
	void output() const override;

	std::string getPointType() const override;
};

#endif 