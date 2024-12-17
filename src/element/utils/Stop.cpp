#include "Stop.h"

Stop::Stop() : offset(0.0f), stopColor() {}
Stop::Stop(float offset, const SVGColor &stopColor) : offset(offset), stopColor(stopColor) {}

void Stop::setOffset(float _offset) { offset = _offset; }
void Stop::setStopColor(const SVGColor &_stopColor) { stopColor = _stopColor; }
float Stop::getOffset() const { return offset; }
SVGColor Stop::getStopColor() const { return stopColor; }

void Stop::output() const {
	std::cout << "Offset: " << offset << '\n';
	std::cout << "Stop-color: "; 
	stopColor.output();
	std::cout << '\n';
}
