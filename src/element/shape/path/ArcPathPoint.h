#ifndef SVG_RENDERING_ARCPATHPOINT_H
#define SVG_RENDERING_ARCPATHPOINT_H

#include "PathPoint.h"

/**
 * @brief Class that represents the arc drawing in path
 * @note This class inherits from PathPoint class
 */

class ArcPathPoint final : public PathPoint {
	Vector2D<float> radii;	// <-- radii of the ellipse
	float xRotation;		// <-- rotation (in degree) of the arc relative to the x-axis
	bool largeArcFlag;      // <-- decide whether < 180 degree (small arc) or > 180 degree (large arc)
	bool sweepFlag;         // <-- clockwise (1) or counterclockwise (0)
public:
	ArcPathPoint();
	ArcPathPoint(char cmd, const Vector2D<float> &pos);
	ArcPathPoint(char cmd, const Vector2D<float> &pos, const Vector2D<float> &radii, float xRotation, bool largeArcFlag, bool sweepFlag);
	ArcPathPoint(const ArcPathPoint &other) = default;
	/**
	 * @brief Setter method to set new radii
	 * @param radii new radii
	 */
	void setRadii(const Vector2D<float> &radii);
	/** @brief Getter method to get the radii */
	Vector2D<float> getRadii() const;
	/**
	 * @brief Setter method to set new x-axis rotation
	 * @param xRotation new x-axis rotation
	 */
	void setXRotation(float xRotation);
	/** @brief Getter method to get the x-axis rotation */
	float getXRotation() const;
	/**
	 * @brief Setter method to set new large-arc-flag
	 * @param largeArcFlag new large-arc-flag
	 */
	void setLargeArcFlag(bool largeArcFlag);
	/** @brief Getter method to get the large-arc-flag */
	bool getLargeArcFlag() const;
	/**
	 * @brief Setter method to set new sweep flag
	 * @param sweepFlag new sweep flag
	 */
	void setSweepFlag(bool sweepFlag);
	/** @brief Getter method to get the sweep flag */
	bool getSweepFlag() const;
	/** @brief Print information of arc-type point */
	void output() const override;
	std::string getPointType() const override;
};

#endif
