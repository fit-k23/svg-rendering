#include "Stop.h"

Stop::Stop() : offset(0.0f), stopColor(SVGColor()) {}

Stop::Stop(float offset, const SVGColor& stopColor) : offset(offset), stopColor(stopColor) {}

Stop::Stop(const Stop& other) : offset(other.offset), stopColor(other.stopColor) {}

void Stop::setOffset(float offset) { this->offset = offset; }

float Stop::getOffset() const { return offset; }

void Stop::setStopColor(const SVGColor& stopColor) { this->stopColor = stopColor; }

SVGColor Stop::getStopColor() const { return stopColor; }
