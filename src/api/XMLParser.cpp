#include "XMLParser.h"

XMLParser::XMLParser() : viewPort{}, viewBox{0, 0, -1, -1} {}

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

	viewBox = parseViewBox(pRoot);

	// Traverse all elements
	rapidxml::xml_node<> *pNode = pRoot->first_node();
	while (pNode != nullptr) {
		std::string nodeName = pNode->name(); // <-- get node's name
		if (nodeName == "defs") { // <-- contains gradient information
			// TODO: Parse and get all gradients (linear + radial)
			// TODO: Save gradients id
		} else if (nodeName == "g") {
			// TODO: Parse and get group attributes
			parseGroup(pNode, v, {});			
		} else { // <-- Shape type, if not then pass ?
			v.push_back(parseShape(pNode, {}));
		}
		pNode = pNode->next_sibling();
	}
}

ViewBox XMLParser::parseViewBox(rapidxml::xml_node<> *pNode) {
	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute("viewBox");
	if (pAttr == nullptr) return {0, 0, -1, -1};
	std::istringstream is(pAttr->value());
	ViewBox v{};
	is >> v.minX >> v.minY >> v.width >> v.height;
	return v;
}

void XMLParser::propagateTransform(std::vector<std::string>& transformation, const std::vector<std::string>& passTransform) {
	std::reverse(transformation.begin(), transformation.end());
	for (int i = (int)passTransform.size() - 1; i >= 0; --i) transformation.push_back(passTransform[i]);
	std::reverse(transformation.begin(), transformation.end());
}

void XMLParser::parseGroup(rapidxml::xml_node<>* pNode, std::vector<Element*>& v, const std::vector<std::string> &passTransform) {
	// All transformations in <g> applies to its children
	// Children nodes inherits fill, stroke from <g>
	std::string transformAttr = parseStringAttr(pNode, "transform");
	std::vector<std::string> transformation = parseTransformation(transformAttr);

	propagateTransform(transformation, passTransform);

	rapidxml::xml_node<>* pChild = pNode->first_node(); // <-- first child node
	while (pChild != nullptr) {
		std::string nodeName = pChild->name();
		if (nodeName == "defs") {
			// TODO: recall function parseDefs and parseGradients (haven't created .-.)
		} else if (nodeName == "g") {
			// recursively call to handle inside g tag
			parseGroup(pChild, v, transformation);
		} else {
			v.push_back(parseShape(pChild, transformation));
		}
		pChild = pChild->next_sibling();
	}
}

Vector2D<float> XMLParser::getViewPort() { return viewPort; }

Element *XMLParser::parseShape(rapidxml::xml_node<>* pNode, const std::vector<std::string> &passTransform) {
	SVGColor fillColor = parseColor(pNode, "fill");
	SVGColor strokeColor = parseColor(pNode, "stroke");
	float strokeWidth = parseFloatAttr(pNode, "stroke-width");
	std::string transformAttr = parseStringAttr(pNode, "transform");
	std::vector<std::string> transformation = parseTransformation(transformAttr);

	std::string nodeName = pNode->name();
	Element* ret = nullptr;
	if (nodeName == "rect")
		ret = new SVGRect(parseRect(pNode, fillColor, strokeColor, strokeWidth));
	else if (nodeName == "ellipse") 
		ret = new SVGEllipse(parseEllipse(pNode, fillColor, strokeColor, strokeWidth));
	else if (nodeName == "circle") 
		ret = new SVGCircle(parseCircle(pNode, fillColor, strokeColor, strokeWidth));
	else if (nodeName == "line") 
		ret = new SVGLine(parseLine(pNode, fillColor, strokeColor, strokeWidth));
	else if (nodeName == "polyline") 
		ret = new SVGPolyline(parsePolyline(pNode, fillColor, strokeColor, strokeWidth));
	else if (nodeName == "polygon") 
		ret = new SVGPolygon(parsePolygon(pNode, fillColor, strokeColor, strokeWidth));
	else if (nodeName == "text") 
		ret = new SVGText(parseText(pNode, fillColor, strokeColor, strokeWidth));
	else if (nodeName == "path") {
		ret = new SVGPath(parsePath(pNode, fillColor, strokeColor, strokeWidth));
		//ret->dbg();
	}
	
	propagateTransform(transformation, passTransform);

	if (ret != nullptr) {
		ret->setTransformation(transformation);
	}
	return ret;
}

SVGRect XMLParser::parseRect(rapidxml::xml_node<> *pNode, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth) {
	float x = parseFloatAttr(pNode, "x");
	float y = parseFloatAttr(pNode, "y");
	float rx = parseFloatAttr(pNode, "rx");
	float ry = parseFloatAttr(pNode, "ry");
	float width = parseFloatAttr(pNode, "width");
	float height = parseFloatAttr(pNode, "height");

	return {Vector2D<float>(x, y), fillColor, strokeColor, strokeWidth, width, height, Vector2D(rx, ry)};
}

SVGEllipse XMLParser::parseEllipse(rapidxml::xml_node<> *pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth) {
	float cx = parseFloatAttr(pNode, "cx");
	float cy = parseFloatAttr(pNode, "cy");
	float rx = parseFloatAttr(pNode, "rx");
	float ry = parseFloatAttr(pNode, "ry");
	return {Vector2D(cx, cy), fillColor, strokeColor, strokeWidth, Vector2D(rx, ry)};
}

SVGCircle XMLParser::parseCircle(rapidxml::xml_node<> *pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth) {
	float cx = parseFloatAttr(pNode, "cx");
	float cy = parseFloatAttr(pNode, "cy");
	float radius = parseFloatAttr(pNode, "r");
	return {Vector2D(cx, cy), fillColor, strokeColor, strokeWidth, radius};
}

SVGLine XMLParser::parseLine(rapidxml::xml_node<> *pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth) {
	float x1 = parseFloatAttr(pNode, "x1");
	float y1 = parseFloatAttr(pNode, "y1");
	float x2 = parseFloatAttr(pNode, "x2");
	float y2 = parseFloatAttr(pNode, "y2");
	return {Vector2D(x1, y1), fillColor, strokeColor, strokeWidth, Vector2D(x2, y2)};
}

SVGPolyline XMLParser::parsePolyline(rapidxml::xml_node<> *pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth) {
	std::vector<Vector2D<float>> points = parsePointsAttr(pNode, "points");
	return {points[0], fillColor, strokeColor, strokeWidth, points, FillRuleHelper::fromName(parseStringAttr(pNode, "fill-rule"))};
}

SVGPolygon XMLParser::parsePolygon(rapidxml::xml_node<> *pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth) {
	std::vector<Vector2D<float>> points = parsePointsAttr(pNode, "points");
	return {points[0], fillColor, strokeColor, strokeWidth, points, FillRuleHelper::fromName(parseStringAttr(pNode, "fill-rule"))};
}

SVGText XMLParser::parseText(rapidxml::xml_node<> *pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth) {
	float x = parseFloatAttr(pNode, "x");
	float y = parseFloatAttr(pNode, "y");
	float dx = parseFloatAttr(pNode, "dx");
	float dy = parseFloatAttr(pNode, "dy");
	x += dx;
	y += dy;
	float fontSize = parseFloatAttr(pNode, "font-size");
	std::string data = pNode->value();
	return {Vector2D<float>{x, y}, fillColor, strokeColor, strokeWidth, data, fontSize, TextAnchorHelper::fromName(parseStringAttr(pNode, "text-anchor"))};
}

SVGPath XMLParser::parsePath(rapidxml::xml_node<>* pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth) {
	FillRule fillRule = FillRuleHelper::fromName(parseStringAttr(pNode, "fill-rule"));

	std::vector<PathPoint *> points;
	std::string d = parseStringAttr(pNode, "d"); // <-- get string of d attribute

	auto isCmd = [](char c) -> bool {
		char ch = tolower(c);
		return ch == 'm' || ch == 'l' || ch == 'h' || ch == 'v' || ch == 'z' || ch == 'c' || ch == 's' || ch == 'q' || ch == 't' || ch == 'a';
	};

	auto getLastPos = [](const std::vector<PathPoint *> &points) -> Vector2D<float> {
		if (points.empty()) return {0.0f, 0.0f};
		return points.back()->getPos();
	};

	// change all hyphens to blank space to use stringstream
	for (char &i : d) {
		if (i == ',') i = ' ';
	}

	//std::cout << "d after format: " << d << '\n';

	Vector2D<float> sta;
	std::stringstream buffer;
	std::string data;
	int size = (int) d.size();
	for (int i = 0; i < size; ++i) {
		if (!isCmd(d[i])) continue;
		char ins = tolower(d[i]);
		int nxt = -1;
		int tmpI = i + 1;
		data = "";
		while (tmpI < size) {
			if (isCmd(d[tmpI])) {
				nxt = tmpI;
				break;
			}
			data += d[tmpI];
			++tmpI;
		}

		buffer.clear();
		buffer.str(data);
		
		if (ins == 'm' || ins == 'l') { // <-- move-to and line command
			float x, y;
			while (buffer >> x >> y) {
				Vector2D<float> newPos = Vector2D<float>(x, y) + (isupper(d[i]) ? Vector2D<float>(0, 0) : getLastPos(points));
				points.push_back(new NormPathPoint(d[i], newPos));
				//std::cout << x << " " << y << '\n';
				if (ins == 'm') sta = newPos;
			}
		} else if (ins == 'h' || ins == 'v') { // <-- horizontal and vertical line
			float num;
			while (buffer >> num) {
				//std::cout << num << '\n';
				Vector2D<float> newPos;
				if (ins == 'h') newPos = Vector2D<float>(d[i] == 'H' ? num : getLastPos(points).x + num, getLastPos(points).y);
				else newPos = Vector2D<float>(getLastPos(points).x, d[i] == 'V' ? num : getLastPos(points).y + num);
				points.push_back(new NormPathPoint(d[i], newPos));
			}
		} else if (ins == 'q') { // <-- Quadratic Bezier Curve
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
		} else if (ins == 't') { // <-- reflection of previous quadratic bezier control's point
			float x, y;
			while (buffer >> x >> y) {
				//std::cout << x << " " << y << '\n';
				Vector2D<float> newPos = Vector2D<float>(x, y);
				if (d[i] == 't') newPos += getLastPos(points);
				Vector2D<float> cen;
				// If previous command not a quadratic-type, the control point is the same as the current point
				if (!points.empty() && points.back()->getPointType() != "quad") cen = getLastPos(points);
				else {
					QuadPathPoint *pQuad = static_cast<QuadPathPoint *>(points.back());
					// calculate new reflection control point
					cen = pQuad->getPos() + (pQuad->getPos() - pQuad->getCen());
				}
				points.push_back(new QuadPathPoint(d[i], newPos, cen));
			}
		} else if (ins == 'c') { // <-- Cubic Bezier Curve
			Vector2D<float> pos;
			float cen0x, cen0y, cen1x, cen1y;
			while (buffer >> cen0x >> cen0y >> cen1x >> cen1y >> pos.x >> pos.y) {
				//std::cout << cen0x << " " << cen0y << " " << cen1x << " " << cen1y << " " << pos.x << " " << pos.y << '\n';
				if (d[i] == 'C') points.push_back(new CubicPathPoint(d[i], pos, Vector2D<float>(cen0x, cen0y), Vector2D<float>(cen1x, cen1y)));
				else {
					Vector2D<float> lastPos = getLastPos(points);
					points.push_back(new CubicPathPoint(d[i], lastPos + pos, lastPos + Vector2D<float>(cen0x, cen0y), lastPos + Vector2D<float>(cen1x, cen1y)));
				}
			}
		} else if (ins == 's') { // <-- only first control point has reflection, second control point must be specified
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
		} else if (ins == 'a') { // <-- Arc
			Vector2D<float> radii;
			float xRotation;
			bool largeArcFlag;
			bool sweepFlag;
			Vector2D<float> pos;
			while (buffer >> radii.x >> radii.y >> xRotation >> largeArcFlag >> sweepFlag >> pos.x >> pos.y) {
				//std::cout << radii.x << " " << radii.y << " " << xRotation << " " << largeArcFlag << " " << sweepFlag << " " << pos.x << " " << pos.y << '\n';
				points.push_back(new ArcPathPoint(d[i], (d[i] == 'A' ? pos : getLastPos(points) + pos), radii, xRotation, largeArcFlag, sweepFlag));
			}
		} else if (ins == 'z') { // end current path
			// No parameter in z command
			// Current point goes back to the starting point
			points.push_back(new NormPathPoint(d[i], sta));
		}
		if (nxt == -1) break;
		i = nxt - 1; // go to position of next command
		//std::cout << "i = " << i << '\n';
	}

	return {*points[0], fillColor, strokeColor, strokeWidth, points, fillRule};
}

float XMLParser::parseFloatAttr(rapidxml::xml_node<> *pNode, const std::string &attrName) {
	float ret = 0.0;
	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute(attrName.c_str());
	if (pAttr == nullptr) { // <-- doesn't exist an attribute with name = attrName
		rapidxml::xml_node<>* pPar = pNode->parent();
		if (pPar != nullptr) return parseFloatAttr(pPar, attrName);
		// stroke, fill, opacity default must be 1
		if (attrName.find("stroke") != std::string::npos || attrName.find("fill") != std::string::npos || attrName.find("opacity") != std::string::npos)
			ret = 1;
		return ret;
	}
	std::string value = pAttr->value();	
	std::stringstream buffer(value);
	buffer >> ret;
	buffer.clear(); // <-- clear buffer
	// TODO: value is a real number
	// TODO: value is percentage (%)
	return ret;
}

std::string XMLParser::parseStringAttr(rapidxml::xml_node<> *pNode, const std::string &attrName) {
	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute(attrName.c_str());
	if (pAttr == nullptr) {
		// TODO: handle if no attribute name = attrName
		return "";
	}
	return pAttr->value();
}

SVGColor XMLParser::parseColor(rapidxml::xml_node<> *pNode, const std::string &attrName) {
	SVGColor color;
	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute(attrName.c_str());
	bool hasOpaque = false;
	rapidxml::xml_attribute<>* pOpa = pNode->first_attribute((attrName + "-opacity").c_str());
	hasOpaque |= (pOpa != nullptr);
	pOpa = pNode->first_attribute("opacity");
	hasOpaque |= (pOpa != nullptr);
	float opaque = parseFloatAttr(pNode, attrName + "-opacity") * parseFloatAttr(pNode, "opacity");
	if (pAttr == nullptr) { // <-- can't find any attribute with name = attrName
		rapidxml::xml_node<>* pPar = pNode->parent();
		// In case there is a parent node, recursively return the color of parent node
		// This works because only parent node of basic shape in this project is <g> tag which has color attributes
		if (pPar != nullptr) {
			SVGColor parColor = parseColor(pPar, attrName);
			if (hasOpaque) {
				//std::cout << "cur opa = " << opaque << '\n';
				parColor.a = (unsigned char)(255.0f * opaque);
			}
			return parColor;
		}
		// If no attribute with attrName specified, default color is black
		color = SVG_BLACK;
		if (attrName == "stroke") { // <-- If stroke is not specifed, then there is no stroke
			color = SVG_BLANK;
			return color;
		}
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
		color.a = (unsigned char) (255.0f * opaque);
		// TODO: More research required to make sure the input don't make the opaque overflowed or having unexpected behavior.
	}
	return color;
}

std::vector<Vector2D<float>> XMLParser::parsePointsAttr(rapidxml::xml_node<> *pNode, const std::string &attrName) {
	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute(attrName.c_str());
	if (pAttr == nullptr) return {};
	std::vector<Vector2D<float>> ret = {};

	std::string value = pAttr->value();
	for (char &i : value) if (i == ',') i = ' ';
	std::stringstream buffer(value);

	float x = 0;
	while (buffer >> x) {
		float y = 0;
		buffer >> y;
		ret.emplace_back(x, y); 
	}

	buffer.clear(); // <-- clear buffer
	return ret;
}

std::vector<std::string> XMLParser::parseTransformation(std::string& transformation) {
	std::vector<std::string> ret;

	for (char &i : transformation)
		if (i >= 'A' && i <= 'Z')
			i = tolower(i);
	
	std::string data;
	bool start = false;
	for (char &save : transformation) {
			if (save == ',' || save == '(' || save == ')') {
			data += ' ';
			if (save == ')') {
				ret.push_back(data);
				data = "";
				start = false;
			}
			continue;
		}
		if ((save >= 'a' && save <= 'z') || (save >= '0' && save <= '9') || save == '.') {
			if (!start) start = true;
		}
		if (start) data += save;
	}
	return ret;
}

ViewBox XMLParser::getViewBox() const { return viewBox; }

