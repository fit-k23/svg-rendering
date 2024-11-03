#include "Text.h"

/*
* @brief Default constructor
*/
Text::Text() : data(""), textAnchor("start"), fontStyle(""), fontSize(1.0) {}

/*
* @brief Parameterized constructor
* @note TODO change font style. What is raylib default font style ???
*/
Text::Text(const Vector2D<float>& position, const SVGColor& fillColor, const SVGColor& strokeColor,
	float strokeWidth, const std::string& data, float fontSize) : Element(position, fillColor, strokeColor, strokeWidth),
																	data(data), textAnchor("start"), fontStyle(""), fontSize(fontSize) {}

/*
* @brief Get type Text
*/
ElementType Text::getTypeName() { return ElementType::Text; }

/*
* @brief Print information of Text
*/
void Text::dbg() {
	std::cout << "[DEBUG TEXT]\n";
	std::cout << "Position: (" << position.x << ", " << position.y << ")\n";
	std::cout << "Data: " << data << '\n';
	std::cout << "Anchor: " << textAnchor << '\n';
	std::cout << "Font style: " << (fontStyle.empty() ? "default" : fontStyle) << '\n';
	std::cout << "Font size: " << fontSize << '\n';
	std::cout << "Stroke width: " << strokeWidth << '\n';
	std::cout << "Fill color: "; fillColor.output(); std::cout << '\n';
	std::cout << "Stroke color: "; strokeColor.output(); std::cout << '\n';
}

/*
* @brief Set data of text
* @param data new data for text
*/
void Text::setData(const std::string& data) { this->data = data; }

/*
* @brief Get data of text
* @note This function doesn't change any attributes
*/
std::string Text::getData() const { return data; }

/*
* @brief Set text anchor
* @param textAnchor new anchor for text
*/
void Text::setTextAnchor(const std::string& textAnchor) { this->textAnchor = textAnchor; }

/*
* @brief Get anchor of text
* @note This function doesn't change any attributes
*/
std::string Text::getTextAnchor() const { return textAnchor; }

/*
* @brief Set font style
* @param fontStyle new font style for text
*/
void Text::setFontStyle(const std::string& fontStyle) { this->fontStyle = fontStyle; }

/*
* @brief Get font style of text
* @note This function doesn't change any attributes
*/
std::string Text::getFontStyle() const { return fontStyle; }

/*
* @brief Set font size
* @param fontSize new font size for text
*/
void Text::setFontSize(float fontSize) { this->fontSize = fontSize; }

/*
* @brief Get font size of text
* @note This function doesn't change any attributes
*/
float Text::getFontSize() const { return fontSize; }
