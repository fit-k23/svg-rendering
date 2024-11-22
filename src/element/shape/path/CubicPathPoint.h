#ifndef SVG_RENDERING_CUBICPATHPOINT_H
#define SVG_RENDERING_CUBICPATHPOINT_H

#include "PathPoint.h"

/**
 * @brief Class that represents a point in Cubic Bezier Curve in svg path
 * @note This class inherits from PathPoint class
*/

class CubicPathPoint : public PathPoint {
private:
	Vector2D<float> cen[2]; // <-- 2 control points of cubic bezier curve
public:
	/** @brief Default constructor for cubic-bezier-curve point */
	CubicPathPoint();
	/** @brief Parameterized constructor */
	CubicPathPoint(char cmd, const Vector2D<float>& pos);
	/** @brief Parameterized constructor with just one control point */
	CubicPathPoint(char cmd, const Vector2D<float>& pos, const Vector2D<float>& cen);
	/** @brief Parameterized constructor with two control points */
	CubicPathPoint(char cmd, const Vector2D<float>& pos, const Vector2D<float>& cen1, const Vector2D<float>& cen2);
	/**
	 * @brief Copy constructor
	 * @param other CubicPathPoint object to copy from
	*/
	CubicPathPoint(const CubicPathPoint& other);
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