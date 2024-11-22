#ifndef SVG_RENDERING_TEXT_ANCHOR_H
#define SVG_RENDERING_TEXT_ANCHOR_H

/** @brief Types of text anchor in SVG (default = START) */
enum class TextAnchor : int{
	START = 0,
	MIDDLE,
	END,
};

/** @brief Utilizer for dealing with TextAnchor */
class TextAnchorHelper final{
public:
	static TextAnchor fromName(const std::string &s) {
		if (s == "middle") {
			return TextAnchor::MIDDLE;
		}
		if (s == "end") {
			return TextAnchor::END;
		}
		return TextAnchor::START; // default is "start"
	}

	static std::string getName(const TextAnchor &tA) {
		switch (tA) {
			case TextAnchor::MIDDLE: return "middle";
			case TextAnchor::END: return "end";
			default: return "start"; // Default is TextAnchor::START
		}
	}
};

#endif //SVG_RENDERING_TEXT_ANCHOR_H
