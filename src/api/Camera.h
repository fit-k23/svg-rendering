#ifndef SVG_RENDERING_CAMERA_H
#define SVG_RENDERING_CAMERA_H

#include "../element/utils/Vector2D.h"

class Camera{
public:
	static Vector2D<float> position;
	static float rotation;
	static float zoom;
};

#endif //SVG_RENDERING_CAMERA_H
