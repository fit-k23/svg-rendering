#ifndef SVG_RENDERING_RADIALGRADIENT_H
#define SVG_RENDERING_RADIALGRADIENT_H

#include "Gradient.h"
#include "Stop.h"
#include "Vector2D.h"

/**
 * @brief Radial gradient class.
 */
class RadialGradient : public Gradient {
private:
	Vector2D<float> pos;
	float radius;
	Vector2D<float> focal;
public:
	/**
	 * @brief Default constructor.
	 */
	RadialGradient();

	/**
	 * @brief Simple constructor.
	 */
	RadialGradient(const std::string& id, const std::vector<std::string>& transforms, const std::string &units);

	/**
	 * @brief Complex constructor.
	 */
	RadialGradient(const std::string& id, const std::vector<std::string>& transforms, const std::string &units, const Vector2D<float> &pos, float radius, const Vector2D<float> &focal);

	/**
	 * @brief Get type of gradient
	 * @return string "radial"
	 * @note This function overrides from Gradient and doesn't change any attributes
	 */
	std::string getType() const override;

	/**
	 * @brief Print information of radial gradient .
	 * @note This function overrides from Gradient and doesn't change any attributes
	 */
	void dbg() const override;

	/**
	 * @brief Set new cx and cy
	 * @param pos the new Vector2D that contains new cx and cy
	 */
	void setPos(const Vector2D<float>& pos);

	/**
	 * @brief Get cx and cy 
	 * @return Vector2D that contains cx and cy.
	 * @note This function doesn't change any attributes
	 */
	Vector2D<float> getPos() const;

	/**
	 * @brief Set new radius
	 * @param radius new radius
	 */
	void setRadius(float radius);

	/**
	 * @brief Get radius
	 * @return float
	 * @note This function doesn't change any attributes
	 */
	float getRadius() const;

	/**
	 * @brief Set new fx and fy
	 * @param focal the new Vector2D that contains new fx and fy
	 */
	void setFocal(const Vector2D<float>& focal);

	/**
	 * @brief Get fx and fy
	 * @return Vector2D that contains fx and fy.
	 * @note This function doesn't change any attributes
	 */
	Vector2D<float> getFocal() const;
};


#endif // SVG_RENDERING_RADIALGRADIENT_H