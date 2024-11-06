#ifndef SVG_RENDERING_RECT_H
#define SVG_RENDERING_RECT_H

#include "../utils/Vector2D.h"
#include "../Element.h"
#include "../utils/SVGColor.h"

class Rectangle : public Element{
private:
	float width;
	float height;
	Vector2D<float> radii;
public:
	/** @brief Default constructor */
	Rectangle();

	/**
	 * @brief Parameterized constructor
	 * @param: position: vector2D position of Rectangle
	 * @param: width: width of Rectangle
	 * @param: height: height of Rectangle
	 * @param: radii: radii of Rectangle
	 * @param: fillColor: fill color of Rectangle
	 * @param: strokeColor: stroke color of Rectangle
	 * @param: strokeWidth: stroke width of Rectangle
	*/
	Rectangle(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, float width, float height, const Vector2D<float> &radii);

	/** @brief Copy constructor */
	Rectangle(const Rectangle &other);

	/**
	 * @brief get type of Rectangle
	 * @return ElementType::Rectangle
	*/
	ElementType getTypeName() override;

	/**
	 * @brief print data of Rectangle for debugging
	*/
	void dbg() override;

	/**
	 * @brief Get bounding box of rect
	 * @return pair of top-left and bottom-right coordinate
	 * @note This function doesn't change any attributes
	*/
	std::pair<Vector2D < float>, Vector2D<float>> getBoundingBox()
	const override;

	/**
	 * @brief set width of the Rectangle
	 * @param: _width: passed width
	*/
	void setWidth(float _width);

	/**
	 * @brief set height of the Rectangle
	 * @param: _height: passed height
	*/
	void setHeight(float _height);

	/**
	 * @brief get width of the Rectangle
	 * @return width of current Rectangle
	*/
	float getWidth() const;

	/**
	 * @brief get height of the Rectangle
	 * @return height of current Rectangle
	*/
	float getHeight() const;

	/**
	 * @brief set radii of the Rectangle
	 * @param: radii: passed-by-reference radii
	*/
	void setRadii(const Vector2D<float> &radii);

	/**
	 * @brief get radii of the Rectangle
	 * @return radii of current Rectangle
	*/
	Vector2D<float> getRadii() const;
};

#endif //SVG_RENDERING_RECT_H
