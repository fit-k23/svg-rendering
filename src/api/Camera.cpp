#include "Camera.h"

Vector2D<float> Camera::position = {};
float Camera::rotation = 0.0f;
float Camera::zoom = 1.0f;
bool Camera::isDragging = false;

void Camera::zoomIn(float amount) {
	Camera::zoom += amount;
	if (Camera::zoom > 10.0f) {
		Camera::zoom = 10.0f;
	}
	if (amount < 0 && Camera::zoom <= 0.0f) {
		Camera::zoom = -amount;
	}
}

void Camera::zoomOut(float amount) {
	Camera::zoomIn(-amount);
}

void Camera::rotateClockWise(float degree) {
	Camera::rotation += degree;
	if (Camera::rotation > 360.0f) {
		Camera::rotation -= 360.0f;
	}
	if (Camera::rotation < 0.0f) {
		Camera::rotation += 360.0f;
	}
}

void Camera::rotateCounterClockWise(float degree) {
	Camera::rotateClockWise(-degree);
}
