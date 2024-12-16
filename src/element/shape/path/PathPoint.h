#ifndef SVG_RENDERING_PATHPOINT_H
#define SVG_RENDERING_PATHPOINT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include "../../utils/Vector2D.h"

/**
 * @brief A PathPoint class to represent all type of points in path
 * @note This is an abstract class
 * @note All types of points in svg path has a command and a position
 */

class PathPoint {
	char cmd;
	Vector2D<float> pos;
public:
	PathPoint();
	/**
	 * @brief Parameterized constructor
	 * @param cmd new command
	 * @param pos new position
	*/
	PathPoint(char cmd, const Vector2D<float> &pos);
	PathPoint(const PathPoint &other) = default;

	/** @brief Virtual destructor to ensure proper de-allocation */
	virtual ~PathPoint() = default;
	/**
	 * @brief Setter method to set new command
	 * @param cmd new command
	 */
	void setCMD(char cmd);
	/** @brief Getter method to get the command */
	char getCMD() const;
	/**
	 * @brief Setter method to set new position
	 * @param pos new position
	 */
	void setPos(const Vector2D<float> &pos);
	/** @brief Getter method to get the position */
	Vector2D<float> getPos() const;
	/**
	 * @brief Print information of point
	 * @note This function can be override to print different types of points
	 */
	virtual void output() const;

	virtual std::string getPointType() const;

	operator Vector2D<float>();
};

#endif // SVG_RENDERING_PATHPOINT_H
