#ifndef SVG_RENDERING_LINEAR_GRADIENT_H
#define SVG_RENDERING_LINEAR_GRADIENT_H

#include "Gradient.h"
#include "Vector2D.h"

using std::string;
using std::vector;

/*
Percentages are allowed for ‘x1’, ‘y1’, ‘x2’ and ‘y2’. For gradientUnits="userSpaceOnUse", percentages represent values relative to the current 
viewport. For gradientUnits="objectBoundingBox", percentages represent values relative to the bounding box for the object.

If ‘x1’ = ‘x2’ and ‘y1’ = ‘y2’, then the area to be painted will be painted as a single color using the color and opacity of the last gradient 
stop.
*/
class LinearGradient : public Gradient{
	Vector2D<float> pos[2];
	// x1, x2, y1, y2
	// default: 0 1 0 0
public:
	LinearGradient();
	LinearGradient(const string &id, const vector<string> &transforms, const string &units);
	LinearGradient(const string &id, const vector<string> &transforms, const string &units, const Vector2D<float> &pos1, const Vector2D<float> &pos2);
	/**
	 * @brief Get type of gradient
	 * @return GradientType::Linear
	 */
	GradientType getType() const override { return GradientType::Linear; };
	void dbg() const override;
	/**
	 * @brief Set new x[id] and y[id] with id = [0/1]
	 * @param id the id of coordinate, id = [0/1]
	 * @param newPos the new Vector2D that contains new x[id] and y[id]
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

#endif