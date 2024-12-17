#ifndef SVG_RENDERING_GRADIENT_H
#define SVG_RENDERING_GRADIENT_H

#include <iostream>
#include <string>
#include <vector>

#include "Stop.h"
#include "Vector2D.h"

using std::string;
using std::vector;

enum class GradientType{
	Linear = 0,
	Radial,
};

namespace GradientTypeHelper {
	static string getGradientTypeName(GradientType type) {
		if (type == GradientType::Radial) {
			return "radial";
		}
		return "linear";
	}

	static GradientType getGradientTypeFromString(const string& type) {
		if (type == "radial") {
			return GradientType::Radial;
		}
		return GradientType::Linear;
	}
}

/** @brief Abstract Gradient class for Linear and Radial Gradient to inherit. */
class Gradient{
	string id;
	vector<string> transforms;
	vector<Stop> stops;
	string units;
public:
	Gradient();
	Gradient(const string &id, const vector<string> &transforms, const string &units);
	virtual ~Gradient() = default;
	/**
	 * @brief Get type of gradient
	 * @note This is a pure virtual function and must be implemented by subclasses
	 * @note This function doesn't change any attributes
	 */
	virtual GradientType getType() const = 0;
	virtual void dbg() const;
	void setID(const string &id);
	string getID() const;
	void setTransforms(const vector<string> &transforms);
	void addTransform(const string &transform);
	/**
	 * @brief Get the gradient transformations
	 * @return vector<string>
	 * @note This function doesn't change any attributes.
	 */
	vector<string> getTransforms() const;

	/** @brief Set new set of stops for gradients */
	void setStops(const vector<Stop> &stops);
	void addStop(const Stop &stop);
	vector<Stop> getStops() const;
	void setUnits(const string &units);

	/**
	 * @brief Get the gradient units
	 * @return string
	 * @note This function doesn't change any attributes.
	 */
	string getUnits() const;
};

#endif
