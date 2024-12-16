#ifndef SVG_RENDERING_RECT_H
#define SVG_RENDERING_RECT_H

#include "../Element.h"
#include "../utils/Vector2D.h"
#include "../utils/SVGColor.h"

/** @brief Class that represents rectangle in svg */
class SVGRect final : public Element{
	float width;
	float height;
	Vector2D<float> radii;
public:
	SVGRect();

	/**
	 * @brief Parameterized constructor
	 * @param position: vector2D position of SVGRect
	 * @param width: width of SVGRect
	 * @param height: height of SVGRect
	 * @param radii: radii of SVGRect
	 * @param fillColor: fill color of SVGRect
	 * @param strokeColor: stroke color of SVGRect
	 * @param strokeWidth: stroke width of SVGRect
	 */
	SVGRect(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, float width, float height, const Vector2D<float> &radii);
	SVGRect(const SVGRect &other) = default;

	/** @brief get type of SVGRect */
	ElementType getTypeName() override;

	/** @brief print data of SVGRect for debugging */
	void dbg() override;

	/**
	 * @brief Get bounding box of this rectangle
	 * @return pair of top-left and bottom-right coordinate
	 * @note This function doesn't change any attributes
	 */
	std::pair<Vector2D<float>, Vector2D<float>> getBoundingBox() const override;

	/**
	 * @brief set width of the SVGRect
	 * @param: width: passed width
	 */
	void setWidth(float width);

	/**
	 * @brief set height of the SVGRect
	 * @param: height: passed height
	 */
	void setHeight(float height);

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
