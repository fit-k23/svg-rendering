#ifndef SVG_RENDERING_NORMPATHPOINT_H
#define SVG_RENDERING_NORMPATHPOINT_H

#include "PathPoint.h"

/**
 * @brief Class that represents the move-to, line-to command in svg path
 * @note We define our own protocol that those are normal points in svg path
 * @note This class inherits from PathPoint class
*/

class NormPathPoint : public PathPoint {
public:
	NormPathPoint(); 
	NormPathPoint(char cmd, const Vector2D<float> &pos);
	NormPathPoint(const NormPathPoint &other);
	void output() const override;
	std::string getPointType() const override;
};

#endif // SVG_RENDERING_NORMPATHPOINT_H