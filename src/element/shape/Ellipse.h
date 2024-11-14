#ifndef SVG_RENDERING_Ell_H
#define SVG_RENDERING_Ell_H

#include "../Element.h"
#include "../utils/SVGColor.h"
#include "../utils/Gradient.h"
#include "../utils/Vector2D.h"

class SVGEllipse : public Element{
	Vector2D<float> radii;

public:
	/** @brief Default Constructor */
	SVGEllipse();

	/** @brief Full-parameterized constructor of SVGEllipse */
	SVGEllipse(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const Vector2D<float> &radii);

	/**
	 * @brief get type of object
	 * @return ElementType::SVGEllipse
	*/
	ElementType getTypeName() override;

	/** @brief print all data of SVGEllipse */
	void dbg() override;

	/**
	 * @brief Get bounding box of SVGEllipse
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

#endif //SVG_RENDERING_Ell_H
