#include "XMLParser.h" 
#include <fstream>

/**
* @brief Default constructor
* @note Nothing much here 
**/
//XMLParser::XMLParser() {
//	 TODO: Not really necessary to add
//}

/**
* @brief Default destructor
* @note In case there are dynamic allocated memories
**/
//XMLParser::~XMLParser() {}
//= default; //= default ?

/**
* @brief Load the xml file
**/
void XMLParser::loadXML(const std::string& fileName) {
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
	viewPort.x = parseDoubleAttr(pRoot, "width"); 
	viewPort.y = parseDoubleAttr(pRoot, "height");

	// TODO: Add viewBox info from pRoot attribute (ViewBox.h not finished .-.)

  	// TODO: Traverse all elements
	rapidxml::xml_node<> *pNode = pRoot->first_node(); 
	while (pNode != nullptr) {
		std::string nodeName = pNode->name(); // <-- get node's name
		if (nodeName == "defs") { // <-- contains gradient information
			// TODO: Parse and get all gradients (linear + radial)
			// TODO: Save gradients id
		} else if (nodeName == "g") {
			// TODO: Parse and get group attributes
			// TODO: Process to each element of group
			// TODO: May perform recursively when <g> contains other <g>
		} else { // <-- Shape type, if not then pass ?
			if (nodeName == "rect") {
				parseRect(pNode);
			} else if (nodeName == "ellipse") {

			} else if (nodeName == "circle") {

			} else if (nodeName == "line") {

			} else if (nodeName == "polyline") {

			} else if (nodeName == "polygon") {

			}
		}
	}
}

/**
* @brief Get the insight value of specific attribute
* @param node: current xml node
* @param attrName: name of attribute
* @return a string type
**/
std::string XMLParser::parseStringAttr(rapidxml::xml_node<>* pNode, std::string attrName) {
	return "";
}

/**
* @brief Get the double value of specific attribute
* @param node: current xml node
* @param attrName: name of attribute
* @return a double
**/
double XMLParser::parseDoubleAttr(rapidxml::xml_node<>* pNode, std::string attrName) {
	double ret = 0.0;
	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute(attrName.c_str());
	if (pAttr == nullptr) { // <-- doesn't exist an attribute with name = attrName
		// stroke, fill, opacity default must be 1
		if (attrName.find("stroke") != std::string::npos || attrName.find("fill") != std::string::npos || 
			attrName.find("opacity") != std::string::npos)
				ret = 1;
		return ret;
	}
	std::string value = pAttr->value();
	// TODO: value is a real number
	// TODO: value is percentage (%)
	return ret;
}

template<typename T>
Vector2D<T> XMLParser::getViewPort() {
	return Vector2D<T>(); //TODO: Implement XMLParser::getViewPort();
}

Rect XMLParser::parseRect(rapidxml::xml_node<>* pNode) {
	double x = parseDoubleAttr(pNode, "x");
	double y = parseDoubleAttr(pNode, "y");
	double rx = parseDoubleAttr(pNode, "rx");
	double ry = parseDoubleAttr(pNode, "ry");
	double width = parseDoubleAttr(pNode, "width"); 
	double height = parseDoubleAttr(pNode, "height");
	SVGColor fillColor = parseColor(pNode, "fill");
	SVGColor strokeColor = parseColor(pNode, "stroke");
	double strokeWidth = parseDoubleAttr(pNode, "stroke-width");
	Rect ret;
	return ret;
}

/**
 * @brief Parse color attributes
 * @param pNode current xml node
 * @param attrName the attribute name to find value
 * @return SVGColor type
 */
SVGColor XMLParser::parseColor(rapidxml::xml_node<>* pNode, std::string attrName) {
	SVGColor color;
	rapidxml::xml_attribute<>* pAttr = pNode->first_attribute(attrName.c_str());
	if (pAttr == nullptr) {
		// If no attribute with attrName specified, default color is black
		// Default constructor of SVGColor is black
		return color;
	}
	std::string value = pAttr->value();
	if (value == "none" || value == "transparent") {
		// If value is none or transparent -> opacity = 0 so return default color
		return color;
	}
	if (value.find("url") != std::string::npos) { // <-- belongs to a gradient
		// TODO: process the case fill or stroke value is a gradient
	} else {
		// get opacity
		color.a = color.a * parseDoubleAttr(pNode, attrName + "-opacity") * parseDoubleAttr(pNode, "opacity"); // TODO: More research required to make sure the input don't make the opaque overflowed or having unexpected behavior.
	}
	return color;
}

