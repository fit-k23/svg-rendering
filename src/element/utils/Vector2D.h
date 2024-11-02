#ifndef SVG_RENDERING_VECTOR2D_H
#define SVG_RENDERING_VECTOR2D_H

#include <iostream>
#include <algorithm>

#ifndef RAYLIB_H
#include "../../../lib/raylib/raylib.h"
#endif
#include "../../../lib/raylib/raymath.h"

/**
* @brief Vector2D is a class explicitly presenting a 2d vector 
* @attributes: same-type x and y attributes (public)
**/

template<typename T>
class Vector2D {
public:
	/**
	* @brief Attributes of vector2D class
	* Both has same type T
	**/
	T x;
	T y;
	
	/**
	* @brief default constructor
	* x and y default is 0
	**/
	Vector2D();

	/**
	* @brief parameterized constructor
	* @param _x: passed x cord, _y: passed y cord
	**/
	Vector2D(const T &_x, const T &_y);

	/**
	* @brief copy constructor to copy content (deep copy)
	* @param other: same-class object
	**/
	Vector2D(const Vector2D<T> &other);
	
	/// TODO: Arithmetic (assignment) operators: +, +=, -, -=, * (number), *= (number), / (number), /= (number)
	/*
	* @brief Arithmetic operator + for vector2D class
	* @param other same-class vector2D
	* @return new vector2D
	*/
	Vector2D<T> operator + (const Vector2D<T>& other);
	/*
	* @brief Arithmetic operator += for vector2D class
	* @param other same-class vector2D
	* @return reference to this
	*/
	Vector2D<T>& operator += (const Vector2D<T>& other);
	/*
	* @brief Arithmetic operator - for vector2D class
	* @param other same-class vector2D
	* @return new vector2D
	*/
	Vector2D<T> operator - (const Vector2D<T>& other);
	/*
	* @brief Arithmetic operator -= for vector2D class
	* @param other same-class vector2D
	* @return reference to this
	*/
	Vector2D<T>& operator -= (const Vector2D<T>& other);
	/*
	* @brief Arithmetic operator * for vector2D class
	* @param a number
	* @return new vector
	*/
	Vector2D<T> operator * (const T& other);
	/*
	* @brief Arithmetic operator *= for vector2D class
	* @param a number
	* @return reference to this
	*/
	Vector2D<T>& operator *= (const T& other);
	/*
	* @brief Arithmetic operator / for vector2D class
	* @param a number
	* @return new vector
	*/
	Vector2D<T> operator / (const T& other);
	/*
	* @brief Arithmetic operator /= for vector2D class
	* @param a number
	* @return reference to this
	*/
	Vector2D& operator /= (const T& other);
	
	/// TODO: relational operator: ==, !=
	/*
	* @brief Relational operator == for vector2D class
	* @param other a same-class object
	* @return boolean
	*/
	bool operator == (const Vector2D<T>& other) const;
	/*
	* @brief Relational operator != for vector2D class
	* @param other a same-class object
	* @return boolean
	*/
	bool operator != (const Vector2D<T>& other) const;

	/*
	* @brief Assignment (equal) operator
	* @note Remember to check self-assignment case
	*/
	Vector2D<T>& operator = (const Vector2D<T>& other);

	operator Vector2();
};


/**
* @brief default constructor
* x and y default is 0
**/
template<typename T>
Vector2D<T>::Vector2D() : x(0), y(0) {}

/**
* @brief parameterized constructor
* @param _x: passed x cord, _y: passed y cord
**/
template<typename T>
Vector2D<T>::Vector2D(const T& _x, const T& _y) : x(_x), y(_y) {}

/**
* @brief copy constructor to copy content (deep copy)
* @param other: same-class object
**/
template<typename T>
Vector2D<T>::Vector2D(const Vector2D<T>& other) : x(other.x), y(other.y) {}

/*
* @brief Arithmetic operator + for vector2D class
* @param other same-class vector2D
* @return new vector2D
*/
template<typename T>
Vector2D<T> Vector2D<T>::operator + (const Vector2D<T>& other) {
	return Vector2D<T>(this->x + other.x, this->y + other.y);
}

/*
* @brief Arithmetic operator += for vector2D class
* @param other same-class vector2D
* @return reference to this
*/
template<typename T>
Vector2D<T>& Vector2D<T>::operator += (const Vector2D<T>& other) {
	this->x += other.x;
	this->y += other.y;
	return *this;
}

/*
* @brief Arithmetic operator - for vector2D class
* @param other same-class vector2D
* @return new vector2D
*/
template<typename T>
Vector2D<T> Vector2D<T>::operator - (const Vector2D<T>& other) {
	return Vector2D<T>(this->x - other.x, this->y - other.y);
}

/*
* @brief Arithmetic operator -= for vector2D class
* @param other same-class vector2D
* @return reference to this
*/
template<typename T>
Vector2D<T>& Vector2D<T>::operator -= (const Vector2D<T>& other) {
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

/*
* @brief Arithmetic operator * for vector2D class
* @param other number of type T
* @return new vector2D
*/
template<typename T>
Vector2D<T> Vector2D<T>::operator * (const T& other) {
	return Vector2D<T>(this->x * other, this->y * other);
}

/*
* @brief Arithmetic operator *= for vector2D class
* @param other number of type T
* @return reference to this
*/
template<typename T>
Vector2D<T>& Vector2D<T>::operator *= (const T& other) {
	this->x *= other;
	this->y *= other;
	return *this;
}

/*
* @brief Arithmetic operator / for vector2D class
* @param other number of type T
* @return new vector2D
*/
template<typename T>
Vector2D<T> Vector2D<T>::operator / (const T& other) {
	assert(other != 0); //W/ <- avoid divide by zero
	return Vector2D<T>(this->x / other, this->y / other);
}

/*
* @brief Arithmetic operator /= for vector2D class
* @param other number of type T
* @return reference to this
*/
template<typename T>
Vector2D<T>& Vector2D<T>::operator /= (const T& other) {
	assert(other != 0); /// <- avoid divide by zero
	this->x /= other;
	this->y /= other;
	return *this;
}

/*
* @brief Relational operator ==, != for vector2D class
* @param other a same-class object
* @return boolean
*/
template<typename T>
bool Vector2D<T>::operator == (const Vector2D<T>& other) const {
	return this->x == other.x && this->y == other.y;
}

template<typename T>
bool Vector2D<T>::operator != (const Vector2D<T>& other) const {
	return !(this->x == other.x && this->y == other.y);
}

template<typename T>
Vector2D<T>::operator Vector2() {
	return Vector2{static_cast<float>(this->x), static_cast<float>(this->y)};
}

/*
* @brief Assignment (equal) operator
* @note Remember to check self-assignment case
*/
template<typename T>
Vector2D<T>& Vector2D<T>::operator = (const Vector2D<T>& other) {
	if (this == &other) { // <-- self-assignment case
		return *this;
	}
	this->x = other.x;
	this->y = other.y;
	return *this;
}


#endif //SVG_RENDERING_VECTOR2D_H
