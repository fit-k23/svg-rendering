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

	//std::cout << "Viewport x = " << viewPort.x << '\n';
	//std::cout << "Viewport y = " << viewPort.y << '\n';

	// TODO: Add viewBox info from pRoot attribute (ViewBox.h not finished .-.)

	// Traverse all elements
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
			} 
			else if (nodeName == "ellipse") {
				v.push_back(new SVGEllipse(parseEllipse(pNode)));
			} 
			else if (nodeName == "circle") {
				v.push_back(new SVGCircle(parseCircle(pNode)));
			} 
			else if (nodeName == "line") {
				v.push_back(new SVGLine(parseLine(pNode)));
			} 
			else if (nodeName == "polyline") {
				v.push_back(new SVGPolyline(parsePolyline(pNode)));
			} 
			else if (nodeName == "polygon") {
				v.push_back(new SVGPolygon(parsePolygon(pNode)));
			} 
			else if (nodeName == "text") {
				v.push_back(new SVGText(parseText(pNode)));
			} 
			else if (nodeName == "path") {
				v.push_back(new SVGPath(parsePath(pNode)));
				//v.back()->dbg();
			}
		}
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
	return {Vector2D<float>{x, y}, fillColor, strokeColor, strokeWidth, data, fontSize, TextAnchorHelper::fromName(textAnchor)};
}

SVGPath XMLParser::parsePath(rapidxml::xml_node<>* pNode) {
	SVGColor fillColor = parseColor(pNode, "fill");
	SVGColor strokeColor = parseColor(pNode, "stroke");
	float strokeWidth = parseFloatAttr(pNode, "stroke-width");
	FillRule fillRule = (parseStringAttr(pNode, "fill-rule") == "nonzero" ? FillRule::NON_ZERO : FillRule::EVEN_ODD);

	std::vector<PathPoint *> points;
	std::string d = parseStringAttr(pNode, "d"); // <-- get string of d attribute

	auto isCmd = [](char c) -> bool {
		char ch = tolower(c);
		return ch == 'm' || ch == 'l' || ch == 'h' || ch == 'v' || ch == 'z' || ch == 'c' || ch == 's' || ch == 'q' || ch == 't' || ch == 'a';
	};

	auto getLastPos = [](const std::vector<PathPoint *> &points) -> Vector2D<float> {
		if (points.empty()) return Vector2D<float>(0.0f, 0.0f);
		return points.back()->getPos();
	};

	// change all hyphens to blank space to use stringstream
	for (int i = 0; i < (int)d.size(); ++i) {
		if (d[i] == ',') d[i] = ' ';
	}

	//std::cout << "d after format: " << d << '\n';

	Vector2D<float> sta;
	std::stringstream buffer;
	std::string data;
	for (int i = 0; i < (int)d.size(); ++i) {
		if (!isCmd(d[i])) continue;
		char ins = tolower(d[i]);
		int nxt = -1;
		int tmpI = i + 1;
		data = "";
		while (tmpI < (int)d.size()) {
			if (isCmd(d[tmpI])) {
				nxt = tmpI;
				break;
			}
			data += d[tmpI];
			++tmpI;
		}
		/*std::cout << "current cmd: " << d[i] << '\n';
		std::cout << "data: " << data << '\n';
		std::cout << "next command: " << (nxt == -1 ? '?' : d[nxt]) << '\n';
		std::cout << "next command position: " << nxt << '\n';*/
		buffer.clear();
		buffer.str(data);
		//std::stringstream buffer(data);
		if (ins == 'm' || ins == 'l') { // <-- move-to and line command
			float x, y;
			while (buffer >> x >> y) {
				Vector2D<float> newPos = Vector2D<float>(x, y) + (isupper(d[i]) ? Vector2D<float>(0, 0) : getLastPos(points));
				points.push_back(new NormPathPoint(d[i], newPos));
				//std::cout << x << " " << y << '\n';
				if (ins == 'm') sta = newPos;
			}
		}
		else if (ins == 'h' || ins == 'v') { // <-- horizontal and vertical line
			float num;
			while (buffer >> num) {
				//std::cout << num << '\n';
				Vector2D<float> newPos;
				if (ins == 'h') newPos = Vector2D<float>(d[i] == 'H' ? num : getLastPos(points).x + num, getLastPos(points).y);
				else newPos = Vector2D<float>(getLastPos(points).x, d[i] == 'V' ? num : getLastPos(points).y + num);
				points.push_back(new NormPathPoint(d[i], newPos));
			}
		}
		else if (ins == 'q') { // <-- Quadratic Bezier Curve
			float x, y, cenx, ceny;
			while (buffer >> cenx >> ceny >> x >> y) {
				//std::cout << cenx << " " << ceny << " " << x << " " << y << '\n';
				Vector2D<float> newPos = Vector2D<float>(x, y);
				Vector2D<float> newCen = Vector2D<float>(cenx, ceny);
				if (d[i] == 'q') {
					newPos += getLastPos(points);
					newCen += getLastPos(points);
				}
				points.push_back(new QuadPathPoint(d[i], newPos, newCen));
			}
		}
		else if (ins == 't') { // <-- reflection of previous quadratic bezier control's point
			float x, y;
			while (buffer >> x >> y) {
				//std::cout << x << " " << y << '\n';
				Vector2D<float> newPos = Vector2D<float>(x, y);
				if (d[i] == 't') newPos += getLastPos(points);
				Vector2D<float> cen;
				// If previous command not a quadratic-type, the control point is the same as the current point
				if (!points.empty() && points.back()->getPointType() != "quad") cen = points.back()->getPos();
				else {
					QuadPathPoint* pQuad = static_cast<QuadPathPoint*>(points.back());
					// calculate new reflection control point
					Vector2D<float> cen = pQuad->getPos() + (pQuad->getPos() - pQuad->getCen());
				}
				points.push_back(new QuadPathPoint(d[i], newPos, cen));
			}
		}
		else if (ins == 's') { // <-- only first control point has reflection, second control point must be specified
			float x, y, cen2x, cen2y;
			while (buffer >> cen2x >> cen2y >> x >> y) {
				//std::cout << cen2x << " " << cen2y << " " << x << " " << y << '\n';
				Vector2D<float> newPos = Vector2D<float>(x, y);
				Vector2D<float> cen2 = Vector2D<float>(cen2x, cen2y);
				if (d[i] == 's') {
					newPos += getLastPos(points);
					cen2 += getLastPos(points);
				}
				Vector2D<float> cen1;
				// If previous cmd not cubic-type, start control point is the same as the curve starting point (current point)
				if (!points.empty() && points.back()->getPointType() != "cubic") cen1 = points.back()->getPos();
				else { // <-- start control point is reflection of previous end control point and current point.
					CubicPathPoint* pCubic = static_cast<CubicPathPoint*>(points.back()); // don't use points[i - 1]
					cen1 = pCubic->getPos() + (pCubic->getPos() - pCubic->getCen(1));
				}
				points.push_back(new CubicPathPoint(d[i], newPos, cen1, cen2));
			}
		}
		else if (ins == 'a') { // <-- Arc
			Vector2D<float> radii;
			float xRotation;
			bool largeArcFlag; 
			bool sweepFlag;
			Vector2D<float> pos;
			while (buffer >> radii.x >> radii.y >> xRotation >> largeArcFlag >> sweepFlag >> pos.x >> pos.y) {
				//std::cout << radii.x << " " << radii.y << " " << xRotation << " " << largeArcFlag << " " << sweepFlag << " " << pos.x << " " << pos.y << '\n';
				points.push_back(new ArcPathPoint(d[i], (d[i] == 'A' ? pos : getLastPos(points) + pos), radii, xRotation, largeArcFlag, sweepFlag));
			}
		}
		else if (ins == 'c') { // <-- Cubic Bezier Curve
			Vector2D<float> pos; 
			float cen0x, cen0y, cen1x, cen1y, x;
			while (buffer >> cen0x >> cen0y >> cen1x >> cen1y >> pos.x >> pos.y) {
				//std::cout << cen0x << " " << cen0y << " " << cen1x << " " << cen1y << " " << pos.x << " " << pos.y << '\n';
				if (d[i] == 'C') points.push_back(new CubicPathPoint(d[i], pos, Vector2D<float>(cen0x, cen0y), Vector2D<float>(cen1x, cen1y)));
				else {
					Vector2D<float> lastPos = getLastPos(points);
					points.push_back(new CubicPathPoint(d[i], lastPos + pos, lastPos + Vector2D<float>(cen0x, cen0y), lastPos + Vector2D<float>(cen1x, cen1y)));
				}
			}
		}
		else if (ins == 'z') { // end current path
			// No parameter in z command
			// Current point goes back to the starting point
			points.push_back(new NormPathPoint(d[i], sta));
		}
		if (nxt == -1) break;
		i = nxt - 1; // go to position of next command
		//std::cout << "i = " << i << '\n';
	}

	return SVGPath(points[0]->getPos(), fillColor, strokeColor, strokeWidth, points, fillRule);
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
		// If no attribute with attrName specified, default color is black
		color = SVG_BLACK;
		if (attrName == "stroke") { // <-- If stroke is not specifed, then there is no stroke
			color = SVG_BLANK;
			return color;
		}
		float opaque = parseFloatAttr(pNode, attrName + "-opacity") * parseFloatAttr(pNode, "opacity");
		color.a = (unsigned char) (255.0f * opaque);
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
		color = SVGColor(value); // <-- get Color in SVGColor class
		// get opacity
		float opaque = parseFloatAttr(pNode, attrName + "-opacity") * parseFloatAttr(pNode, "opacity");
		color.a = (unsigned char) ((double) 255.0f * opaque);

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
		ret.emplace_back(x, y); 
	}

	buffer.str(""); // <-- clear buffer
	return ret;
}

