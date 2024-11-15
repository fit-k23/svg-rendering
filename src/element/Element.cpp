#include "Element.h"

Element::Element() {
	position = Vector2D<float>(0, 0);
	fillColor = SVGColor(0, 0, 0, 0);
	strokeColor = SVGColor(0, 0, 0, 0);
	strokeWidth = 0.0;
	transformation = {};
	gradient = nullptr;
	parent = nullptr;
}

Element::Element(const Vector2D<float> &position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth) {
	this->position = position;
	this->fillColor = fillColor;
	this->strokeColor = strokeColor;
	this->strokeWidth = strokeWidth;
}

Element::Element(const Vector2D<float>& position, const SVGColor& fillColor, const SVGColor& strokeColor, float _strokeWidth, const std::vector<std::string>& transformation) {
	this->position = position;
	this->fillColor = fillColor;
	this->strokeColor = strokeColor;
	this->strokeWidth = _strokeWidth;
	this->transformation = transformation;
}

void Element::setPosition(float x, float y) {
	this->position.x = x;
	this->position.y = y;
}

void Element::setPosition(const Vector2D<float> &_position) {
	this->position.x = _position.x;
	this->position.y = _position.y;
}

Vector2D<float> Element::getPosition() const {
	return position;
}

void Element::setFillColor(const SVGColor &color) {
	this->fillColor = color;
}

SVGColor Element::getFillColor() const {
	return this->fillColor;
}

void Element::setStrokeColor(const SVGColor &color) {
	this->strokeColor = color;
}

SVGColor Element::getStrokeColor() const {
	return this->strokeColor;
}

void Element::setStrokeWidth(float width) {
	this->strokeWidth = width;
}

float Element::getStrokeWidth() const {
	return this->strokeWidth;
}

void Element::addTransformation(const std::string &s) {
	this->transformation.push_back(s);
}

void Element::setTransformation(const std::vector<std::string> &transformations) { this->transformation = transformations; }

std::vector<std::string> Element::getTransformation() const {
	return this->transformation;
}

void Element::setGradient(Gradient *grad) {
	this->gradient = grad;
}

Gradient *Element::getGradient() const {
	return this->gradient;
}

void Element::setParent(Element *_parent) {
	this->parent = _parent;
}

Element *Element::getParent() const {
	return this->parent;
}

void Element::dbg() {
	std::cout << "[DEBUG ";
	switch (getTypeName()) {
		case ElementType::Rectangle:
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
	std::cout << "Fill color: ";
	getFillColor().output();
	std::cout << '\n';
	std::cout << "Stroke color: ";
	getStrokeColor().output();
	std::cout << '\n';
	std::cout << "Stroke width: " << getStrokeWidth() << '\n';
	std::cout << "Bounding box: ";
	std::pair<Vector2D<float>, Vector2D<float>> boundingBox = getBoundingBox();
	std::cout << "top-left(" << boundingBox.first.x << ", " << boundingBox.first.y << ") ";
	std::cout << "bottom-right(" << boundingBox.second.x << ", " << boundingBox.second.y << ")\n";
}

std::pair<Vector2D<float>, Vector2D<float>> Element::getBoundingBox() const {
	return {Vector2D<float>(), Vector2D<float>()};
}