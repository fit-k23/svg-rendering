#ifndef SVG_RENDERING_ELEMENT_H
#define SVG_RENDERING_ELEMENT_H

#include <iostream>
#include "Gradient.h"
#include "raylib.h"
#include "utils/ElementType.h"
#include "Vector2D.h"
#include "SVGColor.h"

/**
* @cmt: Element is an abstract class for all svg elements (nodes)
* @is_abstract: yes
* @inherits: no
* @attributes: contains most of SVG attributes and a pointer to its parent node
* Since it's abtract, the destructor must be virtual to avoid any undefined behaviors
**/
class Element{
private:
	Vector2D<double> position;
	SVGColor fillColor;
	SVGColor strokeColor;
	double strokeWidth;
	Gradient* gradient;
	Element* parent;
protected:
	/*
	* @cmt: Default constructor
	* TODO: change to not default
	* Because now I haven't finished other classes yet .-.
	*/
	Element() = default;
	
	/*
	* @cmt: Parameterized constructor
	* @note: easier for subclass to inherit and write its constructor
	*/
	Element(Vector2D<double> position, const SVGColor& fillColor, const SVGColor& strokeColor, double strokeWidth);
public:
	/*
	* @cmt: Virtual destructor
	*/
	virtual ~Element() = default;
	
	/*
	* @cmt: Get TypeName of an svg element
	* @cmt: This function is abstract and must be implemented by subclasses (derived classes)
	* @param: no
	* @return: the type (ElementType type)
	*/
	virtual ElementType getTypeName() = 0;
	
	/*
	* @cmt: draw or proecss an svg element
	* @cmt: This function is abstract and must be implemented by subclasses (derived classes)
	* @param: no
	*/
	virtual void draw() = 0;
	
	/*
	* @cmt: print all data of an svg element
	* @cmt: For debugging
	*/
	virtual void dbg() = 0;
	
	/*
	* @cmt: set position of an svg element
	* @param: x and y coordinates (double)
	*/
	void setPosition(double x, double y);

	/*
	* @cmt: set position of an svg element
	* @param: a passed-by-referenced vector2D object
	*/
	void setPosition(const Vector2D<double>& position);
	
	/*
	* @cmt: get position of an svg element
	* @return: a vector2D
	*/
	Vector2D<double> getPosition();
	
	/*
	* @cmt: set fill color of an svg element
	* @param: a passed-by-referenced SVGColor object
	*/
	void setFillFolor(const SVGColor &color);

	/*
	* @cmt: get fill color of an svg element
	* @return: an SVGColor object
	*/
	SVGColor getFillColor();

	/*
	* @cmt: set stroke color of an svg element
	* @param: a passed-by-referenced SVGColor object
	*/
	void setStrokeColor(const SVGColor &color);
	
	/*
	* @cmt: get stroke color of an svg element
	* @return: a SVGColor object
	*/
	SVGColor getStrokeColor();

	/*
	* @cmt: set stroke width of an svg element
	* @param: a double variable
	*/
	void setstrokeWidth(double width);

	/*
	* @cmt: get stroke width of an svg element
	* @return: double
	*/
	double getstrokeWidth();

	/*
	* @cmt: set gradient of an svg element
	* @param: a pointer to an abstract Gradient object
	*/
	void setGradient(Gradient* grad);

	/*
	* @cmt: get gradient of an svg element
	* @param: a pointer to a Gradient object
	*/
	Gradient* getGradient();

	/*
	* @cmt: set parent node of an svg element
	* @param: a pointer to a same-class object (parent)
	*/
	void setParent(Element* parent);

	/*
	* @cmt: get parent node of an svg element
	* @return: a pointer to a same-class object (parent)
	*/
	Element* getParent();
};

#endif //SVG_RENDERING_ELEMENT_H
