#include "XMLParser.h" 
#include <fstream>

/**
* @brief Default constructor
* @note Nothing much here 
**/
XMLParser::XMLParser() {
	// TODO: Not really necessary to add
}

/**
* @brief Default destructor
* @note In case there are dynamic allocated memories
**/
~XMLParser() = default;

/**
* @brief Load the xml file
**/
void XMLParser::loadXML(std::string fileName) {
	std::ifstream fin(fileName.c_str()); 
	std::stringstream buffer; 
	buffer << fin.rdbuf(); // <-- push file data to buffer 
	fin.close(); 
	std::string svgData(buffer.str()); // <-- save in svgData string
	doc.parse<0>(&svgData[0]); // <-- save in xml_document type 
}

/**
* @brief Traverse through each nodes and attributes of SVG
* @note Initialize viewport and viewbox
* @note Handling and drawing in here
**/
void XMLParser::traverseXML() {
	rapidxml::xml_node<> *pRoot = doc.first_node(); // <-- <svg>	
	viewPort.x = getDoubleAttr(pRoot, "width"); 
	viewPort.y = getDoubleAttr(pRoot, "height");

	// TODO: add viewBox info (viewbox.h not finished .-.)
}

/**
* @brief Get the insight value of specific attribute
* @param node: current xml node
* @param attrName: name of attribute
* @return a string type
**/
std::string XMLParser::getStringAttr(rapidxml::xml_node<>* pNode, std::string attrName) {
	return std::string();	
}

/**
* @brief Get the double value of specific attribute
* @param node: current xml node
* @param attrName: name of attribute
* @return a double
**/
double XMLParser::getDoubleAttr(rapidxml::xml_node<>* pNode, std::string attrName) {
	double ret = 0.0;
	xml_attribute<> *pAttr = pNode->first_attribute(attrName);
	if (pAttr == nullptr) {
		// TODO: process something here if no attribute with attrName
		return ret;
	}
	std::stringstream buffer(pAttr->value()); // <-- pass attribute value to buffer
	buffer >> ret; // <-- convert and pass value to double
	buffer(std::string()); // <-- clear buffer
	return ret;
}



