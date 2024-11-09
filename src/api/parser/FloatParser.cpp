#include "FloatParser.h"

float FloatParser::parse(rapidxml::xml_node<> *pNode, const std::string &attrName) {
	float ret = 0.0f;
	float ret = 0.0;
	rapidxml::xml_attribute<>* pAttr = pNode->first_attribute(attrName.c_str());
	if (pAttr == nullptr) { // <-- doesn't exist an attribute with name = attrName
		// stroke, fill, opacity default must be 1
		if (attrName.find("stroke") != std::string::npos || attrName.find("fill") != std::string::npos || attrName.find("opacity") != std::string::npos)
			ret = 1.0f;
		return ret;
	}
	std::string value = pAttr->value();
	std::stringstream buffer(value);
	buffer >> ret;
	buffer.str(""); // <-- clear buffer
	// TODO: value is a real number
	// TODO: value is percentage (%)
	return ret;
}
