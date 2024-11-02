#include "Vector2D.h"

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
	return Vector2{this->x, this->y};
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
