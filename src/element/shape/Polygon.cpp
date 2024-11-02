#include "Polygon.h"

/*
* @brief Default constructor
*/
Polygon::Polygon() : Element(), lines({}) {}

/*
* @brief Parameterized constructor
*/
Polygon::Polygon(const Vector2D<double>& position, const SVGColor& fillColor, const SVGColor& strokeColor, double strokeWidth, 
				const std::vector<Line>& _lines) : Element(position, fillColor, strokeColor, strokeWidth), lines(_lines) {}

/*
* @brief Get type Polygon
*/
ElementType Polygon::getTypeName() { return ElementType::Polygon; }

/*
* @brief Print all information of Polygon
*/
void Polygon::dbg() {
	std::cout << "[DEBUG POLYGON]\n";
	std::cout << "Center: (" << position.x << ", " << position.y << ")\n";
	std::cout << "Set of lines are ";
	for (int i = 0; i < (int)lines.size(); ++i) {
		std::cout << "(" << lines[i].getPosition().x << ", " << lines[i].getPosition().y << ") -> ";
		std::cout << "(" << lines[i].getEndPosition().x << ", " << lines[i].getEndPosition().y << ") ";
	}
	std::cout << "Stroke width = " << strokeWidth << '\n';
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
