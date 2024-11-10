#ifndef SVG_RENDERING_PATH_H
#define SVG_RENDERING_PATH_H

#include "../Element.h"

struct Point {
	char instruction;
	Vector2D<float> pos;
	Vector2D<float> radii = { 0.0f, 0.0f };
	float xRotation = 0.0f;
	bool largeArcFlag = false;
	bool sweepFlag = false;
};

class SVGPath : public Element{
private:
	std::vector<Point> points;
public:
	/*
	* @brief Default constructor for path
	*/
	SVGPath();

	/*
	* @brief Get type path
	* @return ElementType::Path
	* @note This function is overrided
	*/
	ElementType getTypeName() override;

	/*
	* @brief Print all information of path
	* @note This function is overrided
	*/
	void dbg() override;

	/*
	* @brief Get bounding box of path object
	* @note This function is overrided and does not change any attributes
	*/
	std::pair<Vector2D<float>, Vector2D<float>> getBoundingBox() const override;
};

#endif //SVG_RENDERING_PATH_H
