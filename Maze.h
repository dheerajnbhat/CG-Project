#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <GL/glut.h>
#include <glm/glm.hpp>

class Maze {
	private:
		typedef enum cell {FREE, WALL, START, FINISH} Cell;

		int width;
		int height;
		int gridSize;
		Cell** grid;

		void generateRecursive(int x, int y);

	public:
		~Maze();
		int getWidth();
		int getHeight();
		bool isCellWall(int x, int y);
		void generate(int width, int height);
		std::vector<glm::vec4> getVertices(float cellSize);
		std::vector<GLuint> getIndexes();
		void print();
		int getWallCount();
};

#endif
