#version 430 

layout (location = 0) uniform mat4 modelview;		//view matrix
layout (location = 1) uniform mat4 projection;		//projection matrix
layout (location = 2) uniform mat4 modeltransform; 	//model transformation matrix

layout (location = 0) in vec4 position;				//vertex attribute: position
uniform mat4 transform;

void main()
{
	gl_Position = projection * modelview * modeltransform * position;
}