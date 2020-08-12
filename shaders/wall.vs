
#version 130

uniform mat4 modelView;
uniform mat4 projection;
in vec4 vPosition;
out vec3 position;

void main() {
	gl_Position = projection * modelView * vPosition;
	position = vPosition.xyz;
}
