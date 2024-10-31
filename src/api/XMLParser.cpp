#include "XMLParser.h"
#include <fstream>

/**
* @brief Default constructor
* @note Nothing much here 
**/
XMLParser::XMLParser() {
	viewPort = Vector2D<double>(0, 0);
	gradients.clear();
}

/**
* @brief Default destructor
* @note In case there are dynamic allocated memories
**/
//XMLParser::~XMLParser() {}
//= default; //= default ?

/**
* @brief Traverse through each nodes and attributes of SVG
* @note Initialize viewport and viewbox
* @note Handling and drawing in here
**/
void XMLParser::traverseXML(const std::string& fileName, std::vector<Element*>& v) {
	std::ifstream fin(fileName.c_str());
	if (!fin.is_open()) {
		std::cout << "Cannot open file\n";
		return;
	}
	std::stringstream buffer;
	buffer << fin.rdbuf(); // <-- push file data to buffer 
	fin.close();
	std::string svgData = buffer.str(); // <-- save in svgData string
	doc.parse<0>(&svgData[0]); // <-- save in xml_document type

	rapidxml::xml_node<> *pRoot = doc.first_node(); // <-- <svg> 
	viewPort.x = parseDoubleAttr(pRoot, "width"); 
	viewPort.y = parseDoubleAttr(pRoot, "height");

	std::cout << "Viewport x = " << viewPort.x << '\n';
	std::cout << "Viewport y = " << viewPort.y << '\n';

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
				v.push_back(new Rect(parseRect(pNode)));
			} else if (nodeName == "ellipse") {

			} else if (nodeName == "circle") {
				v.push_back(new Circle(parseCircle(pNode)));
			} else if (nodeName == "line") {
				v.push_back(new Line(parseLine(pNode)));
			} else if (nodeName == "polyline") {

			} else if (nodeName == "polygon") {

			}
		}
		// TODO: break just for testing
		//break;
		pNode = pNode->next_sibling();
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

/*
* @brief get view port information
* @return viewport
*/
Vector2D<double> XMLParser::getViewPort() {
	return this->viewPort; 
}

/**
* @brief Parse rectangle attributes
* @return Rectangle object
* @note x, y, rx, ry is 0 by default
*/
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
	Rect rect = Rect(Vector2D(x, y), fillColor, strokeColor, strokeWidth, width, height, Vector2D(rx, ry));
	return rect;
}

/*
* @brief Parse Circle attributes
* @return a Circle object
*/
Circle XMLParser::parseCircle(rapidxml::xml_node<>* pNode) {
	double cx = parseDoubleAttr(pNode, "cx");
	double cy = parseDoubleAttr(pNode, "cy");
	double radius = parseDoubleAttr(pNode, "r");
	SVGColor fillColor = parseColor(pNode, "fill");
	SVGColor strokeColor = parseColor(pNode, "stroke");
	double strokeWidth = parseDoubleAttr(pNode, "stroke-width");
	Circle circle = Circle(Vector2D(cx, cy), fillColor, strokeColor, strokeWidth, radius);
	return circle;
}

Line XMLParser::parseLine(rapidxml::xml_node<>* pNode) {
	double x1 = parseDoubleAttr(pNode, "x1");
	double y1 = parseDoubleAttr(pNode, "y1");
	double x2 = parseDoubleAttr(pNode, "x2");
	double y2 = parseDoubleAttr(pNode, "y2");
	SVGColor fillColor = parseColor(pNode, "fill");
	SVGColor strokeColor = parseColor(pNode, "stroke");
	double strokeWidth = parseDoubleAttr(pNode, "stroke-width");
	Line line = Line(Vector2D(x1, y1), fillColor, strokeColor, strokeWidth, Vector2D(x2, y2));
	return line;
}

/**
* @brief Get the double value of specific attribute
* @param node: current xml node
* @param attrName: name of attribute
* @return a double
**/
double XMLParser::parseDoubleAttr(rapidxml::xml_node<>* pNode, std::string attrName) {
	double ret = 0.0;
	rapidxml::xml_attribute<>* pAttr = pNode->first_attribute(attrName.c_str());
	if (pAttr == nullptr) { // <-- doesn't exist an attribute with name = attrName
		// stroke, fill, opacity default must be 1
		if (attrName.find("stroke") != std::string::npos || attrName.find("fill") != std::string::npos ||
			attrName.find("opacity") != std::string::npos)
			ret = 1;
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

/**
 * @brief Parse color attributes
 * @param pNode current xml node
 * @param attrName the attribute name to find value
 * @return SVGColor type
 */
SVGColor XMLParser::parseColor(rapidxml::xml_node<>* pNode, std::string attrName) {
	SVGColor color;
	rapidxml::xml_attribute<>* pAttr = pNode->first_attribute(attrName.c_str());
	if (pAttr == nullptr) { // <-- can't find any attribute with name = attrName
		// If no attribute with attrName specified, default color is black
		// Default constructor of SVGColor is black
		color = SVGColor(0, 0, 0);
		color.a = color.a * parseDoubleAttr(pNode, attrName + "-opacity") * parseDoubleAttr(pNode, "opacity"); 
		return color;
	}
	std::string value = pAttr->value();
	if (value == "none" || value == "transparent") {
		// If value is none or transparent -> opacity = 0 so return default color with alpha = 0
		color = SVGColor(0, 0, 0, 0);
		return color;
	}
	if (value.find("url") != std::string::npos) { // <-- belongs to a gradient
		// TODO: process the case fill or stroke value is a gradient
	} else {
		color = SVGColor(value); // <-- get Color in SVGColor class
		// get opacity
		color.a = color.a * parseDoubleAttr(pNode, attrName + "-opacity") * parseDoubleAttr(pNode, "opacity"); 
		// TODO: More research required to make sure the input don't make the opaque overflowed or having unexpected behavior.
	}
	return color;
}

