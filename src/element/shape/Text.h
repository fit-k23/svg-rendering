#ifndef SVG_RENDERING_TEXT_H
#define SVG_RENDERING_TEXT_H

#include <string>
#include "../Element.h"
#include "../../utils/StringHelper.h"

enum class FontStyle{
	NORMAL = 0,
	ITALIC
};

namespace FontStyleHelper{
	static FontStyle fromName(const std::string &s) {
		string r = s;
		StringHelper::toLowerAsciiString(r);
		if (r == "italic") {
			return FontStyle::ITALIC;
		}
		return FontStyle::NORMAL; // default is "NORMAL"
	}

	static std::string getName(const FontStyle &tA) {
		switch (tA) {
		case FontStyle::ITALIC: return "italic";
		default: return "normal"; // Default is TextStyle::NORMAL
		}
	}
}

/** @brief Types of text anchor in SVG (default = START) */
enum class TextAnchor : int{
	START = 0,
	MIDDLE,
	END,
};

/** @brief Utilizer for dealing with TextAnchor */
namespace TextAnchorHelper{
	static TextAnchor fromName(const string &s) {
		if (s == "middle") {
			return TextAnchor::MIDDLE;
		}
		if (s == "end") {
			return TextAnchor::END;
		}
		return TextAnchor::START; // default is "start"
	}

	static string getName(const TextAnchor &tA) {
		switch (tA) {
		case TextAnchor::MIDDLE: return "middle";
		case TextAnchor::END: return "end";
		default: return "start"; // Default is TextAnchor::START
		}
	}
}

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
	FontStyle fontStyle; // <-- font style of text
	TextAnchor textAnchor; // <-- position based on "cursor", default:  TextAnchor::START
	float fontSize; // <-- font size of text
public:
	SVGText();
	SVGText(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, const std::string &data, float fontSize, FontStyle fontStyle = FontStyle::NORMAL, TextAnchor textAnchor = TextAnchor::START);

	/** @brief Get type Text */
	ElementType getTypeName() override;

	/** @brief Print information of Text */
	void dbg() override;

	/**
	 * @brief Get bounding box of text
	 * @return pair of top-left and bottom-right coordinate
	 */
	std::pair<Vector2D<float>, Vector2D<float>> getBoundingBox() const override;

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
	 * @param TextStyle new font style for text
	 */
	void setFontStyle(const FontStyle &fontStyle);

	/** @brief Get font style of text */
	FontStyle getFontStyle() const;

	/**
	 * @brief Set font size
	 * @param fontSize new font size for text
	 */
	void setFontSize(float fontSize);

	/** @brief Get font size of text */
	float getFontSize() const;
};

#endif //SVG_RENDERING_TEXT_H
