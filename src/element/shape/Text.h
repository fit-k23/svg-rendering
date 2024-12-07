#ifndef SVG_RENDERING_TEXT_H
#define SVG_RENDERING_TEXT_H

#include "../Element.h"
#include "../utils/TextAnchor.h"
#include <string>

/**
 * @brief Class that represents Text object in svg
 * @param textAnchor All text object has a text-anchor (default to start)
 * @param dx shift along Ox (default to be 0)
 * @param dy shift along Oy (default to be 0)
 * @note dx, dy will be added to position so there are no attributes dx, dy
 * @note rotation is set to 0 by default (no rotation)
 * @note font size is default to be 1
*/
class SVGText : public Element{
	std::string data; // <-- content of the text
	TextAnchor textAnchor; // <-- position based on "cursor", default:  TextAnchor::START
	std::string fontStyle; // <-- font style of text
	float fontSize; // <-- font size of text
	float offset; // <-- some offset so that raylib draws text more like svg
	Vector2D<float> dataSize; // <-- width and height of whole text
public:
	SVGText();
	SVGText(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const std::string &data, float fontSize, TextAnchor textAnchor = TextAnchor::START);

	/** @brief Get type Text */
	ElementType getTypeName() override;

	/** @brief Print information of Text */
	void dbg() override;

	/**
	 * @brief Get bounding box of text
	 * @return pair of top-left and bottom-right coordinate
	*/
	std::pair<Vector2D<float>, Vector2D<float>> getBoundingBox() const override;

	/** @brief Return the actual position of the text with inputted text size */
	Vector2D<float> getActualPosition(Vector2D<float> size) const;

	/**
	 * @brief Set data size
	 * @param dataSize new data size including width and height of text based on font
	*/
	void setDataSize(const Vector2D<float> &dataSize);

	/** @brief Set default data size with no font */
	void setDataSize();

	/**
	 * @brief Get data size based on font
	 * @param font font family
	*/
	Vector2D<float> getDataSize() const;

	/**
	 * @brief Set data of text
	 * @param data new data for text
	*/
	void setData(const std::string &data);

	/** @brief Get data of text */
	std::string getData() const;

	/**
	 * @brief Set text anchor
	 * @param textAnchor new anchor for text
	*/
	void setTextAnchor(const TextAnchor &textAnchor);

	/** @brief Get anchor of text */
	TextAnchor getTextAnchor() const;

	/**
	 * @brief Set font style
	 * @param fontStyle new font style for text
	*/
	void setFontStyle(const std::string &fontStyle);

	/** @brief Get font style of text */
	std::string getFontStyle() const;

	/**
	 * @brief Set font size
	 * @param fontSize new font size for text
	*/
	void setFontSize(float fontSize);

	/** @brief Get font size of text */
	float getFontSize() const;
};

#endif //SVG_RENDERING_TEXT_H
