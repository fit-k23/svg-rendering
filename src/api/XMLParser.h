#ifndef XML_PARSER_H_
#define XML_PARSER_H_

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Graphic.h"
#include "../../lib/rapidxml/rapidxml.hpp"

/**
 * @brief Parse SVG (XML format) file and handle its nodes, attributes
 * @note Xml document is declared through xml_document data type
 * @note Nodes and attributes are represented by xml_node and xml_attribute
 * @note Every xml file has only one root node
*/

class XMLParser{
	rapidxml::xml_document<> doc;
	Vector2D<float> viewPort;
	// TODO: add viewBox
public:
	/** @brief Default constructor */
	XMLParser();

	/**
	 * @brief Default destructor
	 * @note In case there are dynamic allocated memories
	*/
	~XMLParser() = default;

	/**
	 * @brief Set view port
	 * @param new view port
	*/
	void setViewPort(const Vector2D<float> &viewPort);

	/**
	 * @brief Get viewport information
	 * @return Vector2D type of viewport
	*/
	Vector2D<float> getViewPort();

	/**
	 * @brief Traverse through each nodes and attributes of SVG
	 * @note Handling and drawing in here
	*/
	void traverseXML(const std::string &fileName, std::vector<Element *> &v);

	/*
	* @brief Parse all common attributes of shapes
	* @note Avoid reusing fill,stroke,strokeWidth,transformation many times
	*/
	Element *parseShape(rapidxml::xml_node<>* pNode);

	/**
	 * @brief Parse rectangle attributes
	 * @return Rectangle object
	 * @note x, y, rx, ry is 0 by default
	*/
	SVGRect parseRect(rapidxml::xml_node<> *pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);

	/**
	 * @brief Parse Ellipse attributes
	 * @return a Ellipse object
	*/
	SVGEllipse parseEllipse(rapidxml::xml_node<>* pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);

	/**
	 * @brief Parse Circle attributes
	 * @return a Circle object
	*/
	SVGCircle parseCircle(rapidxml::xml_node<>* pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);

	/**
	 * @brief Parse Line attributes
	 * @return a Line object
	*/
	SVGLine parseLine(rapidxml::xml_node<>* pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);

	/**
	 * @brief Parse Polyline attributes
	 * @return a Polyline object
	*/
	SVGPolyline parsePolyline(rapidxml::xml_node<>* pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);

	/**
	 * @brief Parse Polygon attributes
	 * @return a Polygon object
	*/
	SVGPolygon parsePolygon(rapidxml::xml_node<>* pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);

	/**
	 * @brief Parse Text attributes
	 * @return a Text object
	*/
	SVGText parseText(rapidxml::xml_node<>* pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);

	/*
	* @brief Parse Path attributes
	*/
	SVGPath parsePath(rapidxml::xml_node<>* pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);

	/**
	 * @brief Get the float value of specific attribute
	 * @param node current xml node
	 * @param attrName attribute's name
	 * @return a float
	*/
	float parseFloatAttr(rapidxml::xml_node<> *pNode, std::string attrName);

	/**
	 * @brief Get the insight value of specific attribute
	 * @param pNode current xml node
	 * @param attrName attribute's name
	 * @return a string type
	*/
	std::string parseStringAttr(rapidxml::xml_node<> *pNode, std::string attrName);

	/**
	 * @brief Parse color attributes
	 * @param pNode current xml node
	 * @param attrName attribute's name
	 * @return SVGColor type
	*/
	SVGColor parseColor(rapidxml::xml_node<> *pNode, std::string attrName);

	/**
	 * @brief Parse set of points attributes
	 * @param pNode current xml node
	 * @param attrName attribute's name
	 * @return a vector of Vector2D<float> set of points
	*/
	std::vector<Vector2D<float>> parsePointsAttr(rapidxml::xml_node<> *pNode, std::string attrName);

	/*
	* @brief Parse transformation and add to vector
	*/
	std::vector<std::string> parseTransformation(std::string &transformation);
};

#endif // XML_PARSER_H_
