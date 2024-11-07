#include "XMLParser.h"

/**
 * @brief Default constructor
*/
XMLParser::XMLParser() {
	viewPort = Vector2D<float>(0, 0);
}

/**
 * @brief Default destructor
 * @note In case there are dynamic allocated memories
*/

/**
 * @brief Traverse through each nodes and attributes of SVG
 * @note Initialize viewport and viewbox
 * @note Handling and drawing in here
*/
void XMLParser::traverseXML(const std::string &fileName, std::vector<Element *> &v) {
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
	viewPort.x = parseFloatAttr(pRoot, "width");
	viewPort.y = parseFloatAttr(pRoot, "height");

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
				v.push_back(new SVGRect(parseRect(pNode)));
			} else if (nodeName == "ellipse") {
				v.push_back(new SVGEllipse(parseEllipse(pNode)));
			} else if (nodeName == "circle") {
				v.push_back(new SVGCircle(parseCircle(pNode)));
			} else if (nodeName == "line") {
				v.push_back(new SVGLine(parseLine(pNode)));
			} else if (nodeName == "polyline") {
				v.push_back(new SVGPolyline(parsePolyline(pNode)));
			} else if (nodeName == "polygon") {
				v.push_back(new SVGPolygon(parsePolygon(pNode)));
			} else if (nodeName == "text") {
				v.push_back(new SVGText(parseText(pNode)));
			}
		}
		// TODO: break just for testing
		pNode = pNode->next_sibling();
	}
}

/**
 * @brief Set view port
 * @param new view port
*/
void XMLParser::setViewPort(const Vector2D<float> &_viewPort) { this->viewPort = _viewPort; }

/**
 * @brief get view port information
 * @return viewport
*/
Vector2D<float> XMLParser::getViewPort() {
	return this->viewPort;
}

/**
 * @brief Parse rectangle attributes
 * @return Rectangle object
 * @note x, y, rx, ry is 0 by default
*/
SVGRect XMLParser::parseRect(rapidxml::xml_node<> *pNode) {
	float x = parseFloatAttr(pNode, "x");
	float y = parseFloatAttr(pNode, "y");
	float rx = parseFloatAttr(pNode, "rx");
	float ry = parseFloatAttr(pNode, "ry");
	float width = parseFloatAttr(pNode, "width");
	float height = parseFloatAttr(pNode, "height");
	SVGColor fillColor = parseColor(pNode, "fill");
	SVGColor strokeColor = parseColor(pNode, "stroke");
	float strokeWidth = parseFloatAttr(pNode, "stroke-width");
	return {Vector2D(x, y), fillColor, strokeColor, strokeWidth, width, height, Vector2D(rx, ry)};
}

/**
 * @brief Parse Ellipse attributes
 * @return Ellipse object
*/
SVGEllipse XMLParser::parseEllipse(rapidxml::xml_node<> *pNode) {
	float cx = parseFloatAttr(pNode, "cx");
	float cy = parseFloatAttr(pNode, "cy");
	float rx = parseFloatAttr(pNode, "rx");
	float ry = parseFloatAttr(pNode, "ry");
	SVGColor fillColor = parseColor(pNode, "fill");
	SVGColor strokeColor = parseColor(pNode, "stroke");
	float strokeWidth = parseFloatAttr(pNode, "stroke-width");
	return {Vector2D(cx, cy), fillColor, strokeColor, strokeWidth, Vector2D(rx, ry)};
}

/**
 * @brief Parse Circle attributes
 * @return a Circle object
*/
SVGCircle XMLParser::parseCircle(rapidxml::xml_node<> *pNode) {
	float cx = parseFloatAttr(pNode, "cx");
	float cy = parseFloatAttr(pNode, "cy");
	float radius = parseFloatAttr(pNode, "r");
	SVGColor fillColor = parseColor(pNode, "fill");
	SVGColor strokeColor = parseColor(pNode, "stroke");
	float strokeWidth = parseFloatAttr(pNode, "stroke-width");
	return {Vector2D(cx, cy), fillColor, strokeColor, strokeWidth, radius};
}

/**
 * @brief Parse Line attributes
 * @return a Line object
*/
SVGLine XMLParser::parseLine(rapidxml::xml_node<> *pNode) {
	float x1 = parseFloatAttr(pNode, "x1");
	float y1 = parseFloatAttr(pNode, "y1");
	float x2 = parseFloatAttr(pNode, "x2");
	float y2 = parseFloatAttr(pNode, "y2");
	SVGColor fillColor = parseColor(pNode, "fill");
	SVGColor strokeColor = parseColor(pNode, "stroke");
	float strokeWidth = parseFloatAttr(pNode, "stroke-width");
	return {Vector2D(x1, y1), fillColor, strokeColor, strokeWidth, Vector2D(x2, y2)};
}

/**
 * @brief Parse Polyline attributes
 * @return a Polyline object
*/
SVGPolyline XMLParser::parsePolyline(rapidxml::xml_node<> *pNode) {
	SVGColor fillColor = parseColor(pNode, "fill");
	SVGColor strokeColor = parseColor(pNode, "stroke");
	float strokeWidth = parseFloatAttr(pNode, "stroke-width");
	std::vector<Vector2D<float>> points = parsePointsAttr(pNode, "points");
	std::string fillRule = parseStringAttr(pNode, "fill-rule");
	Vector2D<float> position = points[0];
	return {position, fillColor, strokeColor, strokeWidth, points, (fillRule == "nonzero") ? FillRule::NON_ZERO : FillRule::EVEN_ODD};
}

/**
 * @brief Parse Polygon attributes
 * @return a Polygon object
*/
SVGPolygon XMLParser::parsePolygon(rapidxml::xml_node<> *pNode) {
	SVGColor fillColor = parseColor(pNode, "fill");
	SVGColor strokeColor = parseColor(pNode, "stroke");
	float strokeWidth = parseFloatAttr(pNode, "stroke-width");
	std::vector<Vector2D<float>> points = parsePointsAttr(pNode, "points");
	std::string fillRule = parseStringAttr(pNode, "fill-rule");
	Vector2D<float> position = points[0];
	return {position, fillColor, strokeColor, strokeWidth, points, (fillRule == "nonzero") ? FillRule::NON_ZERO : FillRule::EVEN_ODD};
}


/**
 * @brief Parse Text attributes
 * @return a Text object
*/
SVGText XMLParser::parseText(rapidxml::xml_node<> *pNode) {
	float x = parseFloatAttr(pNode, "x");
	float y = parseFloatAttr(pNode, "y");
	float dx = parseFloatAttr(pNode, "dx");
	float dy = parseFloatAttr(pNode, "dy");
	x += dx;
	y += dy;
	std::string textAnchor = parseStringAttr(pNode, "text-anchor");
	SVGColor fillColor = parseColor(pNode, "fill");
	SVGColor strokeColor = parseColor(pNode, "stroke");
	float strokeWidth = parseFloatAttr(pNode, "stroke-width");
	float fontSize = parseFloatAttr(pNode, "font-size");
	std::string data = pNode->value();
	return {Vector2D<float>{x, y}, fillColor, strokeColor, strokeWidth, data, fontSize};
}


/**
 * @brief Get the float value of specific attribute
 * @param node: current xml node
 * @param attrName: name of attribute
 * @return a float
*/
float XMLParser::parseFloatAttr(rapidxml::xml_node<> *pNode, std::string attrName) {
	float ret = 0.0;
	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute(attrName.c_str());
	if (pAttr == nullptr) { // <-- doesn't exist an attribute with name = attrName
		// stroke, fill, opacity default must be 1
		if (attrName.find("stroke") != std::string::npos || attrName.find("fill") != std::string::npos || attrName.find("opacity") != std::string::npos)
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
 * @brief Get the insight value of specific attribute
 * @param node: current xml node
 * @param attrName: name of attribute
 * @return a string type
*/
std::string XMLParser::parseStringAttr(rapidxml::xml_node<> *pNode, std::string attrName) {
	std::string data("");
	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute(attrName.c_str());
	if (pAttr == nullptr) {
		/// TODO: handle if no attribute name = attrName
		if (attrName == "fill-rule") data = "nonzero";
		return data;
	}
	data = pAttr->value();
	return data;
}

/**
 * @brief Parse color attributes
 * @param pNode current xml node
 * @param attrName the attribute name to find value
 * @return SVGColor type
*/
SVGColor XMLParser::parseColor(rapidxml::xml_node<> *pNode, std::string attrName) {
	SVGColor color;
	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute(attrName.c_str());
	if (pAttr == nullptr) { // <-- can't find any attribute with name = attrName
		// If no attribute with attrName specified, default color is blank (black with opacity = 0)
		color = SVG_BLANK;
		// If stroke not specified => no stroke
		if (attrName == "stroke") return color;
		float opaque = parseFloatAttr(pNode, attrName + "-opacity") * parseFloatAttr(pNode, "opacity");
		color.a = (unsigned char) (255.0f * opaque);
		if (strcmp(pNode->name(), "line") == 0 && attrName == "stroke") {
			color.a = 0; /// <-- In line, if not specify stroke then not visible
			//std::cout << "Stroke not found in line\n";
		}
		return color;
	}
	std::string value = pAttr->value();
	if (value == "none" || value == "transparent") {
		// If value is none or transparent -> opacity = 0 so return default color with alpha = 0
		return SVG_BLANK;
	}
	if (value.find("url") != std::string::npos) { // <-- belongs to a gradient
		// TODO: process the case fill or stroke value is a gradient
	} else {
		//std::cout << "Can find attribute " << attrName << '\n';
		color = SVGColor(value); // <-- get Color in SVGColor class
		// get opacity
		float opaque = parseFloatAttr(pNode, attrName + "-opacity") * parseFloatAttr(pNode, "opacity");
		//std::cout << "Opacity = " << opaque << '\n';
		color.a = (unsigned char) ((double) 255.0f * opaque);
		//std::cout << "So return color is "; color.output(); std::cout << '\n';

		// TODO: More research required to make sure the input don't make the opaque overflowed or having unexpected behavior.
	}
	return color;
}

std::vector<Vector2D<float>> XMLParser::parsePointsAttr(rapidxml::xml_node<>* pNode, std::string attrName) {
	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute(attrName.c_str());
	if (pAttr == nullptr) return {};
	std::vector<Vector2D<float>> ret = {};

	std::string value = pAttr->value();
	for (char & i : value) if (i == ',') i = ' ';
	std::stringstream buffer(value);

	float x = 0;
	while (buffer >> x) {
		float y = 0;
		buffer >> y;
		ret.emplace_back(x, y); //ret.push_back(Vector2D<float>(x, y));
	}

	buffer.str(""); // <-- clear buffer
	return ret;
}

