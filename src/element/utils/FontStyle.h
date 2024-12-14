#ifndef SVG_RENDERING_TEXT_STYLE_H
#define SVG_RENDERING_TEXT_STYLE_H

#include <string>
using std::string;

enum class FontStyle{
	NORMAL = 0,
	ITALIC
};

#include "../../utils/StringHelper.h"

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

#endif //SVG_RENDERING_TEXT_STYLE_H
