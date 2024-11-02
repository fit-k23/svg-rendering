#ifndef SVG_RENDERING_RECT_H
#define SVG_RENDERING_RECT_H

#include "../utils/Vector2D.h"
#include "../Element.h"
#include "../utils/SVGColor.h"

class Rect : public Element {
private:
	float width;
	float height;
	Vector2D<float> radii;
public:
	/**
	* @brief Default constructor
	*/
	Rect();

	/**
	* @brief Parameterized constructor
	* @param: position: vector2D position of Rect
	* @param: width: width of Rect
	* @param: height: height of Rect
	* @param: radii: radii of Rect
	* @param: fillColor: fill color of Rect
	* @param: strokeColor: stroke color of Rect
	* @param: strokeWidth: stroke width of Rect
	*/
	Rect(Vector2D<float> _position, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth, float width, float height, Vector2D<float>radii);

	/**
	* @brief Copy constructor
	*/
	Rect(const Rect& other);
	
	/**
	* @brief get type of Rect 
	* @return ElementType::Rect
	*/
	ElementType getTypeName() override;

	/**
	* @brief print data of Rect for debugging
	*/
	void dbg() override;

	/**
	* @brief set width of the Rect
	* @param: _width: passed width 
	*/
	void setWidth(float _width);

	/**
	* @brief set height of the Rect
	* @param: _height: passed height
	*/
	void setHeight(float _height);

	/**
	* @brief get width of the Rect
	* @return width of current Rect
	*/
	float getWidth() const;

	/**
	* @brief get height of the Rect
	* @return height of current Rect
	*/
	float getHeight() const;

	/**
	* @brief set radii of the Rect
	* @param: radii: passed-by-reference radii
	*/
	void setRadii(const Vector2D<float>& radii);

	/**
	* @brief get radii of the Rect
	* @return radii of current Rect
	*/
	Vector2D<float> getRadii() const;
};

#endif //SVG_RENDERING_RECT_H
