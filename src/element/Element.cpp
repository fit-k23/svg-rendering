#include "Element.h"

/*
* @brief Default constructor
*/
Element::Element() {
	position = Vector2D<float>(0, 0);
	fillColor = SVGColor(0, 0, 0, 0);
	strokeColor = SVGColor(0, 0, 0, 0);
	strokeWidth = 0.0;
	transformation = {};
	gradient = nullptr;
	parent = nullptr;
}

/*
* @brief Parameterized constructor
* @note: easier for subclass to inherit and write its constructor
*/
Element::Element(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor& strokeColor, float strokeWidth) {
	this->position = position;
	this->fillColor = fillColor;
	this->strokeColor = strokeColor;
	this->strokeWidth = strokeWidth;
}

/*
* @brief set position of a svg element
* @param x and y coordinates (float)
*/
void Element::setPosition(float x, float y) {
	this->position.x = x;
	this->position.y = y;
}

/*
* @brief set position of a svg element
* @param a passed-by-referenced vector2D object
*/
void Element::setPosition(const Vector2D<float> &_position) {
	this->position.x = _position.x;
	this->position.y = _position.y;
}

/*
* @brief get position of a svg element
* @return a vector2D
*/
Vector2D<float> Element::getPosition() const {
	return position;
}

/*
* @brief set fill color of a svg element
* @param a passed-by-referenced SVGColor object
*/
void Element::setFillColor(const SVGColor &color) {
	this->fillColor = color;
}

/*
* @brief get fill color of a svg element
* @return an SVGColor object
*/
SVGColor Element::getFillColor() const {
	return this->fillColor;
}

/*
* @brief set stroke color of a svg element
* @param a passed-by-referenced SVGColor object
*/
void Element::setStrokeColor(const SVGColor& color) {
	this->strokeColor = color;
}

/*
* @brief get stroke color of an svg element
* @return a SVGColor object
*/
SVGColor Element::getStrokeColor() const {
	return this->strokeColor;
}

/*
* @brief set stroke width of a svg element
* @param a float variable
*/
void Element::setStrokeWidth(float width) {
	this->strokeWidth = width;
}

/*
* @brief get stroke width of an svg element
* @return float
*/
float Element::getStrokeWidth() const {
	return this->strokeWidth;
}

void Element::addTransformation(const std::string &s) {
	this->transformation.push_back(s);
}

std::vector<std::string> Element::getTransformation() const {
    return this->transformation;
}

/*
* @brief set gradient of a svg element
* @param a pointer to an abstract Gradient object
*/
void Element::setGradient(Gradient* grad) {
	this->gradient = grad;
}

/*
* @brief get gradient of an svg element
* @param a pointer to a Gradient object
*/
Gradient* Element::getGradient() const {
	return this->gradient;
}

/*
* @brief set parent node of an svg element
* @param a pointer to a same-class object (parent)
*/
void Element::setParent(Element *_parent) {
	this->parent = _parent;
}

/*
* @brief get parent node of an svg element
* @return a pointer to a same-class object (parent)
*/
Element* Element::getParent() const {
	return this->parent;
}

void Element::dbg() {
	std::cout << "[DEBUG ";
	switch (getTypeName()) {
		case ElementType::Rect:
			std::cout << "RECT]\n";
			break;
		case ElementType::Ellipse:
			std::cout << "ELLIPSE]\n";
			break;
		case ElementType::Circle:
			std::cout << "CIRCLE]\n";
			break;
		case ElementType::Line:
			std::cout << "LINE]\n";
			break;
		case ElementType::Text:
			std::cout << "TEXT]\n";
			break;
		case ElementType::Polyline:
			std::cout << "Polyline]\n";
			break;
		case ElementType::Polygon:
			std::cout << "POLYGON]\n";
			break;
		case ElementType::Path:
			std::cout << "PATH]\n";
			break;
		default:
			break;
	}
	std::cout << "Position: (" << getPosition().x << ", " << getPosition().y << ")\n";
	std::cout << "Fill color: "; getFillColor().output(); std::cout << '\n';
	std::cout << "Stroke color: "; getStrokeColor().output(); std::cout << '\n';
	std::cout << "Stroke width: " << getStrokeWidth() << '\n';
	std::cout << "Bounding box: "; 
	std::pair<Vector2D<float>, Vector2D<float>> boundingBox = getBoundingBox();
	std::cout << "top-left(" << boundingBox.first.x << ", " << boundingBox.first.y << ") ";
	std::cout << "bottom-right(" << boundingBox.second.x << ", " << boundingBox.second.y << ")\n";
}

std::pair<Vector2D<float>, Vector2D<float>> Element::getBoundingBox() const {
	return { Vector2D<float>(),Vector2D<float>() };
}