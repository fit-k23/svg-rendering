#ifndef SVG_RENDERING_TEXT_H
#define SVG_RENDERING_TEXT_H

#include "../Element.h"
#include "../../api/Graphic.h"
#include <string>

/*
* @brief Text Class
* @note All text object has a text-anchor (default to start)
* @note dx, dy (shift along Ox, Oy coordinates) is default to be zero
* @note dx, dy will be added to position so there are no attributes dx, dy
* @note rotation is set to 0 by default (no rotation)
* @note font size default to be 1
*/

class Text : public Element{
private:
	std::string data;
	std::string textAnchor;
	std::string fontStyle;
	double fontSize;
public:
	/*
	* @brief Default constructor
	*/
	Text();

	/*
	* @brief Parameterized constructor
	*/
	Text(const Vector2D<double>& position, const SVGColor& fillColor, const SVGColor& strokeColor,
		double strokeWidth, const std::string& data, double fontSize);

	/*
	* @brief Get type Text
	*/
	ElementType getTypeName() override;

	/*
	* @brief Print information of Text
	*/
	void dbg() override;

	/*
	* @brief Set data of text
	* @param data new data for text
	*/
	void setData(const std::string& data);
	
	/*
	* @brief Get data of text
	* @note This function doesn't change any attributes
	*/
	std::string getData() const;

	/*
	* @brief Set text anchor
	* @param textAnchor new anchor for text
	*/
	void setTextAnchor(const std::string& textAnchor);

	/*
	* @brief Get anchor of text
	* @note This function doesn't change any attributes
	*/
	std::string getTextAnchor() const;

	/*
	* @brief Set font style
	* @param fontStyle new font style for text
	*/
	void setFontStyle(const std::string& fontStyle);

	/*
	* @brief Get font style of text
	* @note This function doesn't change any attributes
	*/
	std::string getFontStyle() const;

	/*
	* @brief Set font size
	* @param fontSize new font size for text
	*/
	void setFontSize(double fontSize);

	/*
	* @brief Get font size of text
	* @note This function doesn't change any attributes
	*/
	double getFontSize() const;
};

#endif //SVG_RENDERING_TEXT_H
