#include "Polygon.h"

/*
* @brief Default constructor
*/
Polygon::Polygon() : Element(), lines({}) {}

/*
* @brief Parameterized constructor
*/
Polygon::Polygon(const Vector2D<float>& position, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth,
				const std::vector<Line>& _lines) : Element(position, fillColor, strokeColor, strokeWidth), lines(_lines) {}

/*
* @brief Get type Polygon
*/
ElementType Polygon::getTypeName() { return ElementType::Polygon; }

/*
* @brief Print all information of Polygon
*/
void Polygon::dbg() {
	Element::dbg();
	std::cout << "Set of lines are ";
	for (int i = 0; i < (int)lines.size(); ++i) {
		std::cout << "(" << lines[i].getPosition().x << ", " << lines[i].getPosition().y << ") -> ";
		std::cout << "(" << lines[i].getEndPosition().x << ", " << lines[i].getEndPosition().y << ") ";
	}
}

/*
* @brief Get bounding box of polygon
* @return pair of top-left and bottom-right coordinate
* @note This function doesn't change any attributes
*/
std::pair<Vector2D<float>, Vector2D<float>> Polygon::getBoundingBox() const
{
	return std::pair<Vector2D<float>, Vector2D<float>>();
}

/*
* @brief Set the vector of lines
*/
void Polygon::setLines(const std::vector<Line>& lines) { this->lines = lines; }

/*
* @brief Add a line to vector
*/
void Polygon::addLines(const Line& line) { lines.push_back(line); }

/*
* @brief Get vector of lines
* @note This function doesn't change any attributes
*/
std::vector<Line> Polygon::getLines() const { return lines; }
