#ifndef SVG_RENDERING_TEXT_ANCHOR_H
#define SVG_RENDERING_TEXT_ANCHOR_H

/**
 * @brief Types of text anchor in SVG
 * @note Default is START.
 */
enum class TextAnchor : int{
	START = 0,
	MIDDLE,
	END,
};

//#include <gdiplus/gdiplusenums.h>

/**
 * @brief Supports.for text anchor extracting and getting
 * @note This class only has one instance
 */
class TextAnchorHelper final{
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
