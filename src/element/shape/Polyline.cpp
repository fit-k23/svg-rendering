#include "Polyline.h"
#include "Line.h"

/*
* @brief Default constructor
*/
Polyline::Polyline() : Element(), points{}, fillRule(FillRule::NON_ZERO) {}

/*
* @brief Parameterized constructor
*/
Polyline::Polyline(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const std::vector<elements::Line> &lines) : Element(position, fillColor, strokeColor, strokeWidth), lines(lines), fillRule("nonzero") {}

/*
* @brief Parameterized constructor with fill rule parameter
*/
Polyline::Polyline(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const std::vector<Line> &lines, const std::string &fillRule) : Element(position, fillColor, strokeColor, strokeWidth), lines(lines), fillRule(fillRule) {}

/*
* @brief Copy constructor
*/
Polyline::Polyline(const Polyline &other)  : Element(other) {
	position = other.position;
	fillColor = other.fillColor;
	strokeColor = other.strokeColor;
	strokeWidth = other.strokeWidth;
	points = other.points;
}

/** @brief Get type Line */
ElementType Polyline::getTypeName() { return ElementType::Polyline; }

/** @brief Print all information of Line */
void Polyline::dbg() {
	Element::dbg();
	std::cout << "Fill rule: " << fillRule << '\n';
	std::cout << "Set of lines are ";
	for (int i = 0; i < (int) lines.size(); ++i) {
		std::cout << "(" << lines[i].getPosition().x << ", " << lines[i].getPosition().y << ") -> ";
		std::cout << "(" << lines[i].getEndPosition().x << ", " << lines[i].getEndPosition().y << ") ";
	}
}

/**
 * @brief Get bounding box of polyline
 * @return pair of top-left and bottom-right coordinate
 * @note This function doesn't change any attributes
*/
std::pair<Vector2D <float>, Vector2D<float>> Polyline::getBoundingBox() const {
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
* @brief Set the vector of points
*/
void Polyline::setLines(const std::vector<Line> &lines) { this->lines = lines; }

/*
* @brief Add a line to vector
*/
void Polyline::addLines(const Line &line) { lines.push_back(line); }

/*
* @brief Get vector of lines
* @note This function doesn't change any attributes
*/
std::vector<Line> Polyline::getLines() const { return lines; }

/*
* @brief Set fill rule
* @param fillRule new fill rule
*/
void Polyline::setFillRule(const std::string &fillRule) { this->fillRule = fillRule; }

/*
* @brief Get fill rule
* @return fill rule
*/
std::string Polyline::getFillRule() const { return fillRule; }
