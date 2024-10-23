#ifndef SVG_RENDERING_ELEMENT_H
#define SVG_RENDERING_ELEMENT_H

#include "Gradient.h"
#include "raylib.h"
#include "utils/ElementType.h"
#include "Vector2D.h"
#include "SVGColor.h"

class Element{
private:
	Element *parent;
	Vector2D position;
	SVGColor fillColor;
	SVGColor strokeColor;
	double stokeWidth;
	Gradient gradient;
	void cleanUp();
public:
	virtual Element();
	const ElementType type = ElementType::Unknown;
	Element *setParent(Element *parent);
	Element *getParent();
	virtual ElementType getTypeName() = 0;
	virtual ~Element() = default;
	Vector2D getPosition();
	ElementType *setPosition(const Vector2D &position);
	ElementType *setPosition(double x, double y);
	ElementType *setFillFolor(const SVGColor &fillColor);
	SVGColor getFillColor();
	ElementType *setStrokeColor(const SVGColor &fillColor);
	SVGColor getStrokeColor();
	ElementType *setStokeWidth(double width);
	double getStokeWidth();
	Gradient getGradient();
	ElementType *setGradient(const Gradient &gradient);
};

#endif //SVG_RENDERING_ELEMENT_H
