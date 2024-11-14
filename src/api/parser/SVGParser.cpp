#include "SVGParser.h"
#include "ParserManager.h"
#include "../Graphic.h"

std::vector<Element *> SVGParser::parse(rapidxml::xml_node<> *pNode, const std::string &attributeName) {
//	auto *ellipseParser = ParserManager::getParser<SVGEllipse>("ellipse");
//	auto *circleParser = ParserManager::getParser<SVGCircle>("circle");
//	auto *rectParser = ParserManager::getParser<SVGRect>("rect");
//	auto *lineParser = ParserManager::getParser<SVGLine>("line");
//	auto *polygonParser = ParserManager::getParser<SVGPolygon>("polygon");
//	auto *polylineParser= ParserManager::getParser<SVGPolyline>("polyline");
//	auto *textParser = ParserManager::getParser<SVGText>("text");
//	auto *pathParser = ParserManager::getParser<SVGPath>("path");
//	auto *groupParser = ParserManager::getParser<Group>("group");

	std::vector<Element *> v;

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
			auto *parser = ParserManager::getParser<Element *>(nodeName);
			if (parser != nullptr) {
				auto *element = parser->parse(pNode, "");
				if (element != nullptr) {
					v.push_back(element);
				}
			}
		}
		// TODO: break just for testing
		pNode = pNode->next_sibling();
	}
	return {};
}
