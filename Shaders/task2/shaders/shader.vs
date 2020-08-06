#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec3 myPos = vec3(0.0f, 0.0f, 0.0f);

void main() {
	gl_Position = vec4(
			aPos.x + myPos.x,
			aPos.y + myPos.y,
			aPos.z + myPos.z,
			1.0
			);
}
