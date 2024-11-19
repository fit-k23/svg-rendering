#ifndef SVG_RENDERING_STOP_H
#define SVG_RENDERING_STOP_H

#include <algorithm>
#include "SVGColor.h"

/*
* 1) Gradient offset values less than 0 (or less than 0%) are rounded up to 0%. Gradient offset values greater than 1 (or greater than 100%) are rounded 
* down to 100%.
* 2) It is necessary that at least two stops defined to have a gradient effect. If no stops are defined, then painting shall occur as if 'none' were 
* specified as the paint style. If one stop is defined, then paint with the solid color fill using the color defined for that gradient stop.
* 3) Each gradient offset value is required to be equal to or greater than the previous gradient stop's offset value. If a given gradient stop's offset 
* value is not equal to or greater than all previous offset values, then the offset value is adjusted to be equal to the largest of all previous offset
* values.
* 4) If two gradient stops have the same offset value, then the latter gradient stop controls the color value at the overlap point.
*/

class Stop {
private:
	float offset;
	SVGColor stopColor;
public:
	Stop();

	Stop(float offset, const SVGColor& stopColor);

	Stop(const Stop& other);

	void setOffset(float offset);
	
	float getOffset() const;

	void setStopColor(const SVGColor& stopColor);

	SVGColor getStopColor() const;

	void output() const;
};

#endif // SVG_RENDERING_STOP_H