#ifndef SVG_RENDERING_CIRCLE_H
#define SVG_RENDERING_CIRCLE_H

#include "Ellipse.h"
#include "../SVGColor.h"

class Circle : public Ellipse{
public:
	/**
	* @brief Default constructor 
	* @note TODO: change to not default
	**/
	Circle() = default;

	/**
	* @brief Full-parameterized constructor
	* @param inherits all from Ellipse
	**/
	Circle(Vector2D<double> position, const SVGColor& fillColor, const SVGColor& strokeColor, double  strokeWidth, double radius);

	/**
	* @brief Get type of Circle
	**/
	ElementType getTypeName() override;
		
	/*
	* @brief print information of Circle
	*/
	void dbg() override;
};


#endif //SVG_RENDERING_CIRCLE_H
