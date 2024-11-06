#include "ViewBox.h"

ViewBox::ViewBox() : minX{0.0f}, minY{0.0f}, width{0.0f}, height{0.0f} {}

ViewBox::ViewBox(float _minX, float _minY, float _width, float _height) : minX{_minX}, minY{_minY}, width{_width}, height{_height}  {}

/** @brief Get the minimum X of ViewBox */
float ViewBox::getMinX() const { return minX; }

/** @brief Get the minimum Y of ViewBox */
float ViewBox::getMinY() const { return minY; }

/** @brief Get the width of ViewBox */
float ViewBox::getWidth() const { return width; }

/** @brief Get the height of ViewBox */
float ViewBox::getHeight() const { return height; }
