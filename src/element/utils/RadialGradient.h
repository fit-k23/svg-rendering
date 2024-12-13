#ifndef SVG_RENDERING_RADIAL_GRADIENT_H
#define SVG_RENDERING_RADIAL_GRADIENT_H

#include "Gradient.h"
#include "Stop.h"
#include "Vector2D.h"

using std::string;
using std::vector;

class RadialGradient : public Gradient{
	Vector2D<float> pos;
	float radius;
	Vector2D<float> focal;
public:
	RadialGradient();
	RadialGradient(const string &id, const vector<string> &transforms, const string &units);
	RadialGradient(const string &id, const vector<string> &transforms, const string &units, const Vector2D<float> &pos, float radius, const Vector2D<float> &focal);

	GradientType getType() const override { return GradientType::Radial; };

	void dbg() const override;
	/**
	 * @brief Set new cx and cy
	 * @param pos the new Vector2D that contains new cx and cy
	 */
	void setPos(const Vector2D<float> &pos);
	/**
	 * @brief Corresponds to attribute ‘cx’ and 'cy' on the given ‘radialGradient’ element
	 * @return Vector2D that contains cx and cy.
	 */
	Vector2D<float> getPos() const;
	/**
	 * @brief Set current radius of the radical gradient to target radius
	 * @param radius Target radius
	 */
	void setRadius(float radius);
	/** @brief Corresponds to attribute ‘r’ on the given ‘radialGradient’ element */
	float getRadius() const;
	/** @brief Get radius */
	void setFocal(const Vector2D<float> &focal);
	/**
	 * @brief Corresponds to attribute ‘fx’ and 'fy' on the given ‘radialGradient’ element.
	 * @return Vector2D that contains fx and fy.
	 */
	Vector2D<float> getFocal() const;
};

#endif
