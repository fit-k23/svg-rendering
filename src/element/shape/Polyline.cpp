#include "Polyline.h"
/*
* @brief Default constructor
*/
Polyline::Polyline() : Element(), lines({}) {}

/*
* @brief Parameterized constructor
*/
Polyline::Polyline(const Vector2D<float>& position, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth,
	const std::vector<Line>& lines) : Element(position, fillColor, strokeColor, strokeWidth), lines(lines) {}

/*
* @brief Copy constructor
*/
Polyline::Polyline(const Polyline& other) {
	position = other.position;
	fillColor = other.fillColor;
	strokeColor = other.strokeColor;
	strokeWidth = other.strokeWidth;
	lines = other.lines;
}

/*
* @brief Get type Line
*/
ElementType Polyline::getTypeName() { return ElementType::Polyline; }

/*
* @brief Print all information of Line
*/
void Polyline::dbg() {
	std::cout << "[DEBUG POLYLINE]\n";
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
void Polyline::setLines(const std::vector<Line>& lines) { this->lines = lines;  }

/*
* @brief Add a line to vector
*/
void Polyline::addLines(const Line& line) { lines.push_back(line); }

/*
* @brief Get vector of lines
* @note This function doesn't change any attributes
*/
std::vector<Line> Polyline::getLines() const { return lines; }

