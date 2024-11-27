#ifndef SVG_RENDERING_RADIALGRADIENT_H
#define SVG_RENDERING_RADIALGRADIENT_H

#include "Gradient.h"
#include "Stop.h"
#include "Vector2D.h"

class RadialGradient : public Gradient{
	Vector2D<float> pos;
	float radius;
	Vector2D<float> focal;
public:
	RadialGradient();
	RadialGradient(const std::string &id, const std::vector<std::string> &transforms, const std::string &units);
	RadialGradient(const std::string &id, const std::vector<std::string> &transforms, const std::string &units, const Vector2D<float> &pos, float radius, const Vector2D<float> &focal);
	std::string getType() const override;
	void dbg() const override;
	/**
	 * @brief Set new cx and cy
	 * @param pos the new Vector2D that contains new cx and cy
	*/
	void setPos(const Vector2D<float> &pos);
	/**
	 * @brief Get cx and cy
	 * @return Vector2D that contains cx and cy.
	*/
	Vector2D<float> getPos() const;
	/**
	 * @brief Set current radius of the radical gradient to target radius
	 * @param radius Target radius
	*/
	void setRadius(float radius);
	/** @brief Get radius */
	float getRadius() const;
	/** @brief Get radius */
	void setFocal(const Vector2D<float> &focal);
	/**
	 * @brief Get fx and fy
	 * @return Vector2D that contains fx and fy.
	*/
	Vector2D<float> getFocal() const;
};

#endif // SVG_RENDERING_RADIALGRADIENT_H
