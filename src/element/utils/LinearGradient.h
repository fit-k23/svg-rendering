#ifndef SVG_RENDERING_LINEARGRADIENT_H
#define SVG_RENDERING_LINEARGRADIENT_H

#include "Gradient.h"
#include "Stop.h"
#include "Vector2D.h"

/**
 * @brief Linear gradient class.
 */
class LinearGradient : public Gradient {
private:
	Vector2D<float> pos[2];
public:
	/**
	 * @brief Default constructor.
	 */
	LinearGradient();

	/**
	 * @brief Simple constructor.
	 */
	LinearGradient(const std::string& id, const std::vector<std::string>& transforms, const std::string &units);

	/**
	 * @brief Complex constructor.
	 */
	LinearGradient(const std::string& id, const std::vector<std::string>& transforms, const std::string &units, Vector2D<float> pos1, Vector2D<float> pos2);

	/**
	 * @brief Get type of gradient
	 * @return string "linear"
	 * @note This function overrides from Gradient and doesn't change any attributes
	 */
	std::string getType() const override;

	/**
	 * @brief Print information of linear gradient .
	 * @note This function overrides from Gradient and doesn't change any attributes
	 */
	void dbg() const override;

	/**
	 * @brief Set new x[id] and y[id] with id = [0/1]
	 * @param id the id of coordinate, id = [0/1]
	 * @param pos the new Vector2D that contains new x[id] and y[id]
	 */
	void setPos(int id, const Vector2D<float> &newPos);


	/**
	 * @brief Get x[id] and y[id]  with id = [0/1]
	 * @return Vector2D that contains x[id] and y[id]
	 * @note This function doesn't change any attributes
	 */
	Vector2D<float> getPos(int id) const;
};

#endif // SVG_RENDERING_LINEARGRADIENT_H