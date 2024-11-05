#ifndef SVG_RENDERING_POLYGON_H
#define SVG_RENDERING_POLYGON_H

#include "../Element.h"
#include "../../api/Graphic.h"
#include <vector>
#include <string>

/*
* @brief Polygon class
* @note position vector2D in Polygon is the first point of polygon
* @note lines describe all edges of Polygon
*/
class Polygon : public Element{
private:
	std::vector<Line> lines;
	std::string fillRule;
public:
	/*
	* @brief Default constructor
	*/
	Polygon();

	/*
	* @brief Parameterized constructor
	*/
	Polygon(const Vector2D<float>& position, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth,
		const std::vector<Line>& lines);

	/*
	* @brief Parameterized constructor with fill rule parameter
	*/
	Polygon(const Vector2D<float>& position, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth,
		const std::vector<Line>& lines, const std::string &fillRule);


	/*
	* @brief Get type Polygon
	*/
	ElementType getTypeName() override;

	/*
	* @brief Print all information of Polygon
	*/
	void dbg() override;

	/*
	* @brief Get bounding box of polygon
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

#endif //SVG_RENDERING_POLYGON_H
