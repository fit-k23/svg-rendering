#include "Gradient.h"

Gradient::Gradient() : transforms({}) {}
Gradient::Gradient(const string &_id, const vector<string> &_transforms, const string &_units) : id(_id), transforms(_transforms), units(_units) {}

void Gradient::dbg() const {
	std::cout << "[DEBUG GRADIENT]\n";
	std::cout << "Type: " << GradientTypeHelper::getGradientTypeName(getType()) << "\n";
	std::cout << "ID = " << id << '\n';
	std::cout << "Transforms: ";
	for (const auto &transform : transforms)
		std::cout << transform << " ";
	std::cout << '\n';
	std::cout << "Units: " << units << '\n';
	std::cout << "Stops: \n";
	for (const auto &stop : stops)
		stop.output();
	std::cout << '\n';
}

void Gradient::setID(const string &_id) { id = _id; }
void Gradient::setTransforms(const vector<string> &_transforms) { transforms = _transforms; }
void Gradient::addTransform(const string &transform) { transforms.push_back(transform); }
void Gradient::setStops(const vector<Stop> &_stops) { stops = _stops; }
void Gradient::setUnits(const string &_units) { units = _units; }
void Gradient::addStop(const Stop &stop) { stops.push_back(stop); }
string Gradient::getID() const { return id; }
vector<string> Gradient::getTransforms() const { return transforms; }
vector<Stop> Gradient::getStops() const { return stops; }
int Gradient::getStopsSize() const { return stops.size(); }
string Gradient::getUnits() const { return units; }
