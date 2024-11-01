#ifndef SVG_RENDERING_POLYGON_H
#define SVG_RENDERING_POLYGON_H

#include "../Element.h"
#include "../../api/Graphic.h"
#include <vector>
#include <string>

/*
* @brief Polygon class
* @note position vector2D in Polygon is the center of polygon
* @note lines describe all edges of Polygon
*/
class Polygon : public Element{
private:
	std::vector<Line> lines;
public:
	/*
	* @brief Default constructor
	*/
	Polygon();

	/*
	* @brief Parameterized constructor
	*/
	Polygon(const SVGColor& fillColor, const SVGColor& strokeColor, double strokeWidth,
		const std::vector<Line>& lines);

	/*
	* @brief Get type Polygon
	*/
	ElementType getTypeName() override;

	/*
	* @brief Print all information of Polygon
	*/
	void dbg() override;

	/*
	* @brief Set the vector of lines
	*/
	void setLines(const std::vector<Line>& lines);

	/*
	* @brief Add a line to vector
	*/
	void addLines(const Line& line);

	/*
	* @brief Get vector of lines
	* @note This function doesn't change any attributes
	*/
	std::vector<Line> getLines() const;

	/*
	* @brief Set center of polygon
	* @param center new center of polygon
	*/
	void setCenter(const Vector2D<double>& center); 

	/*
	* @brief Get center point
	*/
	Vector2D<double> getCenter() const;

	/*
	* @brief Get center point with set of lines
	*/
	Vector2D<double> getCenter(const std::vector<Line>& lines) const;
};

#endif //SVG_RENDERING_POLYGON_H
