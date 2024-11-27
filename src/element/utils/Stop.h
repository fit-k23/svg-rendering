#ifndef SVG_RENDERING_STOP_H
#define SVG_RENDERING_STOP_H

#include <algorithm>
#include "SVGColor.h"

/**
 * @brief Stop color for gradient
 * @param stopColor the stop color
 * @param offset the offset for stop color .
 * @note Gradient offset values less than 0 (or less than 0%) are rounded up to 0%. Gradient offset values greater than 1 (or greater than 100%) are rounded down to 100%
 * @note It is necessary that at least two stops defined to have a gradient effect. If no stops are defined, then painting shall occur as if 'none' were specified as the paint style. If one stop is defined, then paint with the solid color fill using the color defined for that gradient stop
 * @note Each gradient offset value is required to be equal to or greater than the previous gradient stop's offset value. If a given gradient stop's offset value is not equal to or greater than all previous offset values, then the offset value is adjusted to be equal to the largest of all previous offset
 * @note If two gradient stops have the same offset value, then the latter gradient stop controls the color value at the overlap point
 */
class Stop {
	float offset;
	SVGColor stopColor;
public:
	/** @brief Default constructor. */
	Stop();
	/** @brief Parameterized constructor. */
	Stop(float offset, const SVGColor& stopColor);
	/** @brief Copy constructor */
	Stop(const Stop& other);
	/**
	 * @brief Set the new offset.
	 * @param offset new offset
	*/
	void setOffset(float offset);
	/**
	 * @brief Get the offset
	 * @return float
	 * @note This function doesn't change any attributes.
	*/
	float getOffset() const;
	/**
	 * @brief Set the new stop color.
	 * @param stopColor new stop color
	*/
	void setStopColor(const SVGColor& stopColor);
	/**
	 * @brief Get the stop color
	 * @return SVGColor
	 * @note This function doesn't change any attributes.
	*/
	SVGColor getStopColor() const;
	/**
	 * @brief Print information of Stop.
	 * @note This function doesn't change any attributes
	*/
	void output() const;
};

#endif // SVG_RENDERING_STOP_H
