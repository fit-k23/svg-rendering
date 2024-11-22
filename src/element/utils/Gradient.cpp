#include "Gradient.h"

Gradient::Gradient() : id(), transforms({}) {}

Gradient::Gradient(const std::string &_id, const std::vector<std::string>& transforms, const std::string &_units) : id(_id), transforms(transforms), units(_units) {}

void Gradient::dbg() const {
	std::cout << "[DEBUG " << getType() << "Gradient]\n";
	std::cout << "ID = " << id << '\n';
	std::cout << "Transforms: ";
	for (const auto &transform : transforms) std::cout << transform << " ";
	std::cout << '\n';
	std::cout << "Units: " << units << '\n';
	std::cout << "Stops: ";
	for (const auto &stop : stops)
		stop.output();
	std::cout << '\n';
}

void Gradient::setID(const std::string &_id) { id = _id; }
void Gradient::setTransforms(const std::vector<std::string> &_transforms) { transforms = _transforms; }
void Gradient::addTransform(const std::string& transform) { transforms.push_back(transform); }
void Gradient::setStops(const std::vector<Stop> &_stops) { stops = _stops; }
void Gradient::setUnits(const std::string &_units) { units = _units; }
void Gradient::addStop(const Stop &stop) { stops.push_back(stop); }
std::string Gradient::getID() const { return id; }
std::vector<std::string> Gradient::getTransforms() const { return transforms; }
std::vector<Stop> Gradient::getStops() const { return stops; }
std::string Gradient::getUnits() const { return units; }
