#include "Camera.h"

Vector2D<int> Camera::screenSize = {1000, 500};
Vector2D<float> Camera::startPosition = {};
Vector2D<float> Camera::mousePosition = {-1, -1};
float Camera::rotation = 0.0f;
//float Camera::zoom = 10.0f;
float Camera::zoom = 1.0f;
bool Camera::isDragging = false;

void Camera::reset() {
	startPosition = {};
	mousePosition = {-1, -1};
	rotation = 0.0f;
	zoom = 1.0f;
}

void Camera::zoomIn(float amount) {
	zoom += amount;
	if (zoom > 10.0f) {
		zoom = 10.0f;
	}
	if (amount < 0 && zoom <= 0.0f) {
		zoom = -amount;
	}
}

void Camera::zoomOut(float amount) {
	zoomIn(-amount);
}

void Camera::rotateClockWise(float degree) {
	rotation += degree;
	if (rotation > 360.0f) {
		rotation -= 360.0f;
	}
	if (rotation < 0.0f) {
		rotation += 360.0f;
	}
}

void Camera::rotateCounterClockWise(float degree) {
	rotateClockWise(-degree);
}
