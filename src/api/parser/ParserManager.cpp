#include <fstream>
#include <sstream>
#include "ParserManager.h"
#include "ParserHInit.h"

std::map<std::string, IParser *> ParserManager::parsers;
rapidxml::xml_document<> ParserManager::doc;

ParserManager::ParserManager() = default;

std::vector<Element *> ParserManager::parseFile(const std::string &fileName) {
	std::ifstream fin(fileName.c_str());
	if (!fin.is_open()) {
		std::cout << "Cannot open file\n";
		return {};
	}
	std::stringstream buffer;
	buffer << fin.rdbuf(); // <-- push file data into buffer stringstream
	fin.close();
	std::string svgData = buffer.str(); // <-- convert to string type
	doc.parse<0>(&svgData[0]); // <-- save ni xml_document type

	std::vector<Element*> ret = {};
	rapidxml::xml_node<>* pRoot = doc.first_node(); // <-- <svg>
	rapidxml::xml_node<>* pNode = pRoot->first_node();

	// Traversing xml file
	while (pNode != nullptr) {
		std::string nodeName = pNode->name(); // <-- get node's name
		if (nodeName == "defs") { // <-- contains gradient information
			// TODO: Parse and get all gradients (linear + radial)
			// TODO: Save gradients id
		}
		else if (nodeName == "g") {
			// TODO: Parse and get group attributes
			// TODO: Process to each element of group
			// TODO: May perform recursively when <g> contains other <g>
		}
		else { // <-- Shape type
			
		}
		pNode = pNode->next_sibling();
	}
	return ret;
}

void ParserManager::parseFile(const std::string &fileName, std::vector<Element *> &v) {
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
}

void ParserManager::free() {
	for (auto &parser : parsers) {
		delete parser.second;
	}
	parsers.clear();
}
