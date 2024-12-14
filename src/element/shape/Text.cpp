#include "Text.h"

SVGText::SVGText() : textAnchor(TextAnchor::START), fontSize(1.0) {}

SVGText::SVGText(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const std::string &data, float fontSize, FontStyle fontStyle, TextAnchor textAnchor) : Element(position, fillColor, strokeColor, strokeWidth), data(data), textAnchor(textAnchor), fontSize(fontSize), fontStyle{fontStyle} {}

ElementType SVGText::getTypeName() { return ElementType::Text; }

void SVGText::dbg() {
	Element::dbg();
	std::cout << "Data: " << data << '\n';
	std::cout << "Anchor: " << TextAnchorHelper::getName(textAnchor) << '\n';
	std::cout << "Font style: " << FontStyleHelper::getName(fontStyle) << '\n';
	std::cout << "Font size: " << fontSize << '\n';
}

std::pair<Vector2D<float>, Vector2D<float>> SVGText::getBoundingBox() const {
	float actualY = position.y - fontSize;
	float actualX = position.x;
	// TODO: Calculating the bounding box of Text
	return {Vector2D<float>(actualX, actualY), Vector2D<float>(actualX, actualY)};
}

void SVGText::setData(const std::string &_data) { data = _data; }

std::string SVGText::getData() const { return data; }

void SVGText::setTextAnchor(const TextAnchor &_textAnchor) { textAnchor = _textAnchor; }

TextAnchor SVGText::getTextAnchor() const { return textAnchor; }

void SVGText::setFontStyle(const FontStyle &_fontStyle) { fontStyle = _fontStyle; }

FontStyle SVGText::getFontStyle() const { return fontStyle; }

void SVGText::setFontSize(float _fontSize) { fontSize = _fontSize; }

float SVGText::getFontSize() const { return fontSize; }
