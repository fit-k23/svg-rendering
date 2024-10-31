#ifndef XML_PARSER_H_
#define XML_PARSER_H_

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "../../lib/rapidxml/rapidxml.hpp"
#include "Graphic.h"

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
  // TODO: add viewBox
  std::map<std::string, Gradient*> gradients; // <-- store all gradients with its id
public:
	/**
	* @brief Default constructor
	* @note Nothing much here 
	**/
	XMLParser();

	/**
	* @brief Default destructor
	* @note In case there are dynamic allocated memories
	**/
	~XMLParser() = default;

	/**
	* @brief Get viewport information
	* @return Vector2D type of viewport
	**/
	Vector2D<double> getViewPort();

	/**
	* @brief Traverse through each nodes and attributes of SVG
	* @note Handling and drawing in here
	**/
	void traverseXML(const std::string& fileName, std::vector<Element*>& v);
	
  /**
	* @brief Get the insight value of specific attribute
	* @param node: current xml node
	* @param attrName: name of attribute
	* @return a string type
	**/
	std::string parseStringAttr(rapidxml::xml_node<>* pNode, std::string attrName); 

	/**
	* @brief Get the double value of specific attribute
	* @param node: current xml node
	* @param attrName: name of attribute
	* @return a double
	**/
	double parseDoubleAttr(rapidxml::xml_node<>* pNode, std::string attrName);

	/**
	 * @brief Parse color attributes
	 * @param pNode current xml node
	 * @param attrName the attribute name to find value
	 * @return SVGColor type
	 */
	SVGColor parseColor(rapidxml::xml_node<>* pNode, std::string attrName);

	/**
	 * @brief Parse rectangle attributes
	 * @return Rectangle object
	 * @note x, y, rx, ry is 0 by default
	 */
	Rect parseRect(rapidxml::xml_node<> *pNode);

	/*
	* @brief Parse Circle attributes
	* @return a Circle object
	*/
	Circle parseCircle(rapidxml::xml_node<>* pNode);
};

#endif // XML_PARSER_H_
