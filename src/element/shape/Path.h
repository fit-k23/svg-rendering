#ifndef SVG_RENDERING_PATH_H
#define SVG_RENDERING_PATH_H

#include "../Element.h"
#include "../utils/FillRule.h"
#include "PathPoint.h"

/**
 * @brief Class that represents path in svg
 * @note This class has a vector containing four types of points in svg path
 * @note This class inherits from Element class
 */

class SVGPath : public Element{
private:
	std::vector<PathPoint *> points;
	FillRule fillRule;
public:
	/** @brief Default constructor for path */
	SVGPath();

	/**
	 * @brief Parameterized constructor for path
	 * @param points new vector of points
	 */
	SVGPath(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const std::vector<PathPoint *> &points, FillRule fillRule);

	/**
	 * @brief Destructor to delete PathPoint memory.
	 */
	~SVGPath();

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

	/**
	 * @brief Set points for path
	 * @param points new set of points for path
	 */
	void setPoints(const std::vector<PathPoint *> &points); 

	/**
	 * @brief Get points for path
	 * @note This function doesn't change any attributes
	 */
	std::vector<PathPoint *> getPoints() const;

	/**
	 * @brief Add a point to path
	 * @param point new point
	 */
	void addPoint(PathPoint* point);

	/**
	 * @brief Set fill rule for path
	 * @param fillRule new fill rule
	 */
	void setFillRule(FillRule fillRule);

	/**
	 * @brief Get fill rule for path
	 * @return fill rule
	 * @note This function doesn't change any attributes
	 */
	FillRule getFillRule() const;
};

#endif //SVG_RENDERING_PATH_H
