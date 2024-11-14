#ifndef SVG_RENDERING_PATHPOINT_H
#define SVG_RENDERING_PATHPOINT_H

#include "../utils/Vector2D.h"
#include <vector>
#include <algorithm>
#include <string>

/*
* @brief A general PathPoint class to represent all type of points in path
* @note This is a superclass 
* @note All types of points in svg path has a command and a position
*/

class PathPoint {
private:
	char cmd;
	Vector2D<float> pos;
public:
	/*
	* @brief Default constructor
	*/
	PathPoint();
	/*
	* @brief Parameterized constructor
	* @param cmd new command
	* @param pos new position
	*/
	PathPoint(char cmd, const Vector2D<float> &pos);
	/*
	* @brief Copy constructor
	* @param other PathPoint object to copy from
	*/
	PathPoint(const PathPoint &other);
	/*
	* @brief Virtual destructor to ensure proper deallocation
	*/
	virtual ~PathPoint() = default;
	/*
	* @brief Setter method to set new command
	* @param cmd new command
	*/
	void setCMD(char cmd); 
	/*
	* @brief Getter method to get the command
	* @note This method doesn't change any attributes
	*/
	char getCMD() const;
	/*
	* @brief Setter method to set new position
	* @param pos new position
	*/
	void setPos(const Vector2D<float> &pos);
	/*
	* @brief Getter method to get the position
	* @note This method doesn't change any attributes
	*/
	Vector2D<float> getPos() const;
	/*
	* @brief Print information of point
	* @note This function can be overrided to print different types of points
	*/
	virtual void output() const;
};

#endif // SVG_RENDERING_PATHPOINT_H