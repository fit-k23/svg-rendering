#ifndef SVG_RENDERING_PARSER_MANAGER_H
#define SVG_RENDERING_PARSER_MANAGER_H

#include "IParser.h"
#include <map>

class ParserManager {
	static std::map<std::string, IParser *> parsers;
	static ParserManager *instance;
	ParserManager();
public:
	static ParserManager &getInstance();
	bool registerParser(IParser *parse);
	std::vector<Element *> parseFile(const std::string &fileName);
	Element *requestToParse(const std::string &attributeName, rapidxml::xml_node<> *pNode);
};

#endif //SVG_RENDERING_PARSER_MANAGER_H
