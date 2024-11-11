#ifndef SVG_RENDERING_TEXT_ANCHOR_H
#define SVG_RENDERING_TEXT_ANCHOR_H

enum class TextAnchor : int{
	START = 0,
	MIDDLE,
	END,
};

#include <gdiplus/gdiplusenums.h>

class TextAnchorHelper{
public:
	static TextAnchor fromName(const std::string &s) {
		if (s == "middle") {
			return TextAnchor::MIDDLE;
		}
		if (s == "end") {
			return TextAnchor::END;
		}
		return TextAnchor::START; // default is start
	}

	static std::string getName(const TextAnchor &tA) {
		switch (tA) {
			case TextAnchor::MIDDLE: return "middle";
			case TextAnchor::END: return "end";
			default: return "start"; // Default is TextAnchor::START
		}
	}

	static Gdiplus::StringAlignment getStringAlignment(const TextAnchor &tA) {
		switch (tA) {
			// TODO: check if the return is correctly chosen
			case TextAnchor::MIDDLE: return Gdiplus::StringAlignmentCenter;
			case TextAnchor::END: return Gdiplus::StringAlignmentFar;
			default: return Gdiplus::StringAlignmentNear; // default is TextAnchor::START
		}
	}
};

#endif //SVG_RENDERING_TEXT_ANCHOR_H
