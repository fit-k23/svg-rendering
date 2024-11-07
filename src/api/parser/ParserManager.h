#ifndef SVG_RENDERING_PARSER_MANAGER_H
#define SVG_RENDERING_PARSER_MANAGER_H

#include <iostream>
#include <map>
#include "IParser.h"
#include "TParser.h"
#include "../../../src/element/Element.h"

class ParserManager {
	static std::map<std::string, IParser *> parsers;
	static rapidxml::xml_document<> doc;
	static ParserManager instance;
	ParserManager();
	~ParserManager();
public:
	static ParserManager &getInstance();
	template<typename T>
	bool registerParser(const std::string &name, TParser<T> *parser) {
		auto parserN = parsers.find(name);
		if (parserN == parsers.end()) {
			parsers[name] = parser;
			return true;
		}
		return false;
	}
	void parseFile(const std::string &fileName, std::vector<Element *> &v);
	std::vector<Element *> parseFile(const std::string &fileName);
	template<typename T>
	TParser<T> *getParser(const std::string &name) {
		auto it = parsers.find(name);
		if (it != parsers.end()) {
			return dynamic_cast<TParser<T> *>(it->second);
		}
		return nullptr;
	}

	template<typename T>
	T requestToParse(const std::string &name, rapidxml::xml_node<> *pNode, const std::string &attributeName) {
		TParser<T> *parser{getParser<TParser<T> *>(name)};
		if (parser != nullptr) {
			return parser->parse(pNode, attributeName);
		}
		return nullptr;
	}
};

#endif //SVG_RENDERING_PARSER_MANAGER_H
