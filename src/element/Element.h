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
	Gradient *fillGradient, *strokeGradient;

	Element();
	/** @brief Constructor without transformations */
	Element(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth);
	/** @brief Constructor with transformations */
	Element(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const std::vector<std::string> &transformation);
public:
	virtual ~Element() = default;
	/**
	 * @brief Get name of an svg element
	 * @return ElementType 
	 * @note This function is pure virtual and must be implemented by subclasses
	*/
	virtual ElementType getTypeName() = 0;

	/**
	 * @brief Print out all data in the element
	 * @note For debugging purpose
	*/
	virtual void dbg();
	/** @brief Get the bounding box of the element */
	virtual std::pair<Vector2D<float>, Vector2D<float>> getBoundingBox() const;
	/** @brief Set current position of the element with emplace-inputs  */
	void setPosition(float x, float y);
	/**
	 * @brief Set the current position of the element to target position
	 * @param position Target position
	*/
	void setPosition(const Vector2D<float> &position);
	/** @brief Get the current position of the element */
	Vector2D<float> getPosition() const;
	/**
	 * @brief Set current fill color to target color
	 * @param color Target color
	*/
	void setFillColor(const SVGColor &color);
	/** @brief Get the current fill color of the element */
	SVGColor getFillColor() const;
	/**
	 * @brief Set the current stroke color to target color
	 * @param color Target color
	*/
	void setStrokeColor(const SVGColor &color);
	/** @brief Get the current stroke color of the element */
	SVGColor getStrokeColor() const;
	/**
	 * @brief Set the current stroke width to target width
	 * @param width Target width
	*/
	void setStrokeWidth(float width);
	/** @brief Get the current stroke width of the element */
	float getStrokeWidth() const;
	/**
	 * @brief Add a transformation to the element
	 * @param s New transformation (in string format)
	*/
	void addTransformation(const std::string &s);
	/** 
	 * @brief Set a new set of transformations to the elements
	 * @param transformations New set of transformations
	*/
	void setTransformation(const std::vector<std::string> &transformations);
	/** @brief Get the current set of transformations */
	std::vector<std::string> getTransformation() const;
	/**
	 * @brief Set the current fill gradient of the element
	 * @param grad Pointer to the allocated Gradient
	 */
	void setFillGradient(Gradient *grad);

	/** @brief Get the pointer to the current fill gradient of the element */
	Gradient *getFillGradient() const;

	/**
	 * @brief Set the current stroke gradient of the element
	 * @param grad Pointer to the allocated Gradient
	*/
	void setStrokeGradient(Gradient* grad);

	/** @brief Get the pointer to the current stroke gradient of the element */
	Gradient* getStrokeGradient() const;
};

#endif //SVG_RENDERING_ELEMENT_H
