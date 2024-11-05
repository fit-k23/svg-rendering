#ifndef SVG_RENDERING_POLYLINE_H
#define SVG_RENDERING_POLYLINE_H

#include "../Element.h"
#include "../../api/Graphic.h"
#include <vector>
#include <string>

/*
* @brief Polyline class
* @note position is the first point of the polygon (first point of the first line)
*/

class Polyline : public Element {
private:
	std::vector<Line> lines;
	std::string fillRule;
public:
	/*
	* @brief Default constructor
	*/
	Polyline(); 

	/*
	* @brief Parameterized constructor
	*/
	Polyline(const Vector2D<float>& position, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth,
		const std::vector<Line>& lines);

	/*
	* @brief Parameterized constructor with fill rule parameter
	*/
	Polyline(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth,
		const std::vector<Line> &lines, const std::string &fillRule);


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
	* @brief Get bounding box of polyline
	* @return pair of top-left and bottom-right coordinate
	* @note This function doesn't change any attributes
	*/
	std::pair<Vector2D<float>, Vector2D<float>> getBoundingBox() const override;


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
	* @brief Set fill rule
	* @param fillRule new fill rule
	*/
	void setFillRule(const std::string& fillRule);

	/*
	* @brief Get fill rule
	* @return fill rule
	*/
	std::string getFillRule() const;

};

#endif //SVG_RENDERING_POLYLINE_H
