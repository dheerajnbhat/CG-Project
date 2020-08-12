#define GLM_ENABLE_EXPERIMENTAL
#include "Player.h"
#include <glm/gtx/rotate_vector.hpp>
#include <math.h>
#include <iostream>


Player::Player() {
	pos = glm::vec3(1.5f, 0.5f, 0.5f);
	forward = glm::vec3(0.0f, 0.0f, 1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::normalize(glm::cross(forward, up));

	vel = glm::vec3(0.0f, 0.0f, 0.0f);
	desiredVel = 0.0f;
	desiredAngle = glm::vec3(0.0f, 0.0f, 0.0f);
}


void Player::setPos(glm::vec3 pos) {
	this->pos = pos;
}


glm::vec3 Player::getPos() {
	return pos;
}


void Player::setVel(glm::vec3 vel) {
	this->vel = vel;
}


glm::vec3 Player::getVel() {
	return vel;
}


void Player::setForward(glm::vec3 forward) {
	this->forward = forward;
}


glm::vec3 Player::getForward() {
	return forward;
}


void Player::setUp(glm::vec3 Up) {
	this->up = up;
}


glm::vec3 Player::getUp() {
	return up;
}


glm::vec3 Player::getRight() {
	return glm::normalize(glm::cross(forward, up));
}

// Forward vector projected onto the XZ plane
glm::vec3 Player::getForwardXZ() {
	return glm::vec3(forward.x, 0.0f, forward.z);
}

// Right vector projected onto the XZ plane
glm::vec3 Player::getRightXZ() {
	return glm::vec3(right.x, 0.0f, right.z);
}


void Player::rotateTowards(glm::vec3 v, float angle) {
	glm::vec3 normal = glm::normalize(glm::cross(forward, v));
	forward = glm::rotate(forward, angle, normal);

	// update right and up vectors
	right = glm::normalize(glm::cross(forward, up));
	up = glm::normalize(glm::cross(right, forward));
	forward = glm::normalize(forward);
}

// use rotation matrix around y-axis
void Player::rotateRight(float angle) {
	angle = -angle;
	forward = glm::vec3(cos(angle)*forward.x + sin(angle)*forward.z, forward.y,
		-sin(angle)*forward.x + cos(angle)*forward.z);
	up = glm::vec3(cos(angle)*up.x + sin(angle)*up.z, up.y,
		-sin(angle)*up.x + cos(angle)*up.z);
	right = glm::vec3(cos(angle)*right.x + sin(angle)*right.z, right.y,
		-sin(angle)*right.x + cos(angle)*right.z);
}


void Player::rotateUp(float angle) {
	rotateTowards(up, angle);
}


void Player::moveTowards(glm::vec3 dir) {
	desiredVel = MAX_VEL;

	if(desiredAngle == glm::vec3(0.0f, 0.0f, 0.0f))
		desiredAngle = glm::normalize(dir);
	else
		desiredAngle = glm::normalize(dir) + glm::normalize(desiredAngle);
}


void Player::step(float dt) {
	float dtSeconds = dt/1000.0f;
	float frameTransition = TRANSITION_SPEED * dtSeconds;

	vel = vel*(1-frameTransition) + (desiredVel*desiredAngle)*frameTransition;
	pos += vel*dtSeconds;

	// assume the player wants to stop unless specified
	desiredVel = 0.0f;
	desiredAngle = glm::vec3(0.0f, 0.0f, 0.0f);
}
