#ifndef SVG_RENDERING_XML_PARSER_H_
#define SVG_RENDERING_XML_PARSER_H_

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
	Element *svg;
	std::map<std::string, Gradient*> grads;
	static XMLParser *instance;
public:
	/**
	 * @brief Get instance of XMLParser (apply singleton design pattern)
	 * @return current instance of XMLParser
	 * @note This function is static
	*/
	static XMLParser* getInstance();

	/** @brief Delete copy constructor to ensure the singleton design pattern */
	XMLParser(const XMLParser &other) = delete;

	/**
	 * @brief Destructor of XMLParser
	 * @note Delete allocated memory of map gradients and root
	*/
	~XMLParser();

	/**
	 * @brief Traverse through each nodes and attributes of SVG
	 * @param pNode the current pointer to current node of XML
	 * @param nearGrp the nearest group that has affected to current node
	 * @note Note that the root node (<svg>) is also considered a group
	 * @note Therefore, nearGrp is only nullptr only with root node
	*/
	void traverseXML(const std::string& fileName, rapidxml::xml_node<>* pNode, Element *nearGrp);

	/**
	 * @brief Get the root element (Group type).
	 * @return Element * the pointer to svg root
	 * @note This function doesn't change any attributes
	*/
	Element* getRoot() const;

	/**
	 * @brief Get view box object
	 * @note This function doesn't change any attributes
	*/
	Vector2D<float> getViewPort() const;
	/**
	 * @brief Get view box object
	 * @return ViewBox type
	 * @note This function doesn't change any attributes
	 */
	ViewBox getViewBox() const;
private:
	/** @brief Default constructor */
	XMLParser();

	/**
	 * @brief Parse view box information
	 * @return a view box
	*/
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
	void parseGroup(rapidxml::xml_node<> *pNode, std::vector<Element*> &v, const std::vector<std::string> &passTransform);
	/**
	 * @brief Parse all common attributes of shapes
	 * @note Avoid reusing the parsing of fill,stroke,strokeWidth,transformation many times
	 * @return Element* type
	*/
	Element *parseShape(rapidxml::xml_node<>* pNode);
	/**
	 * @brief Parse rectangle attributes
	 * @return Rectangle object
	*/
	SVGRect parseRect(rapidxml::xml_node<> *pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);
	/**
	 * @brief Parse Ellipse attributes
	 * @return Ellipse object
	*/
	SVGEllipse parseEllipse(rapidxml::xml_node<>* pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);
	/**
	 * @brief Parse Circle attributes
	 * @return Circle object
	*/
	SVGCircle parseCircle(rapidxml::xml_node<>* pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);
	/**
	 * @brief Parse Line attributes
	 * @return Line object
	*/
	SVGLine parseLine(rapidxml::xml_node<>* pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);
	/**
	 * @brief Parse Polyline attributes
	 * @return Polyline object
	*/
	SVGPolyline parsePolyline(rapidxml::xml_node<>* pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);
	/**
	 * @brief Parse Polygon attributes
	 * @return Polygon object
	*/
	SVGPolygon parsePolygon(rapidxml::xml_node<>* pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);
	/**
	 * @brief Parse Text attributes
	 * @return Text object
	 */
	SVGText parseText(rapidxml::xml_node<>* pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);

	/**
	 * @brief Parse Path attributes
	 * @return Path object.
	 */
	SVGPath parsePath(rapidxml::xml_node<>* pNode, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth);

	/**
	 * @brief Parse gradient attributes
	 * @note All gradients will be stored in grads map
	 */
	void parseGradients(rapidxml::xml_node<>* pNode, const std::vector<std::string> &passTransforms);
	/**
	 * @brief Parse gradient stops attributes
	 * @return vector<Stop> contains all stops of gradient
	 */
	std::vector<Stop> parseStops(rapidxml::xml_node<> *pNode);
	/**
	 * @brief Get the float value of specific attribute
	 * @param pNode current xml node
	 * @param attrName attribute's name
	 * @return float
	 */
	float parseFloatAttr(rapidxml::xml_node<> *pNode, const std::string& attrName);
	/**
	 * @brief Get the insight value of specific attribute
	 * @param pNode current xml node
	 * @param attrName attribute's name
	 * @return string type
	 */
	std::string parseStringAttr(rapidxml::xml_node<> *pNode, const std::string& attrName);
	/**
	 * @brief Parse color attributes
	 * @param pNode current xml node
	 * @param attrName attribute's name
	 * @return SVGColor type
	 */
	SVGColor parseColor(rapidxml::xml_node<> *pNode, const std::string& attrName, std::string &gradID);
	/**
	 * @brief Parse set of points attributes
	 * @param pNode current xml node
	 * @param attrName attribute's name
	 * @return vector<Vector2D<float>> set of points
	 */
	std::vector<Vector2D<float>> parsePointsAttr(rapidxml::xml_node<> *pNode, const std::string& attrName);
	/**
	 * @brief Parse transformation and add to vector
	 * @param transformation the transformation attributes
	 * @return vector<string> set of transformations.
	 */
	std::vector<std::string> parseTransformation(std::string transformation);
};

#endif // SVG_RENDERING_XML_PARSER_H_
