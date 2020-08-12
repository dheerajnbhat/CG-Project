#define GLM_ENABLE_EXPERIMENTAL
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

#define PI 3.14159265f

Camera::Camera() {
	pos = glm::vec3(1.5f, 0.5f, 0.5f);
	forward = glm::vec3(0.0f, 0.0f, 1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::normalize(glm::cross(forward, up));
}

glm::mat4 Camera::render() {
	return glm::lookAt(pos, pos+forward, up);
}

// set the camera position
void Camera::setPosition(glm::vec3 pos) {
	this->pos = pos;
}

void Camera::setForward(glm::vec3 forward) {
	this->forward = forward;
}

void Camera::setUp(glm::vec3 up) {
	this->up = up;
}

void Camera::move(glm::vec3 dir) {
	this->setPosition(this->pos + dir);
}

// move the camera UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD
void Camera::move(Dir dir, float distance) {
	switch (dir) {
		case UP:
			move(up * distance);
			break;
		case DOWN:
			move((-up) * distance);
			break;
		case LEFT:
			move((-right) * distance);
			break;
		case RIGHT:
			move(right * distance);
			break;
		case FORWARD:
			move(forward * distance);
			break;
		case BACKWARD:
			move((-forward) * distance);
			break;
		default:
			std::cout << "Available options are: UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARDS.\n";
	}
}


void Camera::rotateTowards(glm::vec3 v, float angle) {
	glm::vec3 normal = glm::normalize(glm::cross(forward, v));
	forward = glm::rotate(forward, angle, normal);

	// update right and up vectors
	right = glm::normalize(glm::cross(forward, up));
	up = glm::normalize(glm::cross(right, forward));
	forward = glm::normalize(forward);
}

// rotate the camera UP, DOWN, LEFT, RIGHT
void Camera::rotateTowards(Dir dir, float angle) {
	switch (dir) {
		case UP:
			rotateTowards(up, angle);
			break;
		case DOWN:
			rotateTowards(-up, angle);
			break;
		case LEFT:
			rotateTowards(-right, angle);
			break;
		case RIGHT:
			rotateTowards(right, angle);
			break;
		case FORWARD:
			std::cout << "Cannot rotate camera towards FORWARD. Available options are: UP, DOWN, LEFT, RIGHT.\n";
			break;
		case BACKWARD:
			std::cout << "Cannot rotate camera towards BACKWARDS. Available options are: UP, DOWN, LEFT, RIGHT.\n";
			break;
		default:
			std::cout << "Available options are: UP, DOWN, LEFT, RIGHT.\n";
	}
}
