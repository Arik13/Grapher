#version 400 core

in vec4 color;
out vec4 fragmentColour;
void main() {
	//fragmentColour = vec4(1, 1, 1, 1);//= color;
	fragmentColour = color;
};