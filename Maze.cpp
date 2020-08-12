#include "Maze.h"
#include <iostream>


Maze::~Maze() {
	for(int i = 0; i < width; i++)
		delete[] grid[i];
	delete[] grid;
}


int Maze::getWidth() {
	return width;
}


int Maze::getHeight() {
	return height;
}

// check if the cell is within the possible range and is set to wall
bool Maze::isCellWall(int x, int y) {
	return (x >= 0 && x < width && y >= 0 && y < height && grid[x][y] == WALL);
}

// recursively generate the maze
// build from end so that there is only one route to exit
void Maze::generateRecursive(int x, int y) {
	grid[x][y] = FREE;        // free the current spot
	int startDir = rand() % 4; // pick a random direction to move

	// interate through directions in clockwise motion, starting at startDir
	for(int i = 0; i < 4; i++) {
		int dx = 0, dy = 0;

		if((startDir + i) % 4 == 0) dy--; // North
		if((startDir + i) % 4 == 1) dx++; // East
		if((startDir + i) % 4 == 2) dy++; // South
		if((startDir + i) % 4 == 3) dx--; // West

		int x1 = x+dx,  y1 = y+dy;
		int x2 = x1+dx, y2 = y1+dy;

		if(isCellWall(x1, y1) && isCellWall(x2, y2)) {
			grid[x1][y1] = FREE; // free the intermediate block
			generateRecursive(x2, y2); // recursively generate maze
		}
	}
}


void Maze::generate(int width, int height) {
	this->width = width;
	this->height = height;
	gridSize = width*height;

	// create the grid
	grid = new Cell*[width];
	for(int i = 0; i < width; ++i)
		grid[i] = new Cell[height];

	// initialize the grid
	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
			grid[i][j] = WALL;

	generateRecursive(width-2, height-2);

	// remove start, and finish blocks
	grid[width-1][height-2] = FINISH;
	grid[0][1] = START;
}


std::vector<glm::vec4> Maze::getVertices(float cellSize) {
	std::vector<glm::vec4> vertices;
	int gridSizeVert = (width+1)*(height+1);
	vertices.resize(gridSizeVert*2); // each point top and bottom

	for(int i = 0; i < width+1; ++i) {
		for(int j = 0; j < height+1; ++j) {
			vertices[i*(width+1) + j] = glm::vec4((float)i*cellSize, 0.0f, (float)j*cellSize, 1.0f);
			vertices[gridSizeVert + i*(width+1) + j] = glm::vec4((float)i*cellSize, 1.0f*cellSize, (float)j*cellSize, 1.0f);
		}
	}

	return vertices;
}


std::vector<GLuint> Maze::getIndexes() {
	std::vector<GLuint> indices;
	int gridSizeVert = (width+1)*(height+1);

	for(int i = 0; i < width; ++i) {
		for(int j = 0; j < height; ++j) {
			uint NW = j*(width+1)+i, NE = NW+1;
			uint SW = NW + (width+1),  SE = SW+1;

			if(isCellWall(i, j)) {
				// ceiling
				indices.insert(indices.end(), {
					SE+gridSizeVert, NE+gridSizeVert, NW+gridSizeVert,
					SW+gridSizeVert, SE+gridSizeVert, NW+gridSizeVert
				});

				// North
				if(!isCellWall(i, j-1)) {
					indices.insert(indices.end(), {
						NW, NW+gridSizeVert, NE+gridSizeVert,
						NE, NW, NE+gridSizeVert
					});
				}

				// East
				if(!isCellWall(i+1, j)) {
					indices.insert(indices.end(), {
						NE, NE+gridSizeVert, SE+gridSizeVert,
						SE, NE, SE+gridSizeVert
					});
				}

				// South
				if(!isCellWall(i, j+1)) {
					indices.insert(indices.end(), {
						SE, SE+gridSizeVert, SW+gridSizeVert,
						SW, SE, SW+gridSizeVert
					});
				}

				// West
				if(!isCellWall(i-1, j)) {
					indices.insert(indices.end(), {
						SW, SW+gridSizeVert, NW+gridSizeVert,
						NW, SW, NW+gridSizeVert
					});
				}
			}
		}
	}

	return indices;
}

// output the maze grid to the console
void Maze::print() {
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			switch(grid[i][j]) {
				case FREE:
					printf("  ");
					break;
				case WALL:
					printf("::");
					break;
				case START:
					printf("ST");
					break;
				case FINISH:
					printf("FN");
					break;
			}
		} 
		printf("\n");
	}
}

// return the total number of walls in the maze grid
int Maze::getWallCount() {
	int wallCount = 0;
	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
			if(isCellWall(i, j))
				++wallCount;
	return wallCount;
}
