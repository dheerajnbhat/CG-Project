#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>
#include <glm/glm.hpp>

class Camera {
	private:
		glm::vec3 pos;
		glm::vec3 forward;
		glm::vec3 up;
		glm::vec3 right;
	public:
		enum Dir {UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD};

		Camera();
		glm::mat4 render();
		void setPosition(glm::vec3 pos);
		void setForward(glm::vec3 forward);
		void setUp(glm::vec3 up);
		void move(glm::vec3 dir);
		void move(Dir dir, float distance);

		void rotateTowards(glm::vec3 v, float angle);
		void rotateTowards(Dir dir, float angle);
};

#endif
