#version 420 core

in vec3 outColor;
in vec4 outPos;
in vec4 worldPos;


out vec4 a_color;

uniform float currentTime;
uniform int gStencil;
uniform vec3 gCameraPos;
uniform vec3 gStencilColor;
uniform float gTime;

void main(void)
{
	float d = distance(worldPos.xyz, gCameraPos);
	float lerp = (d - 5.0f)/10.0f;
	lerp = clamp(lerp, 0.0f, 1.0f);
	vec4 vFogColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	a_color = (gStencil == 0) ? vec4(outColor, 1) : vec4(gStencilColor, 1);
	//a_color = mix(a_color, vFogColor, lerp);
	

}