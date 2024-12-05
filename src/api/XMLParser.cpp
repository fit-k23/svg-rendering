#include "XMLParser.h"

XMLParser *XMLParser::instance = new XMLParser();

XMLParser::XMLParser() : viewPort{}, viewBox{ 0, 0, -1, -1 }, svg(nullptr), grads() {}

XMLParser* XMLParser::getInstance() { return instance == nullptr ? instance = new XMLParser() : instance; }

XMLParser::~XMLParser() {
	for (auto &gradient : grads)
		delete gradient.second;
	std::cout << "Deleting gradients pointers\n";
	delete svg;
	std::cout << "Deleting root\n";
}

void XMLParser::traverseXML(const std::string &fileName, rapidxml::xml_node<> *pNode, Group *group) {
	if (group == nullptr) {
		//std::cout << "Deleting gradients pointers\n";
		for (auto &gradient : grads) {
			delete gradient.second;
		}
		delete svg;
		//std::cout << "Delete root ta ta ta\n";
		grads.clear();
		std::ifstream fin(fileName.c_str());
		if (!fin.is_open()) {
			std::cout << "Cannot open file " << fileName << '\n';
			svg = nullptr;
			return;
		}
		//std::cout << "Reading " << fileName << "\n";
		std::stringstream buffer;
		buffer << fin.rdbuf(); // <-- push file data to buffer
		fin.close();
		std::string tmpFile = buffer.str();
		doc.parse<0>(&tmpFile[0]);
		rapidxml::xml_node<> *pRoot = doc.first_node(); // <-- <svg>
		std::cout << "Root name: " << pRoot->name() << '\n';

		viewPort.x = parseFloatAttr(pRoot, "width");
		viewPort.y = parseFloatAttr(pRoot, "height");

		std::cout << "View port: " << viewPort.x << " " << viewPort.y << '\n';

		viewBox = parseViewBox(pRoot);

		auto *grp = new Group();
		svg = grp;
		for (rapidxml::xml_node<> *pChild = pRoot->first_node(); pChild != nullptr; pChild = pChild->next_sibling())
			traverseXML(fileName, pChild, grp);
		return;
	}

	if (pNode == nullptr) {
		std::cout << "Current node is nullptr\n";
		return;
	}

	// TODO: Propagate fill,stroke,opacity attributes from parent to child
	for (auto &attr: group->getAttr()) {
		std::string attrName = attr.first;
		// <g> in this project only has stroke, fill, opacity, and transform attributes
		// if (attrName.find("stroke") == std::string::npos && attrName.find("fill") == std::string::npos && attrName.find("opacity") == std::string::npos && attrName.find("transform") == std::string::npos) continue;
		bool has = false;
		for (rapidxml::xml_attribute<> *pAttr = pNode->first_attribute(); pAttr != nullptr; pAttr = pAttr->next_attribute()) {
			if (pAttr->name() == attrName) {
				has = true;
				if (pAttr->name() == "opacity") {
					std::string newOpacity = std::to_string(std::stof(pAttr->name()) * std::stof(attr.second));
					pAttr->value(doc.allocate_string(newOpacity.c_str()));
				}
				break;
			}
		}
		if (!has && attrName != "transform") {
			char *name = doc.allocate_string(attr.first.c_str());
			char *value = doc.allocate_string(attr.second.c_str());
			// std::cout << "pass name: " << name << " pass value: " << value << '\n';
			pNode->append_attribute(doc.allocate_attribute(name, value));
		}
	}

	// TODO: Process current node
	std::string nodeName = pNode->name();
	if (nodeName == "defs") {
		parseGradients(pNode);
	} else if (nodeName == "g") {
		auto *grp = new Group();
		// Adding attributes to Group class
		for (rapidxml::xml_attribute<> *pAttr = pNode->first_attribute(); pAttr != nullptr; pAttr = pAttr->next_attribute())
			grp->addAttr(pAttr->name(), pAttr->value());
		std::string transformAttr = parseStringAttr(pNode, "transform");
		if (!transformAttr.empty()) {
			grp->setTransformation(parseTransformation(transformAttr));
		}
		// Add group to nearest group parent
		group->addElement(grp);

		// grp->dbg();

		// Recursively handle the children with new group parent = grp
		for (rapidxml::xml_node<> *pChild = pNode->first_node(); pChild != nullptr; pChild = pChild->next_sibling())
			traverseXML(fileName, pChild, grp);
	} else {
		Element *shape = parseShape(pNode);
		if (shape != nullptr) {
			group->addElement(shape);
		}
	}
}

Group *XMLParser::getRoot() const { return svg; }

ViewBox XMLParser::parseViewBox(rapidxml::xml_node<> *pNode) {
	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute("viewBox");
	if (pAttr == nullptr) return {0, 0, -1, -1};
	std::istringstream is(pAttr->value());
	ViewBox v{};
	is >> v.minX >> v.minY >> v.width >> v.height;
	return v;
}

Vector2D<float> XMLParser::getViewPort() const { return viewPort; }

void XMLParser::parseGradients(rapidxml::xml_node<> *pNode) {
	rapidxml::xml_node<> *pChild = pNode->first_node();
	if (pChild == nullptr) return;

	while (pChild != nullptr) {
		Gradient *gradient = nullptr;
		std::string nodeName = pChild->name();
		// parse ID
		std::string id = parseStringAttr(pChild, "id");

		if (grads.find(id) != grads.end()) {
			continue;
		}

		// parse gradient transformations
		std::vector<std::string> transforms = parseTransformation(parseStringAttr(pChild, "gradientTransform"));

		// parse gradient units
		std::string units = parseStringAttr(pChild, "gradientUnits");

		// parse stops
		std::vector<Stop> stops = parseStops(pChild);

		if (nodeName == "linearGradient") {
			float x1 = parseFloatAttr(pChild, "x1");
			float y1 = parseFloatAttr(pChild, "y1");
			float x2 = parseFloatAttr(pChild, "x2");
			float y2 = parseFloatAttr(pChild, "y2");
			gradient = new LinearGradient(id, transforms, units, Vector2D<float>(x1, y1), Vector2D<float>(x2, y2));
		} else if (nodeName == "radialGradient") {
			float cx = parseFloatAttr(pChild, "cx");
			float cy = parseFloatAttr(pChild, "cy");
			float r = parseFloatAttr(pChild, "r");
			float fx = parseFloatAttr(pChild, "fx");
			float fy = parseFloatAttr(pChild, "fy");
			gradient = new RadialGradient(id, transforms, units, Vector2D<float>(cx, cy), r, Vector2D<float>(fx, fy));
		}

		if (gradient != nullptr) {
			gradient->setStops(stops);
			//gradient->dbg();
			grads[id] = gradient;
		}

		pChild = pChild->next_sibling();
	}
}

std::vector<Stop> XMLParser::parseStops(rapidxml::xml_node<> *pNode) {
	std::vector<Stop> stops = {};
	rapidxml::xml_node<> *pChild = pNode->first_node();
	while (pChild != nullptr) {
		float offset = parseFloatAttr(pChild, "offset");
		if (offset < 0.0f) offset = 0.0f;
		if (offset > 1.0f) offset = 1.0f;
		std::string id;
		SVGColor stopColor = parseColor(pChild, "stop-color", id);
		if (!stops.empty()) {
			if (offset < stops.back().getOffset()) {
				offset = stops.back().getOffset();
			}
		}
		stops.emplace_back(offset, stopColor);
		pChild = pChild->next_sibling();
	}
	return stops;
}

Element *XMLParser::parseShape(rapidxml::xml_node<> *pNode) {
	std::string fillGradID, strokeGradID;
	SVGColor fillColor = parseColor(pNode, "fill", fillGradID);
	SVGColor strokeColor = parseColor(pNode, "stroke", strokeGradID);
	float strokeWidth = parseFloatAttr(pNode, "stroke-width");
	std::string transformAttr = parseStringAttr(pNode, "transform");
	std::vector<std::string> transformation = parseTransformation(transformAttr);

	std::string nodeName = pNode->name();
	Element *ret = nullptr;
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
	}

	if (ret != nullptr) {
		ret->setTransformation(transformation);
		if (!fillGradID.empty()) {
			if (grads.find(fillGradID) != grads.end())
				ret->setFillGradient(grads[fillGradID]);
			else std::cout << "Fill gradient of id " << fillGradID << " not found\n";
		}
		if (!strokeGradID.empty()) {
			if (grads.find(strokeGradID) != grads.end())
				ret->setStrokeGradient(grads[strokeGradID]);
			else std::cout << "Stroke gradient of id " << strokeGradID << " not found\n";
		}
		//ret->dbg();
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
		char ch = (char) tolower(c);
		return ch == 'm' || ch == 'l' || ch == 'h' || ch == 'v' || ch == 'z' || ch == 'c' || ch == 's' || ch == 'q' || ch == 't' || ch == 'a';
	};

	auto getLastPos = [](const std::vector<PathPoint *> &points) -> Vector2D<float> {
		if (points.empty()) return {0.0f, 0.0f};
		return points.back()->getPos();
	};

	// change all hyphens to blank space to use stringstream
	for (char &i : d) {
		if (i == ',' || i == '\n' || i == '\t') i = ' ';
	}

	Vector2D<float> sta;
	std::stringstream buffer;
	std::string data;
	int size = (int) d.size();
	for (int i = 0; i < size; ++i) {
		if (!isCmd(d[i])) continue;
		char ins = (char) (tolower(d[i]));
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

		buffer.clear(); // reset stringstream cursor to begin
		buffer.str(data);
		
		if (ins == 'm' || ins == 'l') { // <-- move-to and line command
			float x, y;
			int cnt = 0;
			while (buffer >> x >> y) {
				++cnt;
				Vector2D<float> newPos = Vector2D<float>(x, y);
				if (!isupper(d[i])) newPos += getLastPos(points);
				char newCmd = d[i];
				if (ins == 'm') {
					// The starting point doesn't change unless the path is explicitly restarted with another m or similar command.
					if (cnt == 1) {
						newCmd = d[i];
						sta = newPos;
					}
					else newCmd = (d[i] == 'M' ? 'L' : 'l'); 
				}
				points.push_back(new NormPathPoint(newCmd, newPos));
			}
		} else if (ins == 'h' || ins == 'v') { // <-- horizontal and vertical line
			float num;
			while (buffer >> num) {
				Vector2D<float> newPos;
				if (ins == 'h') newPos = Vector2D<float>(d[i] == 'H' ? num : getLastPos(points).x + num, getLastPos(points).y);
				else newPos = Vector2D<float>(getLastPos(points).x, d[i] == 'V' ? num : getLastPos(points).y + num);
				points.push_back(new NormPathPoint(d[i], newPos));
			}
		} else if (ins == 'q') { // <-- Quadratic Bezier Curve
			float x, y, cenX, cenY;
			while (buffer >> cenX >> cenY >> x >> y) {
				Vector2D<float> newPos = Vector2D<float>(x, y);
				Vector2D<float> newCen = Vector2D<float>(cenX, cenY);
				if (d[i] == 'q') {
					newPos += getLastPos(points);
					newCen += getLastPos(points);
				}
				points.push_back(new QuadPathPoint(d[i], newPos, newCen));
			}
		} else if (ins == 't') { // <-- reflection of previous quadratic bezier control's point
			float x, y;
			while (buffer >> x >> y) {
				Vector2D<float> newPos = Vector2D<float>(x, y);
				if (d[i] == 't') newPos += getLastPos(points);
				Vector2D<float> cen;
				// If previous command not a quadratic-type, the control point is the same as the current point
				if (!points.empty() && points.back()->getPointType() != "quad") {
					cen = getLastPos(points);
				} else {
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
				if (d[i] == 'C') {
					points.push_back(new CubicPathPoint(d[i], pos, Vector2D<float>(cen0x, cen0y), Vector2D<float>(cen1x, cen1y)));
				} else {
					Vector2D<float> lastPos = getLastPos(points);
					points.push_back(new CubicPathPoint(d[i], lastPos + pos, lastPos + Vector2D<float>(cen0x, cen0y), lastPos + Vector2D<float>(cen1x, cen1y)));
				}
			}
		} else if (ins == 's') { // <-- only first control point has reflection, second control point must be specified
			float x, y, cen2x, cen2y;
			while (buffer >> cen2x >> cen2y >> x >> y) {
				Vector2D<float> newPos = Vector2D<float>(x, y);
				Vector2D<float> cen2 = Vector2D<float>(cen2x, cen2y);
				if (d[i] == 's') {
					newPos += getLastPos(points);
					cen2 += getLastPos(points);
				}
				Vector2D<float> cen1;
				// If previous cmd not cubic-type, start control point is the same as the curve starting point (current point)
				if (!points.empty() && points.back()->getPointType() != "cubic") {
					cen1 = points.back()->getPos();
				} else { // <-- start control point is reflection of previous end control point and current point.
					CubicPathPoint *pCubic = static_cast<CubicPathPoint *>(points.back()); // don't use points[i - 1]
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
				points.push_back(new ArcPathPoint(d[i], (d[i] == 'A' ? pos : getLastPos(points) + pos), radii, xRotation, largeArcFlag, sweepFlag));
			}
		} else if (ins == 'z') { // end current path
			// No parameter in z command
			// Current point goes back to the starting point
			points.push_back(new NormPathPoint(d[i], sta));
		}
		if (nxt == -1) break;
		i = nxt - 1; // go to position of next command
	}

	return {*points[0], fillColor, strokeColor, strokeWidth, points, fillRule};
}

float XMLParser::parseFloatAttr(rapidxml::xml_node<> *pNode, const std::string &attrName) {
	float ret = 0.0;
	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute(attrName.c_str());
	if (pAttr == nullptr) { // <-- doesn't exist an attribute with name = attrName
		std::string nodeName = pNode->name();
		if (nodeName.find("Gradient") != std::string::npos) { // <-- Default value for gradient attributes
			std::string units = parseStringAttr(pNode, "gradientUnits");
			if (attrName == "x1" || attrName == "y1" || attrName == "y2") return 0.0f;
			else if (attrName == "x2") return (units[0] == 'o' ? 1.0f : viewPort.x);
			else if (attrName == "cx" || attrName == "cy" || attrName == "r") {
				if (units[0] == 'o') return 0.5f;
				else if (attrName == "cx") return 0.5f * viewPort.x;
				else if (attrName == "cy") return 0.5f * viewPort.y;
				// I think it represents the half diagnol of view port when units = userSpaceOnUse ???
				// Can't find document on this
				return 0.5f * (((viewPort.x * viewPort.x) + (viewPort.y * viewPort.y)) * 0.5f); // r 
			}
			else if (attrName == "fx" || attrName == "fy") {
				return (attrName == "fx" ? parseFloatAttr(pNode, "cx") : parseFloatAttr(pNode, "cy"));
			}
		}
		// stroke-width, fill and stroke opacity default must be 1
		if (attrName.find("stroke") != std::string::npos || attrName.find("fill") != std::string::npos || attrName.find("opacity") != std::string::npos)
			ret = 1.0f;
		return ret;
	}
	std::string value = pAttr->value();	
	std::stringstream buffer(value);
	buffer >> ret;
	// If value is percentage (%)
	if (value.find("%") != std::string::npos) {
		ret /= 100.0f;
		std::string nodeName = pNode->name();
		if (nodeName.find("Gradient") != std::string::npos) {
			std::string units = parseStringAttr(pNode, "gradientUnits");
			if (units[0] == 'u') { // userSpaceOnUse
				if (attrName == "fx" || attrName == "fy") return (attrName == "fx" ? parseFloatAttr(pNode, "cx") : parseFloatAttr(pNode, "cy"));
				else if (attrName.find("x") != std::string::npos) return viewPort.x * ret;
				else if (attrName.find("y") != std::string::npos) return viewPort.y * ret;
				else if (attrName == "r") return 0.5f * (((viewPort.x * viewPort.x) + (viewPort.y * viewPort.y)) * 0.5f); // r 
			}
		}
	}
	// If the unit is point (pt)
	// else if ((attrName == "width" || attrName == "height") && value.find("pt") != std::string::npos) ret *= 1.333333333f;
	return ret;
}

std::string XMLParser::parseStringAttr(rapidxml::xml_node<> *pNode, const std::string &attrName) {
	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute(attrName.c_str());
	if (pAttr == nullptr) {
		// TODO: handle if no attribute name = attrName
		if (attrName == "gradientUnits") return "objectBoundingBox";
		return "";
	}
	return pAttr->value();
}

SVGColor XMLParser::parseColor(rapidxml::xml_node<> *pNode, const std::string &attrName, std::string &gradID) {
	SVGColor color;
	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute(attrName.c_str());

	float opaque;
	if (attrName == "stop-color") opaque = parseFloatAttr(pNode, "stop-opacity");
	else opaque = parseFloatAttr(pNode, attrName + "-opacity") * parseFloatAttr(pNode, "opacity");
	if (pAttr == nullptr) { // <-- can't find any attribute with name = attrName
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
		// TODO: Get the id
		for (int i = 5; i < (int)value.size() - 1; ++i)
			gradID += value[i];
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

	return ret;
}

std::vector<std::string> XMLParser::parseTransformation(std::string transformation) {
	std::vector<std::string> ret;

	for (char &i : transformation)
		if (i >= 'A' && i <= 'Z')
			i = (char) tolower(i);

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