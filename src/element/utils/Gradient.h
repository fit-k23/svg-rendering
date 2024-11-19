#ifndef GRADIENT_H
#define GRADIENT_H

#include <iostream>
#include <string>
#include <vector>
#include "Vector2D.h"
#include "Stop.h"

class Gradient{
private:
	std::string id;
	std::vector<std::string> transforms;
	std::vector<Stop> stops;
	std::string units;
public:
	Gradient(); 

	Gradient(const std::string &id, const std::vector<std::string> &transforms, const std::string &units);

	virtual ~Gradient() = default;

	virtual std::string getType() const = 0;

	virtual void dbg() const;

	void setID(const std::string& id);

	std::string getID() const;

	void setTransforms(const std::vector<std::string>& transforms);

	void addTransform(const std::string& transform);

	std::vector<std::string> getTransforms() const;

	void setStops(const std::vector<Stop>& stops);

	void addStop(const Stop& stop);

	std::vector<Stop> getStops() const;

	void setUnits(const std::string &units);

	std::string getUnits() const;
};

#endif //GRADIENT_H
