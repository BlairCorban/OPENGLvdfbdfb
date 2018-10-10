#version 430 core
//size of output patch & no. of times the TCS will be executed 
layout (vertices = 4) out; 

void main() {
	if (gl_InvocationID == 0) {
		gl_TessLevelInner[0] = 8.0; 
		gl_TessLevelInner[1] = 8.0;

		gl_TessLevelOuter[0] = 4.0; 
		gl_TessLevelOuter[1] = 4.0; 
		gl_TessLevelOuter[2] = 4.0; 
		gl_TessLevelOuter[3] = 4.0;
	} 
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}