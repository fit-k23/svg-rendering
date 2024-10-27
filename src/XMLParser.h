#ifndef XML_PARSER_H_
#define XML_PARSER_H_

#include <iostream>
#include <sstream>
#include <string>
#include "../lib/rapidxml/rapidxml.hpp"
#include "../lib/raylib/raylib.h"
#include "element/utils/Vector2D.h"

/**
* @brief Parse SVG (XML format) file and handle its nodes, attributes
* @note Xml document is declared through xml_document data type
* @note Nodes and attributes are represented by xml_node and xml_attribute
* @note Every xml file has only one root node 
**/

class XMLParser {
private:
	rapidxml::xml_document<> doc;
	Vector2D<double> viewPort;
public:
	/**
	* @brief Default constructor
	* @note Nothing much here 
	**/
	XMLParser() = default;

	/**
	* @brief Default destructor
	* @note In case there are dynamic allocated memories
	**/
	~XMLParser() = default;

	/**
	* @brief Get viewport information
	* @return Vector2D type of viewport
	**/
	template<typename T>
	Vector2D<T> getViewPort();

	/**
	* @brief Load the xml file
	**/
	void loadXML(const std::string& fileName);

	/**
	* @brief Traverse through each nodes and attributes of SVG
	* @note Handling and drawing in here
	**/
	void traverseXML();

	/**
	* @brief Get the insight value of specific attribute
	* @param node: current xml node
	* @param attrName: name of attribute
	* @return a string type
	**/
	std::string getStringAttr(rapidxml::xml_node<>* pNode, std::string attrName); 

	/**
	* @brief Get the double value of specific attribute
	* @param node: current xml node
	* @param attrName: name of attribute
	* @return a double
	**/
	double getDoubleAttr(rapidxml::xml_node<>* pNode, std::string attrName);
};

#endif // XML_PARSER_H_
