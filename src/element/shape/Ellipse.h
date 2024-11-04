#ifndef SVG_RENDERING_ELLIPSE_H
#define SVG_RENDERING_ELLIPSE_H

#include "../Element.h"
#include "../utils/SVGColor.h"
#include "../utils/Gradient.h"
#include "../utils/Vector2D.h"

class Ellipse : public Element{
private:
	Vector2D<float> radii;
public:
	/**
	 * @brief Default Constructor
	 */
	Ellipse(); 

	/**
	 * @brief Full-parameterized constructor of ellipse
	 */
	Ellipse(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const Vector2D<float> &radii);

	/**
	 * @brief get type of object
	 * @return ElementType::Ellipse
	 */
	ElementType getTypeName() override;

	/**
	 * @brief print all data of Ellipse
	 */
	void dbg() override;


	/*
	* @brief Get bounding box of ellipse
	* @return pair of top-left and bottom-right coordinate
	* @note This function doesn't change any attributes
	*/
	std::pair<Vector2D<float>, Vector2D<float>> getBoundingBox() const override;

	/**
	 * @brief set radii
	 * @param radii update radii
	 */
	void setRadii(const Vector2D<float> &radii);

	/**
	 * @brief get radii
	 * @return radii
	 * @note This function doesn't change any attributes
	 */
	Vector2D<float> getRadii() const;
};

#endif //SVG_RENDERING_ELLIPSE_H
