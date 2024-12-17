#ifndef SVG_RENDERING_PARSER_MANAGER_H
#define SVG_RENDERING_PARSER_MANAGER_H

#include <iostream>
#include <map>
#include "IParser.h"
#include "TParser.h"
#include "../../../src/element/Element.h"

class ParserManager {
	static std::map<std::string, IParser *> parsers; // <-- store type of parser with corresponding node name
	static rapidxml::xml_document<> doc;
	ParserManager();
	~ParserManager(); // delete allocated memory in parsers
public:
	/** @brief Register a new type of parser */
	template<typename T>
	static bool registerParser(const std::string &name, TParser<T> *parser) {
		auto parserN = parsers.find(name);
		if (parserN == parsers.end()) { // if not found type of parser
			parsers[name] = parser; // <-- successfully register new type of parser
			return true;
		}
		return false;
	}

	/** @brief Parse xml file and store elements in a Element-pointer vector */
	static void parseFile(const std::string &fileName, std::vector<Element *> &v);
	static std::vector<Element *> parseFile(const std::string &fileName);

	/** @brief Get the proper parser with given name and return type */
	template<typename T>
	static TParser<T> *getParser(const std::string &name) {
		if (auto it = parsers.find(name); it != parsers.end()) {
			return dynamic_cast<TParser<T> *>(it->second);
		}
		return nullptr;
	}

	static IParser *getParser(const std::string &name) {
		if (auto it = parsers.find(name); it != parsers.end()) {
			return it->second;
		}
		return nullptr;
	}

	template<typename T>
	static T requestToParse(const std::string &name, rapidxml::xml_node<> *pNode, const std::string &attributeName) {
		TParser<T> *parser{getParser<TParser<T> *>(name)};
		if (parser != nullptr) {
			return parser->parse(pNode, attributeName);
		}
		return nullptr;
	}

	static void free();
};

#endif //SVG_RENDERING_PARSER_MANAGER_H
