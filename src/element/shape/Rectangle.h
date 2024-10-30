#ifndef SVG_RENDERING_Rect_H
#define SVG_RENDERING_Rect_H

#include "../utils/Vector2D.h"
#include "../Element.h"
#include "../SVGColor.h"
#include "../../../lib/raylib/rlgl.h"

class Rect : public Element {
private:
	double width;
	double height;
	Vector2D<double> radii;
public:
	/*
	* @cmt: Default constructor
	*/
	Rect();

	/*
	* @cmt: Parameterized constructor
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
	* @cmt: get type of Rect 
	* @return: ElementType::Rect
	*/
	ElementType getTypeName() override;

	/*
	* @cmt: draw Rect
	*/
	void draw() override;

	/*
	* @cmt: print data of Rect for debugging
	*/
	void dbg() override;

	/*
	* @cmt: set width of the Rect
	* @param: _width: passed width 
	*/
	void setWidth(double _width);

	/*
	* @cmt: set height of the Rect
	* @param: _height: passed height
	*/
	void setHeight(double _height);

	/*
	* @cmt: get width of the Rect
	* @return: width of current Rect
	*/
	double getWidth();

	/*
	* @cmt: get height of the Rect
	* @return: height of current Rect
	*/
	double getHeight();

	/*
	* @cmt: set radii of the Rect
	* @param: radii: passed-by-reference radii
	*/
	void setRadii(const Vector2D<double>& radii);

	/*
	* @cmt: get radii of the Rect
	* @return: radii of current Rect
	*/
	Vector2D<double> getRadii();
};

#endif //SVG_RENDERING_Rect_H
