#ifndef SVG_RENDERING_ARCPATHPOINT_H
#define SVG_RENDERING_ARCPATHPOINT_H

#include "PathPoint.h"

class ArcPathPoint : public PathPoint {
private:
	Vector2D<float> radii;	// <-- radii of the ellipse
	float xRotation;		// <-- rotation (in degree) of the arc relative to the x-axis
	bool largeArcFlag;      // <-- decide whether < 180 degree (small arc) or > 180 degree (large arc)
	bool sweepFlag;         // <-- clockwise (1) or counterclockwise (0) 
public:
	ArcPathPoint();
	ArcPathPoint(char cmd, const Vector2D<float>& pos);
	ArcPathPoint(char cmd, const Vector2D<float>& pos, const Vector2D<float> &radii, float xRotation, bool largeArcFlag, bool sweepFlag);
	ArcPathPoint(const ArcPathPoint& other);
	void setRadii(const Vector2D<float> &radii);
	Vector2D<float> getRadii() const;
	void setXRotation(float xRotation);
	float getXRotation() const;
	void setLargeArcFlag(bool largeArcFlag);
	bool getLargeArcFlag() const;
	void setSweepFlag(bool sweepFlag);
	bool getSweepFlag() const;
	void output() const override;

	std::string getPointType() const override;
};

#endif 