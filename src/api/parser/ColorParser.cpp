#include "ColorParser.h"
#include "ParserManager.h"

SVGColor ColorParser::parse(rapidxml::xml_node<> *pNode, const std::string &attributeName) {
	TParser<float> *floatParser = ParserManager::getParser<float>("float");
	if (floatParser == nullptr) return SVG_BLANK;
	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute(attributeName.c_str());
	if (pAttr == nullptr) { // <-- can't find any attribute named attributeName
		// If no attribute with attributeName specified, default color is blank (black with opacity = 0)
		// If stroke not specified => no stroke
		if (attributeName == "stroke") {
//			if (strcmp(pNode->name(), "line" == 0)) {
//				return SVG_BLANK; // <-- In line, if not specify stroke then not visible
//			}
			return SVG_BLANK;
		}
		float opaque = floatParser->parse(pNode, attributeName + "-opacity") * floatParser->parse(pNode, "opacity");
		return SVG_BLACK.alpha((unsigned char) (255.0f * opaque));
	}
	SVGColor color;
	std::string value = pAttr->value();
	if (value == "none" || value == "transparent") {
		// If value is none or transparent -> opacity = 0 so return default color with alpha = 0
		return SVG_BLANK;
	}
	if (value.find("url") != std::string::npos) { // <-- belongs to a gradient
		// TODO: process the case fill or stroke value is a gradient
		return SVG_BLANK; // temp solution to gradient fill
	}
	float opaque = floatParser->parse(pNode, attributeName + "-opacity") * floatParser->parse(pNode, "opacity");
	// TODO: More research required to make sure the input don't make the opaque overflowed or having unexpected behavior.
	return SVGColor(value).alpha((unsigned char) (255.0f * opaque));
}