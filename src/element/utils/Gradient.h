#ifndef GRADIENT_H
#define GRADIENT_H

#include <iostream>
#include <string>
#include <vector>
#include "Vector2D.h"
#include "Stop.h"

/**
 * @brief Abstract Gradient class for Linear and Radial Gradient to inherit.
 */
class Gradient{
private:
	std::string id;
	std::vector<std::string> transforms;
	std::vector<Stop> stops;
	std::string units;
public:
	/**
	 * @brief Default constructor.
	 */
	Gradient(); 

	/**
	 * @brief Parameterized constructor
	 */
	Gradient(const std::string &id, const std::vector<std::string> &transforms, const std::string &units);

	/**
	 * @brief Virtual destructor for properly delete subclasses.
	 */
	virtual ~Gradient() = default;

	/**
	 * @brief Get type of gradient
	 * @note This is a pure virtual function and must be implemented by subclasses
	 * @note This function doesn't change any attributes
	 */
	virtual std::string getType() const = 0;

	/**
	 * @brief Print information of Gradient .
	 * @note This function doesn't change any attributes
	 */
	virtual void dbg() const;

	/**
	 * @brief Set new id for gradient
	 * @param id new id
	 */
	void setID(const std::string& id);

	/**
	 * @brief Get the id of gradient
	 * @return string
	 * @note This function doesn't change any attributes.
	 */
	std::string getID() const;

	/**
	 * @brief Set new transformations for gradient
	 * @param transforms new transformations
	 */
	void setTransforms(const std::vector<std::string>& transforms);

	/**
	 * @brief Add new transformation
	 * @param transform new transformation.
	 */
	void addTransform(const std::string& transform);

	/**
	 * @brief Get the gradient transformations
	 * @return vector<string>
	 * @note This function doesn't change any attributes.
	 */
	std::vector<std::string> getTransforms() const;

	/**
	 * @brief Set new set of stops for gradient
	 * @param stops new set of stops
	 */
	void setStops(const std::vector<Stop>& stops);

	/**
	 * @brief Add new stop
	 * @param stop new stop
	 */
	void addStop(const Stop& stop);

	/**
	 * @brief Get the set of stops of gradient
	 * @return vector<Stop>
	 * @note This function doesn't change any attributes.
	 */
	std::vector<Stop> getStops() const;

	/**
	 * @brief Set new gradient units
	 * @param units new gradient units
	 */
	void setUnits(const std::string &units);

	/**
	 * @brief Get the gradient units
	 * @return string
	 * @note This function doesn't change any attributes.
	 */
	std::string getUnits() const;
};

#endif //GRADIENT_H
