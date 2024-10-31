#ifndef SVG_RENDERING_ELLIPSE_H
#define SVG_RENDERING_ELLIPSE_H

#include "../Element.h"
#include "../utils/SVGColor.h"
#include "../utils/Gradient.h"
#include "../utils/Vector2D.h"

class Ellipse : public Element{
private:
	Vector2D<double> radii;
public:
	/**
	 * @brief Default Constructor
	 */
	Ellipse(); 

	/**
	 * @brief Full-parameterized constructor of ellipse
	 */
	Ellipse(const Vector2D<double>& _position, const SVGColor& fillColor, const SVGColor& strokeColor, double strokeWidth, const Vector2D<double>&radii);

	/**
	 * @brief get type of object
	 * @return ElementType::Ellipse
	 */
	ElementType getTypeName() override;

	/**
	 * @brief print all data of Ellipse
	 */
	void dbg() override;

	/**
	 * @brief set radii
	 * @param radii update radii
	 */
	void setRadii(const Vector2D<double> &radii);

	/**
	 * @brief get radii
	 * @return radii
	 */
	Vector2D<double> getRadii();
};

#endif //SVG_RENDERING_ELLIPSE_H
