#ifndef SVG_RENDERING_CUBICPATHPOINT_H
#define SVG_RENDERING_CUBICPATHPOINT_H

#include "PathPoint.h"

/**
 * @brief Class that represents a point in Cubic Bezier Curve in svg path
 * @note This class inherits from PathPoint class
 */

class CubicPathPoint final : public PathPoint {
	Vector2D<float> cen[2]; // <-- 2 control points of cubic bezier curve
public:
	CubicPathPoint();
	CubicPathPoint(char cmd, const Vector2D<float> &pos);
	CubicPathPoint(char cmd, const Vector2D<float> &pos, const Vector2D<float> &cen);
	CubicPathPoint(char cmd, const Vector2D<float> &pos, const Vector2D<float> &cen1, const Vector2D<float> &cen2);
	CubicPathPoint(const CubicPathPoint& other) = default;
	/**
	 * @brief Setter method to set new control point
	 * @param cen new control point
	 * @param id tells which control point to set
	 */
	void setCen(const Vector2D<float>& cen, int id);
	/**
	 * @brief Getter method to get the control point
	 * @param id tells which control point to get
	 */
	Vector2D<float> getCen(int id) const;
	/**
	 * @brief Print information of cubic-bezier-curve point
	 * @note This function overrides from PathPoint
	 */
	void output() const override;

	std::string getPointType() const override;
};

#endif
