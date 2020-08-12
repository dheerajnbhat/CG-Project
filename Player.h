#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>


class Player {
	private:
		glm::vec3 pos;
		glm::vec3 forward;
		glm::vec3 up;
		glm::vec3 right;

		glm::vec3 vel;
		float desiredVel;
		glm::vec3 desiredAngle;

		const float MAX_VEL = 300.0f;
		const float TRANSITION_SPEED = 10.0f;

	public:
		const float ROT_SPEED =  3.141592/64;

		Player();
		void setPos(glm::vec3 pos);
		glm::vec3 getPos();
		void setVel(glm::vec3 vel);
		glm::vec3 getVel();
		void setForward(glm::vec3 forward);
		glm::vec3 getForward();
		void setUp(glm::vec3 Up);
		glm::vec3 getUp();
		glm::vec3 getRight();
		glm::vec3 getForwardXZ();
		glm::vec3 getRightXZ();
		void rotateTowards(glm::vec3 v, float angle);
		void rotateRight(float angle);
		void rotateUp(float angle);


		void moveTowards(glm::vec3 dir);
		void step(float dt);
};

#endif
