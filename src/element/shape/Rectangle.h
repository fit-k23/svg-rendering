#ifndef SVG_RENDERING_RECT_H
#define SVG_RENDERING_RECT_H

#include "../utils/Vector2D.h"
#include "../Element.h"
#include "../utils/SVGColor.h"

class SVGRect : public Element{
private:
	float width;
	float height;
	Vector2D<float> radii;
public:
	/** @brief Default constructor */
	SVGRect();

	/**
	 * @brief Parameterized constructor
	 * @param: position: vector2D position of SVGRect
	 * @param: width: width of SVGRect
	 * @param: height: height of SVGRect
	 * @param: radii: radii of SVGRect
	 * @param: fillColor: fill color of SVGRect
	 * @param: strokeColor: stroke color of SVGRect
	 * @param: strokeWidth: stroke width of SVGRect
	*/
	SVGRect(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, float width, float height, const Vector2D<float> &radii);

	/** @brief Copy constructor */
	SVGRect(const SVGRect &other);

	/**
	 * @brief get type of SVGRect
	 * @return ElementType::SVGRect
	*/
	ElementType getTypeName() override;

	/**
	 * @brief print data of SVGRect for debugging
	*/
	void dbg() override;

	/**
	 * @brief Get bounding box of svgrect
	 * @return pair of top-left and bottom-right coordinate
	 * @note This function doesn't change any attributes
	*/
	std::pair<Vector2D < float>, Vector2D<float>> getBoundingBox()
	const override;

	/**
	 * @brief set width of the SVGRect
	 * @param: _width: passed width
	*/
	void setWidth(float _width);

	/**
	 * @brief set height of the SVGRect
	 * @param: _height: passed height
	*/
	void setHeight(float _height);

	/**
	 * @brief get width of the SVGRect
	 * @return width of current SVGRect
	*/
	float getWidth() const;

	/**
	 * @brief get height of the SVGRect
	 * @return height of current SVGRect
	*/
	float getHeight() const;

	/**
	 * @brief set radii of the SVGRect
	 * @param: radii: passed-by-reference radii
	*/
	void setRadii(const Vector2D<float> &radii);

	/**
	 * @brief get radii of the SVGRect
	 * @return radii of current SVGRect
	*/
	Vector2D<float> getRadii() const;
};

#endif //SVG_RENDERING_RECT_H
