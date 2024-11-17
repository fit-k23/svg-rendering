#include "Gradient.h"

Gradient::Gradient() : id(""), transforms({}) {}

Gradient::Gradient(const std::string& id, const std::vector<std::string>& transforms, const std::string& units) : id(id), transforms(transforms), units(units) {}

void Gradient::setID(const std::string& id) { this->id = id; }

std::string Gradient::getID() const { return id; }

void Gradient::setTransforms(const std::vector<std::string>& transforms) { this->transforms = transforms; }

void Gradient::addTransform(const std::string& transform) { transforms.push_back(transform); }

std::vector<std::string> Gradient::getTransforms() const { return transforms; }

void Gradient::setStops(const std::vector<Stop>& stops) { this->stops = stops; }

void Gradient::addStop(const Stop& stop) { stops.push_back(stop); }

std::vector<Stop> Gradient::getStops() const { return stops; }

void Gradient::setUnits(const std::string& units) { this->units = units; }

std::string Gradient::getUnits() const { return units; }
