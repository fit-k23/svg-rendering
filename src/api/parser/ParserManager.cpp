#include "ParserManager.h"
ParserManager::ParserManager() = default;

ParserManager *ParserManager::instance = new ParserManager();

ParserManager &ParserManager::getInstance() {
	if (instance == nullptr) instance = new ParserManager();
	return *instance;
}

bool ParserManager::registerParser(IParser *parse) {
	std::string attributeName = parse->getAttributeName();
	auto parserN = parsers.find(attributeName);
	if (parserN == parsers.end()) {
		parsers[attributeName] = parse;
		return true;
	}
	return false;
}

std::vector<Element *> ParserManager::parseFile(const std::string &fileName) {
	return std::vector<Element *>();
}

Element *ParserManager::requestToParse(const std::string &attributeName, rapidxml::xml_node<> *pNode) {
	auto parserN = parsers.find(attributeName);
	if (parserN == parsers.end()) {
		return nullptr;
	}
	return parserN->second->parse(pNode);
}
