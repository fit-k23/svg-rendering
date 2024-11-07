#include <fstream>
#include <sstream>
#include "ParserManager.h"
#include "ParserHInit.h"

std::map<std::string, IParser *> ParserManager::parsers;
rapidxml::xml_document<> ParserManager::doc;
ParserManager ParserManager::instance;

ParserManager::ParserManager() = default;

ParserManager &ParserManager::getInstance() { return instance; }

ParserManager::~ParserManager() {
	for (auto &parser : parsers) delete parser.second;
}

std::vector<Element *> ParserManager::parseFile(const std::string &fileName) {

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
