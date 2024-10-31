#ifndef SVG_RENDERING_Rect_H
#define SVG_RENDERING_Rect_H

#include "../utils/Vector2D.h"
#include "../Element.h"
#include "../utils/SVGColor.h"

class Rect : public Element {
private:
	double width;
	double height;
	Vector2D<double> radii;
public:
	/*
	* @brief Default constructor
	*/
	Rect();

	/*
	* @brief Parameterized constructor
	* @param: position: vector2D position of Rect
	* @param: width: width of Rect
	* @param: height: height of Rect
	* @param: radii: radii of Rect
	* @param: fillColor: fill color of Rect
	* @param: strokeColor: stroke color of Rect
	* @param: strokeWidth: stroke width of Rect
	*/
	Rect(Vector2D<double> _position, const SVGColor& fillColor, const SVGColor& strokeColor, double strokeWidth, 
			  double width, double height, Vector2D<double>radii);

	/*
	* @brief Copy constructor
	*/
	Rect(const Rect& other);
	
	/*
	* @brief get type of Rect 
	* @return ElementType::Rect
	*/
	ElementType getTypeName() override;

	/*
	* @brief print data of Rect for debugging
	*/
	void dbg() override;

	/*
	* @brief set width of the Rect
	* @param: _width: passed width 
	*/
	void setWidth(double _width);

	/*
	* @brief set height of the Rect
	* @param: _height: passed height
	*/
	void setHeight(double _height);

	/*
	* @brief get width of the Rect
	* @return width of current Rect
	*/
	double getWidth() const;

	/*
	* @brief get height of the Rect
	* @return height of current Rect
	*/
	double getHeight() const;

	/*
	* @brief set radii of the Rect
	* @param: radii: passed-by-reference radii
	*/
	void setRadii(const Vector2D<double>& radii);

	/*
	* @brief get radii of the Rect
	* @return radii of current Rect
	*/
	Vector2D<double> getRadii() const;
};

#endif //SVG_RENDERING_Rect_H
