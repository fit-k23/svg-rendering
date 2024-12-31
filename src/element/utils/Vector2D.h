#ifndef SVG_RENDERING_VECTOR2D_H
#define SVG_RENDERING_VECTOR2D_H

#include <cassert>
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
	T x, y;
	Vector2D() : x(0), y(0) {}
	/**
	 * @brief parameterized constructor
	 * @param x passed x cord
	 * @param y passed y cord
	 */
	Vector2D(T x, T y) : x(x), y(y) {}
	Vector2D operator*(float scale) { return {x * scale, y * scale}; }
	Vector2D operator/(float scale) {
		assert(scale != 0); // <- avoid divide by zero
		return {x / scale, y / scale};
	}
	Vector2D &operator*=(float scale) {
		x *= scale;
		y *= scale;
		return *this;
	}
	Vector2D &operator/=(float scale) {
		assert(scale != 0);
		x /= scale;
		y /= scale;
		return *this;
	}

	/**
	 * @brief Arithmetic operator + for vector2D class
	 * @param other same-class vector2D
	 * @return new vector2D
	 */
	Vector2D operator+(const Vector2D &other) { return {x + other.x, y + other.y}; }

	/**
	 * @brief Arithmetic operator += for vector2D class
	 * @param other same-class vector2D
	 * @return reference to this
	 */
	Vector2D &operator+=(const Vector2D &other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2D operator+(float amount) { return {x + amount, y + amount}; }
	Vector2D &operator+=(float amount) {
		x += amount;
		y += amount;
		return *this;
	}

	Vector2D operator-(float amount) { return {x - amount, y - amount}; }
	Vector2D &operator-=(float amount) {
		x -= amount;
		y -= amount;
		return *this;
	}

	/**
	 * @brief Arithmetic operator - for vector2D class
	 * @param other same-class vector2D
	 * @return new vector2D
	 */
	Vector2D operator-(const Vector2D &other) { return {x - other.x, y - other.y}; }

	/**
	 * @brief Arithmetic operator -= for vector2D class
	 * @param other same-class vector2D
	 * @return reference to this
	 */
	Vector2D &operator-=(const Vector2D &other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2D operator*(const Vector2D &other) { return {x * other.x, y * other.y}; }
	Vector2D &operator*=(const Vector2D &other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}

	/**
	 * @brief Relational operator == for vector2D class
	 * @param other a same-class object
	 * @return boolean
	 */
	bool operator==(const Vector2D &other) const { return x == other.x && y == other.y; }

	/**
	 * @brief Relational operator != for vector2D class
	 * @param other a same-class object
	 * @return boolean
	 */
	bool operator!=(const Vector2D &other) const { return !(*this == other); }

	/**
	 * @brief Assignment (equal) operator
	 * @note Remember to check self-assignment case
	 */
	Vector2D &operator=(const Vector2D &other) {
		if (this != &other) { // <-- self-assignment case
			x = other.x;
			y = other.y;
		}
		return *this;
	}

	/** @brief Auto-cast the class to Gdiplus::Point */
	operator Gdiplus::Point() { return {static_cast<int>(x), static_cast<int>(y)}; }
	/** @brief Auto-cast the class to Gdiplus::PointF */
	operator Gdiplus::PointF() { return {static_cast<float>(x), static_cast<float>(y)}; }
	/** @brief Auto-cast the class to Gdiplus::Size */
	operator Gdiplus::Size() { return {static_cast<int>(x), static_cast<int>(y)}; }
	/** @brief Auto-cast the class to Gdiplus::SizeF */
	operator Gdiplus::SizeF() { return {static_cast<float>(x), static_cast<float>(y)}; }
	/** @brief Auto-cast the class to POINTS */
	operator POINT() { return {static_cast<LONG>(x), static_cast<LONG>(y)}; }
	operator Vector2D<int>() { return {static_cast<int>(x), static_cast<int>(y)}; }
	operator Vector2D<float>() { return {static_cast<float>(x), static_cast<float>(y)}; }
};


#endif //SVG_RENDERING_VECTOR2D_H
