#include "SVGParser.h"
#include "ParserManager.h"
#include "../Graphic.h"

std::vector<Element *> SVGParser::parse(rapidxml::xml_node<> *pNode, const std::string &attributeName) {
	auto *ellipseParser = ParserManager::getInstance().getParser<SVGEllipse>("ellipse");
	auto *circleParser = ParserManager::getInstance().getParser<SVGCircle>("circle");
	auto *rectParser = ParserManager::getInstance().getParser<SVGRect>("rect");
	auto *lineParser = ParserManager::getInstance().getParser<SVGLine>("line");
	auto *polygonParser = ParserManager::getInstance().getParser<SVGPolygon>("polygon");
	auto *polylineParser= ParserManager::getInstance().getParser<SVGPolyline>("polyline");
	auto *textParser = ParserManager::getInstance().getParser<SVGText>("text");
	auto *pathParser = ParserManager::getInstance().getParser<Group>("path");
	auto *groupParser = ParserManager::getInstance().getParser<SVGEllipse>("group");
	return {};
}
