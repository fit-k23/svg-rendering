#ifndef SVG_RENDERING_POLYLINE_H
#define SVG_RENDERING_POLYLINE_H

#include "../Element.h"
#include "../../api/Graphic.h"
#include <vector>
#include <string>

class Polyline : public Element {
private:
	std::vector<Line> lines;
public:
	/*
	* @brief Default constructor
	*/
	Polyline(); 

	/*
	* @brief Parameterized constructor
	*/
	Polyline(const Vector2D<double>& position, const SVGColor& fillColor, const SVGColor& strokeColor, double strokeWidth,
		const std::vector<Line>& lines);

	/*
	* @brief Copy constructor
	*/
	Polyline(const Polyline& other);

	/*
	* @brief Get type Line
	*/
	ElementType getTypeName() override;

	/*
	* @brief Print all information of Line
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
};

#endif //SVG_RENDERING_POLYLINE_H
