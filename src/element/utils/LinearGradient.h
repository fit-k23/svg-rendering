#ifndef SVG_RENDERING_LINEARGRADIENT_H
#define SVG_RENDERING_LINEARGRADIENT_H

#include "Gradient.h"
#include "Stop.h"
#include "Vector2D.h"

class LinearGradient : public Gradient{
	Vector2D<float> pos[2];
	// x1, x2, y1, y2
	// default: 0 1 0 0
public:
	LinearGradient();
	LinearGradient(const std::string &id, const std::vector<std::string> &transforms, const std::string &units);
	LinearGradient(const std::string &id, const std::vector<std::string> &transforms, const std::string &units, const Vector2D<float> &pos1, const Vector2D<float> &pos2);
	/**
	 * @brief Get type of gradient
	 * @return string "linear"
	 * @note This function overrides from Gradient and doesn't change any attributes
	*/
	std::string getType() const override;
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
	float getX1() const;
	float getX2() const;
	float getY1() const;
	float getY2() const;
};

#endif // SVG_RENDERING_LINEARGRADIENT_H