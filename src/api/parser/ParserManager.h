#ifndef SVG_RENDERING_PARSER_MANAGER_H
#define SVG_RENDERING_PARSER_MANAGER_H

#include <iostream>
#include <map>
#include "IParser.h"
#include "TParser.h"
#include "../../../src/element/Element.h"

/*
* @brief This class only has one instance 
* @note Apply singleton design pattern
*/

class ParserManager {
	static std::map<std::string, IParser *> parsers; // <-- store type of parser with corresponding node name
	static rapidxml::xml_document<> doc;
	static ParserManager instance; // <-- instance of ParserManager
	ParserManager();
	~ParserManager(); // delete allocated memory in parsers
public:
	/*
	* @brief Get current instance of parser manager class
	* @note Static method that controls access to Singleton instance
	*/
	static ParserManager &getInstance();
	
	/*
	* @brief Register a new type of parser
	*/
	template<typename T>
	bool registerParser(const std::string &name, TParser<T> *parser) {
		auto parserN = parsers.find(name);
		if (parserN == parsers.end()) { // if not found type of parser
			parsers[name] = parser; // <-- successfully register new type of parser
			return true;
		}
		return false;
	}

	/*
	* @brief Parse xml file and store elements in a Element-pointer vector
	*/
	void parseFile(const std::string &fileName, std::vector<Element *> &v);
	std::vector<Element *> parseFile(const std::string &fileName);

	/*
	* @brief Get the proper parser for the node name
	*/
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
