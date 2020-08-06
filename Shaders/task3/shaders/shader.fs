#version 330 core

in vec4 final_pos;
out vec4 FragColor;
uniform vec4 ourColor;

void main() {
	FragColor = final_pos;
}
