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
 * @note It contains most of SVG attributes and a reference to Gradient class (applying bridge design pattern)
 * @note Must have the virtual destructor to avoid any undefined behaviors
 */
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
	 * @brief Default constructor.
	 */
	Element();

	/**
	 * @brief Constructor without transformations
	 */
	Element(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth);

	/**
	 * @brief Constructor wiith transformations
	 */
	Element(const Vector2D<float>& position, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth, const std::vector<std::string> &transformation);

public:
	/**
	 * @brief Virtual destructor
	 */
	virtual ~Element() = default;

	/**
	 * @brief Get name of an svg element
	 * @return ElementType 
	 * @note This function is pure virtual and must be implemented by subclasses
	 */
	virtual ElementType getTypeName() = 0;

	/**
	 * @brief Print all data of an svg element
	 * @note For debugging purpose
	 */
	virtual void dbg();

	/*
	 * @brief Get bounding box of an svg element
	 * @note This function doesn't change any attributes
	 */
	virtual std::pair<Vector2D<float>, Vector2D<float>> getBoundingBox() const;

	/**
	 * @brief Set position of an svg element
	 * @param x the x coordinate
	 * @param y the y coordinate
	 */
	void setPosition(float x, float y);

	/**
	 * @brief Set position of an svg element
	 * @param position new position of type Vector2D
	 */
	void setPosition(const Vector2D<float> &position);

	/**
	 * @brief Get position of an svg element
	 * @return Vector2D
	 * @note This function doesn't change any attributes
	 */
	Vector2D<float> getPosition() const;

	/**
	 * @brief Set fill color of an svg element
	 * @param color new fill color
	 */
	void setFillColor(const SVGColor &color);

	/**
	 * @brief Get fill color of an svg element
	 * @return SVGColor
	 * @note This function doesn't change any attributes
	 */
	SVGColor getFillColor() const;

	/**
	 * @brief Set stroke color of an svg element
	 * @param color new stroke color
	 */
	void setStrokeColor(const SVGColor &color);

	/**
	 * @brief Get stroke color of an svg element
	 * @return SVGColor
	 * @note This function doesn't change any attributes
	 */
	SVGColor getStrokeColor() const;

	/**
	 * @brief Set stroke width of an svg element
	 * @param width new width
	 */
	void setStrokeWidth(float width);

	/**
	 * @brief Get stroke width of an svg element
	 * @return float
	 * @note This function doesn't change any attributes
	 */
	float getStrokeWidth() const;

	/**
	 * @brief Add a transformation  
	 * @param s new transformation
	 */
	void addTransformation(const std::string &s);

	/** 
	 * @brief Set transformations
	 * @param transformations new set of transformations for svg element
	 */
	void setTransformation(const std::vector<std::string> &transformations);

	/**
	 * @brief Get all current transformations
	 * @return vector<string>
	 * @note This function doesn't change any attributes
	 */
	std::vector<std::string> getTransformation() const;

	/**
	 * @brief Set gradient of an svg element
	 * @param grad pointer to a concrete-Gradient object
	 */
	void setGradient(Gradient *grad);

	/**
	 * @brief Get gradient of an svg element
	 * @return a pointer to a concrete-Gradient object
	 * @note This function doesn't change any attributes
	 */
	Gradient *getGradient() const;

	/**
	 * @brief Set parent node of an svg element
	 * @param parent a pointer to a concrete-Element object
	 */
	void setParent(Element *parent);

	/**
	 * @brief Get parent node of an svg element
	 * @return a pointer to a concrete-Element object
	 * @note This function doesn't change any attributes
	 */
	Element *getParent() const;
};

#endif //SVG_RENDERING_ELEMENT_H
