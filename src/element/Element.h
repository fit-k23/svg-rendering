#ifndef SVG_RENDERING_ELEMENT_H
#define SVG_RENDERING_ELEMENT_H

#include <iostream>
#include <string>
#include <vector>
#include <objidl.h>
#include <gdiplus.h>
#include "utils/ElementType.h"
#include "utils/Vector2D.h"
#include "utils/Gradient.h"
#include "utils/SVGColor.h"

/**
* @brief Element is an abstract class for all svg elements (nodes)
* @attributes contains most of SVG attributes and a pointer to its parent node
* Since it's abstract, the destructor must be virtual to avoid any undefined behaviors
**/
class Element{
protected:
	Vector2D<float> position;
	SVGColor fillColor;
	SVGColor strokeColor;
	float strokeWidth;
	std::vector<std::string> transformation;
	Gradient *gradient{};
	Element *parent{};

	/**
	* @brief Default constructor
	* TODO: change to not default
	* Because now I haven't finished other classes yet .-.
	*/
	Element();

	/**
	* @brief Parameterized constructor
	* @note easier for subclass to inherit and write its constructor
	*/
	Element(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth);

public:
	/**
	* @brief Virtual destructor
	*/
	virtual ~Element() = default;

	/**
	* @brief Get TypeName of an svg element
	* @brief This function is abstract and must be implemented by subclasses (derived classes)
	* @param no
	* @return the type (ElementType type)
	*/
	virtual ElementType getTypeName() = 0;

	/**
	* @brief Print all data of an svg element
	* @note For debugging
	*/
	virtual void dbg();

	/*
	* @brief Get bounding box of an svg element
	* @note This function doesn't change any attributes
	*/
	virtual std::pair<Vector2D<float>, Vector2D<float>> getBoundingBox() const;

	/**
	* @brief Set position of an svg element
	* @param x and y coordinates (float)
	*/
	void setPosition(float x, float y);

	/**
	* @brief set position of an svg element
	* @param position new vector2D position
	*/
	void setPosition(const Vector2D<float> &position);

	/**
	* @brief get position of an svg element
	* @return a vector2D
	* @note This function doesn't change any attributes
	*/
	Vector2D<float> getPosition() const;

	/**
	* @brief set fill color of an svg element
	* @param a passed-by-referenced SVGColor object
	*/
	void setFillColor(const SVGColor &color);

	/**
	* @brief get fill color of an svg element
	* @return an SVGColor object
	* @note This function doesn't change any attributes
	*/
	SVGColor getFillColor() const;

	/**
	* @brief set stroke color of an svg element
	* @param a passed-by-referenced SVGColor object
	*/
	void setStrokeColor(const SVGColor &color);

	/**
	* @brief get stroke color of an svg element
	* @return a SVGColor object
	* @note This function doesn't change any attributes
	*/
	SVGColor getStrokeColor() const;

	/**
	* @brief set stroke width of an svg element
	* @param a float variable
	*/
	void setStrokeWidth(float width);

	/**
	* @brief get stroke width of an svg element
	* @return float
	* @note This function doesn't change any attributes
	*/
	float getStrokeWidth() const;

	/**
	 * @brief add a transformation  
	 * @param s a transformation string
	 */
	void addTransformation(const std::string &s);

	/**
	 * @brief get all current transformations
	 * @return transformation
	* @note This function doesn't change any attributes
	 */
	std::vector<std::string> getTransformation() const;

	/**
	* @brief set gradient of an svg element
	* @param a pointer to an abstract Gradient object
	*/
	void setGradient(Gradient *grad);

	/**
	* @brief get gradient of an svg element
	* @param a pointer to a Gradient object
	* @note This function doesn't change any attributes
	*/
	Gradient *getGradient() const;

	/**
	* @brief set parent node of an svg element
	* @param a pointer to a same-class object (parent)
	*/
	void setParent(Element *parent);

	/**
	* @brief get parent node of an svg element
	* @return a pointer to a same-class object (parent)
	* @note This function doesn't change any attributes
	*/
	Element *getParent() const;
};

#endif //SVG_RENDERING_ELEMENT_H
