#ifndef GRADIENT_H
#define GRADIENT_H

#include <iostream>
#include <string>
#include <vector>
#include "Vector2D.h"
#include "Stop.h"

/** @brief Abstract Gradient class for Linear and Radial Gradient to inherit. */
class Gradient{
	std::string id;
	std::vector<std::string> transforms;
	std::vector<Stop> stops;
	std::string units;
public:
	Gradient();
	Gradient(const std::string &id, const std::vector<std::string> &transforms, const std::string &units);
	virtual ~Gradient() = default;
	/**
	 * @brief Get type of gradient
	 * @note This is a pure virtual function and must be implemented by subclasses
	 * @note This function doesn't change any attributes
	*/
	virtual std::string getType() const = 0;
	virtual void dbg() const;
	void setID(const std::string& id);
	std::string getID() const;
	void setTransforms(const std::vector<std::string> &transforms);
	void addTransform(const std::string &transform);
	/**
	 * @brief Get the gradient transformations
	 * @return vector<string>
	 * @note This function doesn't change any attributes.
	*/
	std::vector<std::string> getTransforms() const;

	/** @brief Set new set of stops for gradients */
	void setStops(const std::vector<Stop> &stops);
	void addStop(const Stop &stop);
	std::vector<Stop> getStops() const;
	void setUnits(const std::string &units);

	/**
	 * @brief Get the gradient units
	 * @return string
	 * @note This function doesn't change any attributes.
	*/
	std::string getUnits() const;
};

#endif //GRADIENT_H
