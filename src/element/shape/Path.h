#ifndef SVG_RENDERING_PATH_H
#define SVG_RENDERING_PATH_H

#include "../Element.h"
#include "../utils/FillRule.h"

struct PathPoint {
	char cmd;								// <-- type of instruction
	Vector2D<float> pos;					// <-- end position
	Vector2D<float> cen[2] = { {}, {} };	// <-- center points for bezier curve
	Vector2D<float> radii = { 0.0f, 0.0f };	// <-- radii of the ellipse
	float xRotation = 0.0f;					// <-- rotation (in degree) of the arc relative to the x-axis
	bool largeArcFlag = false;              // <-- decide whether < 180 degree (small arc) or > 180 degree (large arc)
	bool sweepFlag = false;                 // <-- clockwise (1) or counterclockwise (0) 

	/** @brief Default constructor */
	PathPoint();

	/** @brief Parameterized constructor for normal point */
	PathPoint(char cmd, const Vector2D<float>& pos);

	/** @brief Parameterized constructor for arc point */
	PathPoint(char cmd, Vector2D<float> pos, Vector2D<float> radii, float xRotation, bool largeArcFlag, bool sweepFlag);

	/** @brief Parameterized constructor for quadratic bezier curve */
	PathPoint(char cmd, Vector2D<float> pos, Vector2D<float> cen);

	/** @brief Parameterized constructor for cubic bezier curve */
	PathPoint(char cmd, Vector2D<float> pos, Vector2D<float> cen1, Vector2D<float> cen2);

	/** @brief Print information of a point */
	void output();
};

class SVGPath : public Element{
private:
	std::vector<PathPoint> points;
	FillRule fillRule;
public:
	/** @brief Default constructor for path */
	SVGPath();

	/**
	 * @brief Parameterized constructor for path
	 * @param points new vector of points
	*/
	SVGPath(const Vector2D<float>& position, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth, const std::vector<PathPoint> &points, FillRule fillRule);


	/**
	 * @brief Get type path
	 * @return ElementType::Path
	 * @note This function is override
	*/
	ElementType getTypeName() override;

	/**
	 * @brief Print all information of path
	 * @note This function is override
	*/
	void dbg() override;

	/**
	 * @brief Get bounding box of path object
	 * @note This function is override and does not change any attributes
	*/
	std::pair<Vector2D<float>, Vector2D<float>> getBoundingBox() const override;

	/*
	 * @brief Set points for path
	 * @param points new set of points for path
	*/
	void setPoints(const std::vector<PathPoint>& points); 

	/*
	* @brief Get points for path
	* @note This function doesn't change any attributes
	*/
	std::vector<PathPoint> getPoints() const;

	/*
	* @brief Add a point to path
	* @param point new point
	*/
	void addPoint(const PathPoint& point);

	/*
	* @brief Set fill rule for path
	* @param fillRule new fill rule
	*/
	void setFillRule(FillRule fillRule);

	/*
	* @brief Get fill rule for path
	* @return fill rule
	* @note This function doesn't change any attributes
	*/
	FillRule getFillRule() const;

};

#endif //SVG_RENDERING_PATH_H
