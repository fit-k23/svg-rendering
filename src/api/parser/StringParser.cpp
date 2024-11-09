#include "StringParser.h"

std::string StringParser::parse(rapidxml::xml_node<>* pNode, const std::string& attrName) {
	std::string data("");
	rapidxml::xml_attribute<>* pAttr = pNode->first_attribute(attrName.c_str());
	if (pAttr == nullptr) {
		/// TODO: handle if no attribute name = attrName
		if (attrName == "fill-rule") data = "nonzero";
		return data;
	}
	data = pAttr->value();
	return data;
}
