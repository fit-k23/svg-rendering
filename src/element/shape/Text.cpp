#include "Text.h"

/** @brief Default constructor */
SVGText::SVGText() : data(""), textAnchor("start"), fontStyle(""), fontSize(1.0), offset(10.0) {}

/**
 * @brief Parameterized constructor
 * @note TODO change font style. What is raylib default font style ???
*/
SVGText::SVGText(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const std::string &data, float fontSize) : Element(position, fillColor, strokeColor, strokeWidth), data(data), textAnchor("start"), fontStyle(""), fontSize(fontSize), offset(10.0) {}

/** @brief Get type Text */
ElementType SVGText::getTypeName() { return ElementType::Text; }

/** @brief Print information of Text */
void SVGText::dbg() {
	Element::dbg();
	std::cout << "Data: " << data << '\n';
	std::cout << "Anchor: " << textAnchor << '\n';
	std::cout << "Font style: " << (fontStyle.empty() ? "default" : fontStyle) << '\n';
	std::cout << "Font size: " << fontSize << '\n';
}

/**
 * @brief Get bounding box of text
 * @return pair of top-left and bottom-right coordinate
 * @note This function doesn't change any attributes
*/
std::pair<Vector2D<float>, Vector2D<float>>

SVGText::getBoundingBox() const {
	float actualY = position.y - fontSize + offset;
	float actualX = position.x;
	if (textAnchor == "middle" || textAnchor == "end") {
		if (textAnchor == "middle") actualX -= dataSize.x / 2.0f;
		actualX -= dataSize.x;
	}
	return {Vector2D<float>(actualX, actualY), Vector2D<float>(actualX + dataSize.x, actualY + dataSize.y)};
}

/**
 * @brief Set data size
 * @param dataSize new data size including width and height of text based on font
*/
void SVGText::setDataSize(const Vector2D<float> &_dataSize) { this->dataSize = _dataSize; }

/** @brief Set default data size with no font */
void SVGText::setDataSize() {
//	Vector2D<float> dataSize = { (float)MeasureText(&data[0], fontSize), fontSize }; // TODO: Correctly finding the text size in GDI+
	Vector2D<float> _dataSize = {0, 0};
	this->dataSize = _dataSize;
}

/**
 * @brief Get data size based on font
 * @param font font family
 * @note This function doesn't change any attributes
*/
Vector2D<float> SVGText::getDataSize() const { return dataSize; }

/**
 * @brief Set data of text
 * @param data new data for text
*/
void SVGText::setData(const std::string &data) { this->data = data; }

/**
 * @brief Get data of text
 * @note This function doesn't change any attributes
*/
std::string SVGText::getData() const { return data; }

/**
 * @brief Set text anchor
 * @param textAnchor new anchor for text
*/
void SVGText::setTextAnchor(const std::string &textAnchor) { this->textAnchor = textAnchor; }

/**
 * @brief Get anchor of text
 * @note This function doesn't change any attributes
*/
std::string SVGText::getTextAnchor() const { return textAnchor; }

/**
 * @brief Set font style
 * @param fontStyle new font style for text
*/
void SVGText::setFontStyle(const std::string &fontStyle) { this->fontStyle = fontStyle; }

/**
 * @brief Get font style of text
 * @note This function doesn't change any attributes
*/
std::string SVGText::getFontStyle() const { return fontStyle; }

/**
 * @brief Set font size
 * @param fontSize new font size for text
*/
void SVGText::setFontSize(float fontSize) { this->fontSize = fontSize; }

/**
 * @brief Get font size of text
 * @note This function doesn't change any attributes
*/
float SVGText::getFontSize() const { return fontSize; }
