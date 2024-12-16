#ifndef SVG_RENDERING_Ell_H
#define SVG_RENDERING_Ell_H

#include "../Element.h"
#include "../utils/SVGColor.h"
#include "../utils/Gradient.h"
#include "../utils/Vector2D.h"

/** @brief Class that represents ellipse shape in svg */
class SVGEllipse : public Element{
	Vector2D<float> radii;
public:
	SVGEllipse();
	/** @brief Full-parameterized constructor of SVGEllipse */
	SVGEllipse(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const Vector2D<float> &radii);

	/** @brief get type of object */
	ElementType getTypeName() override;
	/** @brief print all data of SVGEllipse */
	void dbg() override;

	/**
	 * @brief Get the bounding box of the ellipse
	 * @return Pair of top-left and bottom-right coordinate
	 */
	std::pair<Vector2D<float>, Vector2D<float>> getBoundingBox() const override;

	/**
	 * @brief Set the current horizontal and vertical radius of the ellipse to the target size
	 * @param radii Target radius
	 */
	void setRadii(const Vector2D<float> &radii);

	/**
	 * @brief Get the current horizontal and vertical radius of the ellipse
	 * @return Return the radius of the ellipse
	 */
	Vector2D<float> getRadii() const;
};

#endif //SVG_RENDERING_Ell_H
