#include "Element.h"

Element::Element() {
	position = Vector2D<float>(0, 0);
	fillColor = SVGColor(0, 0, 0, 0);
	strokeColor = SVGColor(0, 0, 0, 0);
	strokeWidth = 0.0;
	transformation = {};
	fillGradient = nullptr;
	strokeGradient = nullptr;
}

Element::Element(const Vector2D<float> &_position, const SVGColor &_fillColor, const SVGColor &_strokeColor, float _strokeWidth) {
	position = _position;
	fillColor = _fillColor;
	strokeColor = _strokeColor;
	strokeWidth = _strokeWidth;
	fillGradient = nullptr;
	strokeGradient = nullptr;
}

Element::Element(const Vector2D<float> &_position, const SVGColor &_fillColor, const SVGColor &_strokeColor, float _strokeWidth, const vector<string> &_transformation) : Element(_position, _fillColor, _strokeColor, _strokeWidth) {
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

void Element::addTransformation(const string &s) {
	this->transformation.push_back(s);
}

void Element::setTransformation(const vector<string> &transformations) { this->transformation = transformations; }

vector<string> Element::getTransformation() const {
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
	std::cout << "-= [DEBUG] =-\n";
	std::cout << "Element type: " << ElementTypeHelper::getElementTypeName(getTypeName()) << '\n';
	std::cout << "Position: (" << getPosition().x << ", " << getPosition().y << ")\n";
	std::cout << "Fill color: ";
	getFillColor().output();
	std::cout << '\n';
	std::cout << "Stroke color: ";
	getStrokeColor().output();
	std::cout << '\n';
	std::cout << "Stroke width: " << getStrokeWidth() << '\n';
	std::cout << "Bounding box: ";
	auto [tl, bt] = getBoundingBox();
	std::cout << " + top-left(" << tl.x << ", " << tl.y << ") ";
	std::cout << " + bottom-right(" << bt.x << ", " << bt.y << ")\n";
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

pair<Vector2D<float>, Vector2D<float>> Element::getBoundingBox() const {
	return {Vector2D<float>(), Vector2D<float>()};
}