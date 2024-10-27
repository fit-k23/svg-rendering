#ifndef SVG_RENDERING_VECTOR2D_H
#define SVG_RENDERING_VECTOR2D_H

#include <iostream>
#include <algorithm>

/**
* @cmt: Vector2D is a class explicitly presenting a 2d vector 
* @is_abstract: no
* @inherits: no
* @attributes: same-type x and y attributes
**/

template<typename T>
class Vector2D {
public:
	/**
	* @cmt: Attributes of vector2D class
	* Both has same type T
	**/
	T x;
	T y;
	
	/**
	* @cmt: default constructor
	* x and y default is 0
	**/
	Vector2D();

	/**
	* @cmt: parameterized constructor
	* @param: _x: passed x cord, _y: passed y coord
	**/
	Vector2D(const T& _x, const T& _y);	

	/**
	* @cmt: copy constructor to copy content (deep copy)
	* @param: other: same-class object
	**/
	Vector2D(const Vector2D<T>& other);
	
	// TODO: arithmetic operator: +, +=, -, -=, *(number), *= (number), /(number), /=(number)
	/*
	* @cmt: Arithmetic operator + for vector2D class
	* @param: other same-class vector2D
	* @return: new vector2D
	*/
	Vector2D<T> operator + (const Vector2D<T>& other);
	/*
	* @cmt: Arithmetic operator += for vector2D class
	* @param: other same-class vector2D
	* @return: reference to this
	*/
	Vector2D<T>& operator += (const Vector2D<T>& other);
	/*
	* @cmt: Arithmetic operator - for vector2D class
	* @param: other same-class vector2D
	* @return: new vector2D
	*/
	Vector2D<T> operator - (const Vector2D<T>& other);
	/*
	* @cmt: Arithmetic operator -= for vector2D class
	* @param: other same-class vector2D
	* @return: reference to this
	*/
	Vector2D<T>& operator -= (const Vector2D<T>& other);
	/*
	* @cmt: Arithmetic operator * for vector2D class
	* @param: a number
	* @return: new vector
	*/
	Vector2D<T> operator * (const T& other);
	/*
	* @cmt: Arithmetic operator *= for vector2D class
	* @param: a number
	* @return: reference to this
	*/
	Vector2D<T>& operator *= (const T& other);
	/*
	* @cmt: Arithmetic operator / for vector2D class
	* @param: a number
	* @return: new vector
	*/
	Vector2D<T> operator / (const T& other);
	/*
	* @cmt: Arithmetic operator /= for vector2D class
	* @param: a number
	* @return: reference to this
	*/
	Vector2D& operator /= (const T& other);
	// TODO: relational operator: ==, !=
	/*
	* @cmt: Relational operator == for vector2D class
	* @param: other a same-class object
	* @return: boolean
	*/
	bool operator == (const Vector2D& other) const;
	/*
	* @cmt: Relational operator != for vector2D class
	* @param: other a same-class object
	* @return: boolean
	*/
	bool operator != (const Vector2D& other) const;
};

/**
* @cmt: default constructor
* x and y default is 0
**/
template<typename T>
Vector2D<T>::Vector2D() : x(0), y(0) {}

/**
* @cmt: parameterized constructor
* @param: _x: passed x cord, _y: passed y cord
**/
template<typename T>
Vector2D<T>::Vector2D(const T& _x, const T& _y) : x(_x), y(_y) {}

/**
* @cmt: copy constructor to copy content (deep copy)
* @param: other: same-class object
**/
template<typename T>
Vector2D<T>::Vector2D(const Vector2D<T>& other) : x(other.x), y(other.y) {}

/*
* @cmt: Arithmetic operator + for vector2D class
* @param: other same-class vector2D
* @return: new vector2D
*/
template<typename T>
Vector2D<T> Vector2D<T>::operator + (const Vector2D<T>& other) {
	return Vector2D<T>(this->x + other.x, this->y + other.y);
}

/*
* @cmt: Arithmetic operator += for vector2D class
* @param: other same-class vector2D
* @return: reference to this
*/
template<typename T>
Vector2D<T>& Vector2D<T>::operator += (const Vector2D<T>& other) {
	this->x += other.x;
	this->y += other.y;
	return *this;
}

/*
* @cmt: Arithmetic operator - for vector2D class
* @param: other same-class vector2D
* @return: new vector2D
*/
template<typename T>
Vector2D<T> Vector2D<T>::operator - (const Vector2D<T>& other) {
	return Vector2D<T>(this->x - other.x, this->y - other.y);
}

/*
* @cmt: Arithmetic operator -= for vector2D class
* @param: other same-class vector2D
* @return: reference to this
*/
template<typename T>
Vector2D<T>& Vector2D<T>::operator -= (const Vector2D<T>& other) {
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

/*
* @cmt: Arithmetic operator * for vector2D class
* @param: other number of type T
* @return: new vector2D
*/
template<typename T>
Vector2D<T> Vector2D<T>::operator * (const T& other) {
	return Vector2D<T>(this->x * other, this->y * other);
}

/*
* @cmt: Arithmetic operator *= for vector2D class
* @param: other number of type T
* @return: reference to this
*/
template<typename T>
Vector2D<T>& Vector2D<T>::operator *= (const T& other) {
	this->x *= other;
	this->y *= other;
	return *this;
}

/*
* @cmt: Arithmetic operator / for vector2D class
* @param: other number of type T
* @return: new vector2D
*/
template<typename T>
Vector2D<T> Vector2D<T>::operator / (const T& other) {
	assert(other != 0); /// <- avoid divide by zero
	return Vector2D<T>(this->x / other, this->y / other);
}

/*
* @cmt: Arithmetic operator /= for vector2D class
* @param: other number of type T
* @return: reference to this
*/
template<typename T>
Vector2D<T>& Vector2D<T>::operator /= (const T& other) {
	assert(other != 0); /// <- avoid divide by zero
	this->x /= other;
	this->y /= other;
	return *this;
}

/*
* @cmt: Relational operator > for vector2D class
* @param: other a same-class object
* @return: boolean
*/
template<typename T>
bool Vector2D<T>::operator == (const Vector2D<T>& other) const {
	return this->x == other.x && this->y == other.y;
}

template<typename T>
bool Vector2D<T>::operator != (const Vector2D<T>& other) const {
	return !(this->x == other.x && this->y == other.y);
}

#endif //SVG_RENDERING_VECTOR2D_H
