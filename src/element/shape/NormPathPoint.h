#ifndef SVG_RENDERING_NORMPATHPOINT_H
#define SVG_RENDERING_NORMPATHPOINT_H

#include "PathPoint.h"

class NormPathPoint : public PathPoint {
private:

public:
	NormPathPoint(); 
	NormPathPoint(char cmd, const Vector2D<float> &pos);
	NormPathPoint(const NormPathPoint& other);
	void output() const override;
};

#endif // SVG_RENDERING_NORMPATHPOINT_H