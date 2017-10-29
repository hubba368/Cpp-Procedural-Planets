#version 430 

layout (location = 0) uniform mat4 modelview;		//view matrix
layout (location = 1) uniform mat4 projection;		//projection matrix
layout (location = 2) uniform mat4 modeltransform; 	//model transformation matrix
layout (location = 3) uniform vec3 cameraPos;

layout (location = 0) in vec4 position;				//vertex attribute: position
layout (location = 1) in vec4 inNormal;				//vertex attribute: normal
layout (location = 2) in vec2 inUV;					//vertex attribute: tex coords
layout (location = 3) in vec3 inTangent;

out vec4 outNormal;
out vec4 vertexPos;
out vec4 viewVec;
out vec2 outUV;


void main()
{
	mat4 normalMatrix = transpose(inverse(modeltransform));

	//mvp matrix
	gl_Position = projection * modelview * modeltransform * position;

	outUV = inUV;

	outNormal = normalMatrix * position;

	vertexPos = modeltransform * position;

	vec3 viewDirection = normalize(cameraPos - vertexPos.xyz);
	viewVec = vec4(viewDirection, 0.0f);
	viewVec = normalize(viewVec);

}