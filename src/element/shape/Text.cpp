#include "Text.h"

SVGText::SVGText() : textAnchor(TextAnchor::START), fontSize(1.0), offset(10.0) {}

SVGText::SVGText(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const std::string &data, float fontSize, TextAnchor textAnchor) : Element(position, fillColor, strokeColor, strokeWidth), data(data), textAnchor(textAnchor), fontSize(fontSize), offset(10.0) {}

ElementType SVGText::getTypeName() { return ElementType::Text; }

void SVGText::dbg() {
	Element::dbg();
	std::cout << "Data: " << data << '\n';
	std::cout << "Anchor: " << TextAnchorHelper::getName(textAnchor) << '\n';
	std::cout << "Font style: " << (fontStyle.empty() ? "default" : fontStyle) << '\n';
	std::cout << "Font size: " << fontSize << '\n';
}

std::pair<Vector2D<float>, Vector2D<float>> SVGText::getBoundingBox() const {
	float actualY = position.y - fontSize + offset;
	float actualX = position.x;
	// TODO: Calculating the bounding box of Text
	return {Vector2D<float>(actualX, actualY), Vector2D<float>(actualX + dataSize.x, actualY + dataSize.y)};
}

void SVGText::setDataSize(const Vector2D<float> &_dataSize) { this->dataSize = _dataSize; }

Vector2D<float> SVGText::getDataSize() const { return dataSize; }

void SVGText::setData(const std::string &_data) { data = _data; }

std::string SVGText::getData() const { return data; }

void SVGText::setTextAnchor(const TextAnchor &_textAnchor) { textAnchor = _textAnchor; }

TextAnchor SVGText::getTextAnchor() const { return textAnchor; }

void SVGText::setFontStyle(const std::string &_fontStyle) { fontStyle = _fontStyle; }

std::string SVGText::getFontStyle() const { return fontStyle; }

void SVGText::setFontSize(float _fontSize) { fontSize = _fontSize; }

float SVGText::getFontSize() const { return fontSize; }

Vector2D<float> SVGText::getActualPosition(Vector2D<float> size) const {
	switch (textAnchor) {
		case TextAnchor::START:
			return {position.x, position.y - size.y * 0.75f};
		case TextAnchor::MIDDLE:
			return {position.x - size.x / 2.0f, position.y - size.y / 2.0f};
		case TextAnchor::END:
			return {position.x - size.x, position.y - size.y / 2.0f};
		default:
			return position;
	}
}
