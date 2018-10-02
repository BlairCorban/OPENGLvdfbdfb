#version 420 core

in vec3 a_position;
in vec3 a_color;

out vec3 outColor;
out vec4 outPos;

uniform mat4 gScale;
uniform mat4 gRotate;
uniform mat4 gTranslate;
uniform mat4 gView;
uniform mat4 gPerspective;


void main(void)
{
	gl_Position = gPerspective * gView * gTranslate * gRotate * gScale * vec4(a_position, 1.0);

	outColor = a_color;
	outPos = gl_Position;
}