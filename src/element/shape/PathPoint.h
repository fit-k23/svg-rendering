#ifndef SVG_RENDERING_PATHPOINT_H
#define SVG_RENDERING_PATHPOINT_H

#include "../utils/Vector2D.h"
#include <vector>
#include <algorithm>
#include <string>

class PathPoint {
private:
	char cmd;
	Vector2D<float> pos;
public:
	PathPoint();
	PathPoint(char cmd, const Vector2D<float> &pos);
	PathPoint(const PathPoint &other);
	virtual ~PathPoint() = default;
	void setCMD(char cmd); 
	char getCMD() const;
	void setPos(const Vector2D<float> &pos);
	Vector2D<float> getPos() const;
	virtual void output() const;
};

#endif // SVG_RENDERING_PATHPOINT_H