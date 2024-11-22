#ifndef SVG_RENDERING_FILL_RULE_H
#define SVG_RENDERING_FILL_RULE_H

/**
 * @brief Types of fill rule in SVG
 * @note Default is NON_ZERO
 */
enum class FillRule : int{
	NON_ZERO = 0,
	EVEN_ODD,
};

//#include <gdiplus/gdiplusenums.h>

/**
 * @brief Supports.for Fill Rule extracting and getting
 * @note This class only has one instance
 */
class FillRuleHelper final{
public:
	static FillRule fromName(const std::string &s) {
		if (s == "evenodd") {
			return FillRule::EVEN_ODD;
		}
		return FillRule::NON_ZERO; // default is non_zero
	}

	static std::string getName(const FillRule &fillRule) {
		if (fillRule == FillRule::EVEN_ODD) return "evenodd";
		return "nonzero";
	}

	static Gdiplus::FillMode getGdiplusFillMode(const FillRule &fillRule) {
		if (fillRule == FillRule::EVEN_ODD) return Gdiplus::FillModeAlternate;
		return Gdiplus::FillModeWinding;
	}
};

#endif //SVG_RENDERING_FILL_RULE_H
