#ifndef SVG_RENDERING_ELEMENT_H
#define SVG_RENDERING_ELEMENT_H

#include <iostream>
#include <string>
#include <vector>
#include "../../lib/raylib/raylib.h"
#include "utils/ElementType.h"
#include "utils/Vector2D.h"
#include "Gradient.h"
#include "SVGColor.h"

/**
* @brief: Element is an abstract class for all svg elements (nodes)
* @is_abstract: yes
* @inherits: no
* @attributes: contains most of SVG attributes and a pointer to its parent node
* Since it's abstract, the destructor must be virtual to avoid any undefined behaviors
**/
class Element{
private:
	Vector2D<double> position;
	SVGColor fillColor;
	SVGColor strokeColor;
	double strokeWidth;
	std::vector<std::string> transformation;
	Gradient *gradient{};
	Element *parent{};
protected:
	/**
	* @brief: Default constructor
	* TODO: change to not default
	* Because now I haven't finished other classes yet .-.
	*/
	Element() = default;
	
	/**
	* @brief: Parameterized constructor
	* @note: easier for subclass to inherit and write its constructor
	*/
	Element(const Vector2D<double> &position, const SVGColor &fillColor, const SVGColor &strokeColor, double strokeWidth);
public:
	/**
	* @brief: Virtual destructor
	*/
	virtual ~Element() = default;
	
	/**
	* @brief: Get TypeName of an svg element
	* @brief: This function is abstract and must be implemented by subclasses (derived classes)
	* @param: no
	* @return: the type (ElementType type)
	*/
	virtual ElementType getTypeName() = 0;
	
	/**
	* @brief: draw or process an svg element
	* @brief: This function is abstract and must be implemented by subclasses (derived classes)
	* @param: no
	*/
	virtual void draw() = 0;
	
	/**
	* @brief: print all data of an svg element
	* @brief: For debugging
	*/
	virtual void dbg() = 0;
	
	/**
	* @brief: set position of an svg element
	* @param: x and y coordinates (double)
	*/
	void setPosition(double x, double y);

	/**
	* @brief: set position of an svg element
	* @param: a passed-by-referenced vector2D object
	*/
	void setPosition(const Vector2D<double> &position);
	
	/**
	* @brief: get position of an svg element
	* @return: a vector2D
	*/
	Vector2D<double> getPosition();
	
	/**
	* @brief: set fill color of an svg element
	* @param: a passed-by-referenced SVGColor object
	*/
	void setFillColor(const SVGColor &color);

	/**
	* @brief: get fill color of an svg element
	* @return: an SVGColor object
	*/
	SVGColor getFillColor();

	/**
	* @brief: set stroke color of an svg element
	* @param: a passed-by-referenced SVGColor object
	*/
	void setStrokeColor(const SVGColor &color);
	
	/**
	* @brief: get stroke color of an svg element
	* @return: a SVGColor object
	*/
	SVGColor getStrokeColor();

	/**
	* @brief: set stroke width of an svg element
	* @param: a double variable
	*/
	void setStrokeWidth(double width);

	/**
	* @brief: get stroke width of an svg element
	* @return: double
	*/
	double getStrokeWidth() const;

	/**
	 * @brief add a transformation  
	 * @param s a transformation string
	 */
	void addTransformation(const std::string& s);

	/**
	 * @brief get all current transformations
	 * @return transformation
	 */
	std::vector<std::string> getTransformation() const;

	/**
	* @brief: set gradient of an svg element
	* @param: a pointer to an abstract Gradient object
	*/
	void setGradient(Gradient *grad);

	/**
	* @brief: get gradient of an svg element
	* @param: a pointer to a Gradient object
	*/
	Gradient *getGradient();

	/**
	* @brief: set parent node of an svg element
	* @param: a pointer to a same-class object (parent)
	*/
	void setParent(Element *parent);

	/**
	* @brief: get parent node of an svg element
	* @return: a pointer to a same-class object (parent)
	*/
	Element *getParent();
};

#endif //SVG_RENDERING_ELEMENT_H
