#ifndef SVG_RENDERING_CAMERA_H
#define SVG_RENDERING_CAMERA_H

#include "../element/utils/Vector2D.h"

class Camera{
public:
	static Vector2D<int> screenSize;
	static Vector2D<float> startPosition;
	static Vector2D<float> mousePosition;
	static float rotation;
	static float zoom;
	static bool isDragging;
	static bool isPixelMode;
	static bool isPixelModeOverlay;
	/** @brief Camera zoom in (default = 0.05) */
	static void zoomIn(float amount = 0.05f);
	/** @brief Camera zoom out (default = 0.05) */
	static void zoomOut(float amount = 0.05f);
	static void rotateClockWise(float degree = 1.0f);
	static void rotateCounterClockWise(float degree = 1.0f);
	static void reset();
};

#endif //SVG_RENDERING_CAMERA_H
