#ifndef SVG_RENDERING_VECTOR2D_H
#define SVG_RENDERING_VECTOR2D_H

#include <objidl.h>
#include <gdiplus.h>

/**
 * @brief Vector2D is a class explicitly presenting a 2D vector
 * @param x the x coordinate of vector
 * @param y the y coordinate of vector
 * @note This is a template class
 */

template<typename T>
struct Vector2D{
	/**
	 * @brief Attributes of vector2D class
	 * @note Both has same type T
	 */
	T x;
	T y;

	Vector2D();

	/**
	 * @brief parameterized constructor
	 * @param x passed x cord
	 * @param y passed y cord
	 */
	Vector2D(T x, T y);

	/**
	 * @brief copy constructor to copy content (deep copy)
	 * @param other: same-class object
	 */
	Vector2D(const Vector2D &other);

	// TODO: Arithmetic (assignment) operators: +, +=, -, -=, * (number), *= (number), / (number), /= (number)
	/**
	 * @brief Arithmetic operator + for vector2D class
	 * @param other same-class vector2D
	 * @return new vector2D
	 */
	Vector2D operator+(const Vector2D &other);

	/**
	 * @brief Arithmetic operator += for vector2D class
	 * @param other same-class vector2D
	 * @return reference to this
	 */
	Vector2D &operator+=(const Vector2D &other);

	/**
	 * @brief Arithmetic operator - for vector2D class
	 * @param other same-class vector2D
	 * @return new vector2D
	 */
	Vector2D operator-(const Vector2D &other);

	/**
	 * @brief Arithmetic operator -= for vector2D class
	 * @param other same-class vector2D
	 * @return reference to this
	 */
	Vector2D &operator-=(const Vector2D &other);

	/**
	 * @brief Arithmetic operator * for vector2D class
	 * @return new vector
	 */
	Vector2D operator*(const T &other);

	/**
	 * @brief Arithmetic operator *= for vector2D class
	 * @return reference to this
	 */
	Vector2D &operator*=(const T &other);

	/**
	 * @brief Arithmetic operator / for vector2D class
	 * @return new vector
	 */
	Vector2D operator/(const T &other);

	/**
	 * @brief Arithmetic operator /= for vector2D class
	 * @return reference to this
	 */
	Vector2D &operator/=(const T &other);

	// TODO: relational operator: ==, !=
	/**
	 * @brief Relational operator == for vector2D class
	 * @param other a same-class object
	 * @return boolean
	 */
	bool operator==(const Vector2D &other) const;

	/**
	 * @brief Relational operator != for vector2D class
	 * @param other a same-class object
	 * @return boolean
	 */
	bool operator!=(const Vector2D &other) const;

	/**
	 * @brief Assignment (equal) operator
	 * @note Remember to check self-assignment case
	 */
	Vector2D &operator=(const Vector2D &other);

	/** @brief Auto-cast the class to Gdiplus::Point */
	operator Gdiplus::Point();
	/** @brief Auto-cast the class to Gdiplus::PointF */
	operator Gdiplus::PointF();
	/** @brief Auto-cast the class to Gdiplus::Size */
	operator Gdiplus::Size();
	/** @brief Auto-cast the class to Gdiplus::SizeF */
	operator Gdiplus::SizeF();
	/** @brief Auto-cast the class to POINTS */
	operator POINT();
	operator Vector2D<int>();
	operator Vector2D<float>();
};

template<typename T>
Vector2D<T>::Vector2D() : x(0), y(0) {}

template<typename T>
Vector2D<T>::Vector2D(T x, T y) : x(x), y(y) {}

template<typename T>
Vector2D<T>::Vector2D(const Vector2D &other) : x(other.x), y(other.y) {}

template<typename T>
Vector2D<T> Vector2D<T>::operator+(const Vector2D &other) {
	return Vector2D(x + other.x, y + other.y);
}

template<typename T>
Vector2D<T> &Vector2D<T>::operator+=(const Vector2D &other) {
	x += other.x;
	y += other.y;
	return *this;
}

template<typename T>
Vector2D<T> Vector2D<T>::operator-(const Vector2D &other) {
	return Vector2D(x - other.x, y - other.y);
}

template<typename T>
Vector2D<T> &Vector2D<T>::operator-=(const Vector2D &other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

template<typename T>
Vector2D<T> Vector2D<T>::operator*(const T &other) {
	return Vector2D(x * other, y * other);
}

template<typename T>
Vector2D<T> &Vector2D<T>::operator*=(const T &other) {
	x *= other;
	y *= other;
	return *this;
}

template<typename T>
Vector2D<T> Vector2D<T>::operator/(const T &other) {
	assert(other != 0); // <- avoid divide by zero
	return Vector2D<T>(x / other, y / other);
}

template<typename T>
Vector2D<T> &Vector2D<T>::operator/=(const T &other) {
	assert(other != 0); // <- avoid divide by zero
	x /= other;
	y /= other;
	return *this;
}

template<typename T>
bool Vector2D<T>::operator==(const Vector2D &other) const {
	return x == other.x && y == other.y;
}

template<typename T>
bool Vector2D<T>::operator!=(const Vector2D &other) const {
	return !(x == other.x && y == other.y);
}

template<typename T>
Vector2D<T>::operator POINT() {
	return POINT{static_cast<LONG>(x), static_cast<LONG>(y)};
}

template<typename T>
Vector2D<T>::operator Gdiplus::Point() {
	return Gdiplus::Point{static_cast<int>(x), static_cast<LONG>(y)};
}

template<typename T>
Vector2D<T>::operator Gdiplus::PointF() {
	return Gdiplus::PointF{static_cast<float>(x), static_cast<float>(y)};
}

template<typename T>
Vector2D<T>::operator Gdiplus::Size() {
	return Gdiplus::Size{static_cast<int>(x), static_cast<LONG>(y)};
}

template<typename T>
Vector2D<T>::operator Gdiplus::SizeF() {
	return Gdiplus::SizeF{static_cast<float>(x), static_cast<float>(y)};
}

template<typename T>
Vector2D<T>::operator Vector2D<int>() {
	return Vector2D{static_cast<int>(x), static_cast<int>(y)};
}

template<typename T>
Vector2D<T>::operator Vector2D<float>() {
	return Vector2D{static_cast<float>(x), static_cast<float>(y)};
}

template<typename T>
Vector2D<T> &Vector2D<T>::operator=(const Vector2D &other) {
	if (this == &other) { // <-- self-assignment case
		return *this;
	}
	x = other.x;
	y = other.y;
	return *this;
}


#endif //SVG_RENDERING_VECTOR2D_H
