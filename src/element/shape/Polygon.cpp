#include "Polygon.h"

/*
* @brief Default constructor
*/
Polygon::Polygon() : Element(), lines({}) {}

/*
* @brief Parameterized constructor
*/
Polygon::Polygon(const SVGColor& fillColor, const SVGColor& strokeColor, double strokeWidth, 
				const std::vector<Line>& _lines) : Element(this->position = getCenter(_lines), fillColor, strokeColor, strokeWidth), 
				lines(_lines) {}

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
		std::cout << "(" << lines[i].getEndPosition().x << ", " << lines[i].getEndPosition().y << " ";
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

/*
* @brief Set center of polygon
* @param center new center of polygon
*/
void Polygon::setCenter(const Vector2D<double>& center) { setPosition(center); }

/*
* @brief Get center point
*/
Vector2D<double> Polygon::getCenter() const { return position; }

/*
* @brief Get center point with set of lines
*/
Vector2D<double> Polygon::getCenter(const std::vector<Line>& lines) const {
	double sumx = 0, sumy = 0;
	for (int i = 0; i < (int)lines.size(); ++i) {
		sumx += lines[i].getPosition().x;
		sumx += lines[i].getEndPosition().x;
		sumy += lines[i].getPosition().y;
		sumy += lines[i].getEndPosition().y;
	}
	sumx /= (double)((int)lines.size() * 2);
	sumy /= (double)((int)lines.size() * 2);
	return Vector2D(sumx, sumy);
}
