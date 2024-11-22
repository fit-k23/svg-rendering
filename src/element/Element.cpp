#include "Element.h"

Element::Element() {
	position = Vector2D<float>(0, 0);
	fillColor = SVGColor(0, 0, 0, 0);
	strokeColor = SVGColor(0, 0, 0, 0);
	strokeWidth = 0.0;
	transformation = {};
	fillGradient = nullptr;
	strokeGradient = nullptr;
	parent = nullptr;
}

Element::Element(const Vector2D<float> &_position, const SVGColor &_fillColor, const SVGColor &_strokeColor, float _strokeWidth) {
	position = _position;
	fillColor = _fillColor;
	strokeColor = _strokeColor;
	strokeWidth = _strokeWidth;
	fillGradient = nullptr;
	strokeGradient = nullptr;
}

Element::Element(const Vector2D<float> &_position, const SVGColor &_fillColor, const SVGColor &_strokeColor, float _strokeWidth, const std::vector<std::string> &_transformation) : Element(_position, _fillColor, _strokeColor, _strokeWidth) {
	transformation = _transformation;
	fillGradient = nullptr;
	strokeGradient = nullptr;

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

void Element::setFillGradient(Gradient *grad) {
	this->fillGradient = grad;
}

Gradient *Element::getFillGradient() const {
	return this->fillGradient;
}

void Element::setStrokeGradient(Gradient* grad) {
	this->strokeGradient = grad;
}

Gradient* Element::getStrokeGradient() const {
	return this->strokeGradient;
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
			std::cout << "POLYLINE]\n";
			break;
		case ElementType::Polygon:
			std::cout << "POLYGON]\n";
			break;
		case ElementType::Path:
			std::cout << "PATH]\n";
			break;
		case ElementType::Group:
			std::cout << "GROUP]\n";
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
	std::cout << "Transformation: \n"; 
	for (const auto &trans : transformation)
		std::cout << trans << '\n';
	std::cout << "Fill gradients: \n"; 
	if (fillGradient != nullptr) fillGradient->dbg();
	else std::cout << "null\n";
	std::cout << "Stroke gradients: \n";
	if (strokeGradient != nullptr) strokeGradient->dbg();
	else std::cout << "null\n";
}

std::pair<Vector2D<float>, Vector2D<float>> Element::getBoundingBox() const {
	return {Vector2D<float>(), Vector2D<float>()};
}