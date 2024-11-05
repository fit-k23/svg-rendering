#include "Polygon.h"
#include "../utils/FillRule.h"

/*
* @brief Default constructor
*/
Polygon::Polygon() : Element(), points{}, fillRule(elements::FillRule::NON_ZERO) {}

/** @brief Parameterized constructor */
Polygon::Polygon(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const std::vector<Vector2D<float>> &_points) : Element(position, fillColor, strokeColor, strokeWidth), points(_points) {}

/** @brief Parameterized constructor with fill rule parameter */
Polygon::Polygon(const Vector2D<float> &_position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const std::vector<Vector2D<float>> &_points, const elements::FillRule &fillRule) : Element(_position, fillColor, strokeColor, strokeWidth), points(_points), fillRule(fillRule) {}


/*
* @brief Get type Polygon
*/
ElementType Polygon::getTypeName() { return ElementType::Polygon; }

/*
* @brief Print all information of Polygon
*/
void Polygon::dbg() {
	Element::dbg();
	std::cout << "Fill rule: " << (fillRule == elements::FillRule::NON_ZERO ? "nonzero" : "evenodd") << '\n';
	std::cout << "Set of lines are ";
	for (int i = 0; i < (int) points.size(); ++i) {
		// TODO: correctly debug Polygon
//		std::cout << "(" << lines[i].getPosition().x << ", " << lines[i].getPosition().y << ") -> ";
//		std::cout << "(" << lines[i].getEndPosition().x << ", " << lines[i].getEndPosition().y << ") ";
	}
}

/**
 * @brief Get bounding box of polygon
 * @return pair of top-left and bottom-right coordinate
 * @note This function doesn't change any attributes
*/
std::pair<Vector2D<float>, Vector2D<float>> Polygon::getBoundingBox() const {
	Vector2D<float> topLeft = {99999.0f, 99999.0f};
	Vector2D<float> bottomRight = {-99999.0f, -99999.0f};
	for (int i = 0; i < (int) points.size(); ++i) {
		Vector2D<float> sta = points[i];
		Vector2D<float> fin = points[(i + 1) % points.size()];
		topLeft.x = std::min(topLeft.x, std::min(sta.x, fin.x));
		bottomRight.x = std::max(bottomRight.x, std::max(sta.x, fin.x));
		topLeft.y = std::min(topLeft.y, std::min(sta.y, fin.y));
		bottomRight.y = std::max(bottomRight.y, std::max(sta.y, fin.y));
	}
	topLeft.x += strokeWidth / 2.0f;
	topLeft.y += strokeWidth / 2.0f;
	bottomRight.x += strokeWidth / 2.0f;
	bottomRight.y += strokeWidth / 2.0f;
	return {topLeft, bottomRight};
}

/*
* @brief Set the vector of lines
*/
void Polygon::setPoints(const std::vector<Vector2D<float>> &_points) { this->points = _points; }

/*
* @brief Add a line to vector
*/
void Polygon::addPoints(const Vector2D<float> &point) { points.push_back(point); }

/*
* @brief Get vector of lines
* @note This function doesn't change any attributes
*/
std::vector<Line> Polygon::getLines() const { return lines; }

/*
* @brief Set fill rule
* @param fillRule new fill rule
*/
void Polygon::setFillRule(const std::string &fillRule) { this->fillRule = fillRule; }

/*
* @brief Get fill rule
* @return fill rule
*/
std::string Polygon::getFillRule() const { return fillRule; }

