#ifndef SVG_RENDERING_XML_PARSER_H_
#define SVG_RENDERING_XML_PARSER_H_

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "Graphic.h"
#include "../../lib/rapidxml/rapidxml.hpp"
#include "../utils/StringHelper.h"

using std::vector;
using std::map;
using std::string;

/**
 * @brief Parse SVG (XML format) file and handle its nodes, attributes
 * @note Xml document is declared through xml_document data type
 * @note Nodes and attributes are represented by xml_node and xml_attribute
 * @note Every xml file has only one root node
 */

class XMLParser final {
	rapidxml::xml_document<> doc;
	Vector2D<float> viewPort;
	ViewBox viewBox{};
	Group *svg;
	map<string, Gradient *> grads;
	static XMLParser *instance;
	XMLParser();
public:
	/**
	 * @brief Get instance of XMLParser (apply singleton design pattern)
	 * @return current instance of XMLParser
	 */
	static XMLParser *getInstance();

	/** @brief Delete copy constructor to ensure the singleton design pattern */
	XMLParser(const XMLParser &other) = delete;
	~XMLParser();

	/**
	 * @brief Traverse through each node and attributes of SVG
	 * @param pNode the current pointer to current node of XML
	 * @param group the nearest group that has affected to current node
	 * @note Note that the root node (<svg>) is also considered a group
	 * @note Therefore, nearGrp is only nullptr only with root node
	 */
	void traverseXML(const string& fileName, rapidxml::xml_node<> *pNode, Group *group);

	/**
	 * @brief Get the root element (Group type).
	 * @return Group * the pointer to svg root
	 */
	Group* getRoot() const;

	/** @brief Get view box object */
	Vector2D<float> getViewPort() const;
	/**
	 * @brief Get view box object
	 * @return ViewBox type
	 */
	ViewBox getViewBox() const;
private:
	/**
	 * @brief Parse view box information
	 * @return a view box
	 */
	static ViewBox parseViewBox(rapidxml::xml_node<> *pNode);
	/**
	 * @brief Parse all common attributes of shapes
	 * @note Avoid reusing the parsing of fill,stroke,strokeWidth,transformation many times
	 * @return Element* type
	 */
	Element *parseShape(rapidxml::xml_node<> *pNode);
	/**
	 * @brief Parse rectangle attributes
	 * @return Rectangle object
	 */
	SVGRect parseRect(rapidxml::xml_node<> *pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);
	/**
	 * @brief Parse Ellipse attributes
	 * @return Ellipse object
	 */
	SVGEllipse parseEllipse(rapidxml::xml_node<> *pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);
	/**
	 * @brief Parse Circle attributes
	 * @return Circle object
	 */
	SVGCircle parseCircle(rapidxml::xml_node<> *pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);
	/**
	 * @brief Parse Line attributes
	 * @return Line object
	 */
	SVGLine parseLine(rapidxml::xml_node<> *pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);
	/**
	 * @brief Parse Polyline attributes
	 * @return Polyline object
	 */
	SVGPolyline parsePolyline(rapidxml::xml_node<> *pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);
	/**
	 * @brief Parse Polygon attributes
	 * @return Polygon object
	 */
	SVGPolygon parsePolygon(rapidxml::xml_node<> *pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);
	/**
	 * @brief Parse Text attributes
	 * @return Text object
	 */
	SVGText parseText(rapidxml::xml_node<> *pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);

	/**
	 * @brief Parse Path attributes
	 * @return Path object.
	 */
	SVGPath parsePath(rapidxml::xml_node<> *pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);

	/**
	 * @brief Parse gradient attributes
	 * @note All gradients will be stored in grads map
	 */
	void parseGradients(rapidxml::xml_node<> *pNode);
	/**
	 * @brief Parse gradient stops attributes
	 * @return vector<Stop> contains all stops of gradient
	 */
	vector<Stop> parseStops(rapidxml::xml_node<> *pNode);
	/**
	 * @brief Get the float value of specific attribute
	 * @param pNode current xml node
	 * @param attrName attribute's name
	 * @return float
	 */
	float parseFloatAttr(rapidxml::xml_node<> *pNode, const string& attrName);
	/**
	 * @brief Get the insight value of specific attribute
	 * @param pNode current xml node
	 * @param attrName attribute's name
	 * @return string type
	 */
	string parseStringAttr(rapidxml::xml_node<> *pNode, const string& attrName);
	/**
	 * @brief Parse color attributes
	 * @param pNode current xml node
	 * @param attrName attribute's name
	 * @return SVGColor type
	 */
	SVGColor parseColor(rapidxml::xml_node<> *pNode, const string& attrName, string &gradID);
	/**
	 * @brief Parse set of points attributes
	 * @param pNode current xml node
	 * @param attrName attribute's name
	 * @return vector<Vector2D<float>> set of points
	 */
	vector<Vector2D<float>> parsePointsAttr(rapidxml::xml_node<> *pNode, const string& attrName);
	/**
	 * @brief Parse transformation and add to vector
	 * @param transformation the transformation attributes
	 * @return vector<string> set of transformations.
	 */
	vector<string> parseTransformation(string transformation);
};

#endif // SVG_RENDERING_XML_PARSER_H_
