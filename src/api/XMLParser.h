#ifndef XML_PARSER_H_
#define XML_PARSER_H_

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Graphic.h"
#include "../../lib/rapidxml/rapidxml.hpp"
#include "../element/utils/Gradient.h"
#include "../element/utils/LinearGradient.h"
#include "../element/utils/RadialGradient.h"

/**
 * @brief Parse SVG (XML format) file and handle its nodes, attributes
 * @note Xml document is declared through xml_document data type
 * @note Nodes and attributes are represented by xml_node and xml_attribute
 * @note Every xml file has only one root node
*/

class XMLParser{
private:
	rapidxml::xml_document<> doc;
	Vector2D<float> viewPort;
	ViewBox viewBox{};
	std::map<std::string, Gradient *> grads;
public:
	/** @brief Default constructor */
	XMLParser();

	/**
	 * @brief Default destructor
	 * @note In case there are dynamic allocated memories
	*/
	~XMLParser();

	/**
	 * @brief Get viewport information
	 * @return Vector2D type of viewport
	*/
	Vector2D<float> getViewPort();

	/*
	* @brief Get view box object
	*/
	ViewBox getViewBox() const;

	/**
	 * @brief Traverse through each nodes and attributes of SVG
	 * @note Handling and drawing in here
	*/
	void traverseXML(const std::string &fileName, std::vector<Element *> &v);

	ViewBox parseViewBox(rapidxml::xml_node<> *pNode);

	/**
	 * @brief Propagate transformation from parent to children
	 * @note Ensure correct order of transformation (parent first, then children)
	*/
	void propagateTransform(std::vector<std::string> &transformation, const std::vector<std::string> &passTransforms);

	/**
	 * @brief Parse group attributes and apply to its children
	 * @note This function do
	*/
	void parseGroup(rapidxml::xml_node<>* pNode, std::vector<Element*>& v, const std::vector<std::string> &passTransform);

	/**
	 * @brief Parse all common attributes of shapes
	 * @note Avoid reusing fill,stroke,strokeWidth,transformation many times
	*/
	Element *parseShape(rapidxml::xml_node<>* pNode, const std::vector<std::string>& passTransform);

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

	/** @brief Parse Path attributes */
	SVGPath parsePath(rapidxml::xml_node<>* pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);

	/*
	* @brief Parse gradient attributes 
	* @note All gradients will be stored in grads map
	*/
	void parseGradients(rapidxml::xml_node<>* pNode, const std::vector<std::string> &passTransforms);

	/**
	 * @brief Get the float value of specific attribute
	 * @param node current xml node
	 * @param attrName attribute's name
	 * @return a float
	*/
	float parseFloatAttr(rapidxml::xml_node<> *pNode, const std::string& attrName);

	/**
	 * @brief Get the insight value of specific attribute
	 * @param pNode current xml node
	 * @param attrName attribute's name
	 * @return a string type
	*/
	std::string parseStringAttr(rapidxml::xml_node<> *pNode, const std::string& attrName);

	/**
	 * @brief Parse color attributes
	 * @param pNode current xml node
	 * @param attrName attribute's name
	 * @return SVGColor type
	*/
	SVGColor parseColor(rapidxml::xml_node<> *pNode, const std::string& attrName);

	/**
	 * @brief Parse set of points attributes
	 * @param pNode current xml node
	 * @param attrName attribute's name
	 * @return a vector of Vector2D<float> set of points
	*/
	std::vector<Vector2D<float>> parsePointsAttr(rapidxml::xml_node<> *pNode, const std::string& attrName);

	/** @brief Parse transformation and add to vector */
	std::vector<std::string> parseTransformation(std::string &transformation);
};

#endif // XML_PARSER_H_
