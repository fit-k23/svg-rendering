#ifndef SVG_RENDERING_CAMERA_H
#define SVG_RENDERING_CAMERA_H

#include "../element/utils/Vector2D.h"

class Camera{
public:
	static Vector2D<float> position;
	static float rotation;
	static float zoom;
	static bool isDragging;
	static void zoomIn(float amount = 0.05f);
	static void zoomOut(float amount = 0.05f);
	static void rotateClockWise(float degree = 1.0f);
	static void rotateCounterClockWise(float degree = 1.0f);

};

#endif //SVG_RENDERING_CAMERA_H
