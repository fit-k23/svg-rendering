#ifndef SVG_RENDERING_VECTOR2D_H
#define SVG_RENDERING_VECTOR2D_H

#include <iostream>
#include <algorithm>
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

	explicit operator Vector2();
};

#endif //SVG_RENDERING_VECTOR2D_H
