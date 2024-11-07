#ifndef SVG_RENDERING_FLOATPARSER_H
#define SVG_RENDERING_FLOATPARSER_H

#include "TParser.h"

class FloatParser : public TParser<float> {
	float parse(rapidxml::xml_node<> *pNode, const std::string &attributeName = "") override;
};

#endif //SVG_RENDERING_FLOATPARSER_H
