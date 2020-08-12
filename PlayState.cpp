#include "PlayState.h"

GLuint program;
glm::mat4 projection;
GLuint objVAO;
int triangles;

Camera camera;
Maze myMaze;
Keyboard keys;

#define CELL_SIZE 100.0f

#define FOV 45.0f
#define NEAR_CLIP 1.0f
#define FAR_CLIP (100.0f*CELL_SIZE)

#define SENSITIVITY 0.9f

int width = 0;
int height = 0;


void PlayState::enter() {
	std::cout << "Player at ST position. Reach FN and Press ESC!\n";
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutSetCursor(GLUT_CURSOR_NONE);

	int vs = buildShader(GL_VERTEX_SHADER,   (char *)"shaders/wall.vs");
	int fs = buildShader(GL_FRAGMENT_SHADER, (char *)"shaders/wall.fs");
	program = buildProgram(vs, fs, 0);
	//dumpProgram(program, (char *)"Template"); // output information on the shader program

	// init Maze
	srand(time(NULL)); // seed random number generator

	myMaze.generate(25, 25);
	myMaze.print();

	// init OpenGL
	GLuint vbuffer;
	GLuint ibuffer;
	GLint vPosition;

	glGenVertexArrays(1, &objVAO);
	glBindVertexArray(objVAO);

	// get the vertices and indices from myMaze
	std::vector<glm::vec4> vecVertices = myMaze.getVertices(CELL_SIZE);
	std::vector<GLuint> vecIndexes = myMaze.getIndexes();

	triangles = vecIndexes.size()/3;

	glGenBuffers(1, &vbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glBufferData(GL_ARRAY_BUFFER, vecVertices.size()*sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vecVertices.size()*sizeof(glm::vec4), &vecVertices[0]);

	glGenBuffers(1, &ibuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vecIndexes.size()*sizeof(GLuint), &vecIndexes[0], GL_STATIC_DRAW);

	glUseProgram(program);
	vPosition = glGetAttribLocation(program, "vPosition");
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);

	// set play position
	player.setPos(glm::vec3(1.5*CELL_SIZE, 0.5f*CELL_SIZE, 0.5f*CELL_SIZE));
}


void PlayState::leave() {

}


void PlayState::update() {
	// update mouse
	int deltaMovex = mouse.getx() - width/2;
	float deltaMovey = mouse.gety() - height/2;
	float mouseMoveRatiox = (float)deltaMovex/width;
	float mouseMoveRatioy = (float)deltaMovey/height;

	player.rotateRight(mouseMoveRatiox*SENSITIVITY);
	player.rotateUp(-mouseMoveRatioy*SENSITIVITY);

	mouse.warp(width/2, height/2);


	// User input for player
	if(keys.isDown('a'))
		player.moveTowards(-player.getRightXZ());
	if(keys.isDown('d'))
		player.moveTowards(player.getRightXZ());
	if(keys.isDown('w'))
		player.moveTowards(player.getForwardXZ());
	if(keys.isDown('s'))
		player.moveTowards(-player.getForwardXZ());
	if(keys.isDown('j'))
		player.rotateRight(-player.ROT_SPEED);
	if(keys.isDown('l'))
		player.rotateRight(player.ROT_SPEED);
	if(keys.isDown('i'))
		player.rotateUp(player.ROT_SPEED);
	if(keys.isDown('k'))
		player.rotateUp(-player.ROT_SPEED);

	// player step
	glm::vec3 pos0 = player.getPos();
	player.step(1000/60);
	glm::vec3 pos = player.getPos();
	glm::vec3 vel = player.getVel();


	// collision
	// x-axis
	float PLAYER_RAD = 5.0f;
	if(myMaze.isCellWall(floor(pos0.z/CELL_SIZE), floor((pos.x + PLAYER_RAD)/CELL_SIZE)) ||
	   myMaze.isCellWall(floor(pos0.z/CELL_SIZE), floor((pos.x - PLAYER_RAD)/CELL_SIZE))) {
		vel.x = 0.0f;
		pos.x = pos0.x;
	}
	if(myMaze.isCellWall(floor((pos.z + PLAYER_RAD)/CELL_SIZE), floor(pos0.x/CELL_SIZE)) ||
	   myMaze.isCellWall(floor((pos.z - PLAYER_RAD)/CELL_SIZE), floor(pos0.x/CELL_SIZE))) {
		vel.z = 0.0f;
		pos.z = pos0.z;
	}
	player.setPos(pos);
	player.setVel(vel);


	// update camera to player position
	camera.setPosition(player.getPos());
	camera.setForward(player.getForward());
	camera.setUp(player.getUp());
}


void PlayState::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);

	// Update view matrix
	glm::mat4 view = camera.render();

	int viewLoc = glGetUniformLocation(program, "modelView");
	glUniformMatrix4fv(viewLoc, 1, 0, glm::value_ptr(view));
	int projLoc = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(projLoc, 1, 0, glm::value_ptr(projection));

	glBindVertexArray(objVAO);
	glDrawElements(GL_TRIANGLES, 3*triangles, GL_UNSIGNED_INT, NULL);

	glutSwapBuffers();
}


void PlayState::changeSize(int w, int h) {
	if (h == 0) h = 1; // Prevent a divide by zero, when window is too short

	width = w;
	height = h;

	float ratio = 1.0 * w / h;
	glViewport(0, 0, w, h);
	projection = glm::perspective(FOV, ratio, NEAR_CLIP, FAR_CLIP);
}


void PlayState::keyboardDown(unsigned char key, int x, int y) {
	// Exit on Esc
	if(key == 27)
	{
		system("kill `ps | grep 'aplay'|awk '{print $1}'`") ;
		glutLeaveMainLoop();
	}
}


void PlayState::keyboardUp(unsigned char key, int x, int y) {

}


void PlayState::mousePress(int button, int state, int x, int y) {

}


void PlayState::mouseMove(int x, int y) {

}
