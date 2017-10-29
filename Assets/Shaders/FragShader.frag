#version 430 

layout (binding = 0) uniform sampler2D texColour;
layout (binding = 1) uniform sampler2D texNormal;
layout (binding = 2) uniform sampler2D texSpec;
layout (binding = 3) uniform sampler2D texEnv;
layout (binding = 4) uniform sampler2D shadowmap;

layout (location = 0) out vec4 outFrag;

layout (location = 0) in vec3	outNormal;
layout (location = 1) in vec4   vertexPos;
layout (location = 2) in vec4	viewVec;
layout (location = 3) in vec2	outUV;
layout (location = 4) in vec3	outTangent;


struct DirectionalLight
{
	vec3 colour;
	float diffuseIntensity;
	vec3 direction;
} directionalLight;


vec4 CalculateLight(vec4 colour, float diffuseIntensity, vec4 lightDirection, vec4 normal)
{
	vec4 ambient = vec4(0.3, 0.3, 0.3, 1.0);

	float diffuseAngle = max( dot(-lightDirection, normal), 0.0);

	vec4 specularMap = texture(texSpec, outUV);

	vec4 diffuse;
	vec4 specular = vec4(0.0f);

	if(diffuseAngle > 0.0f)
	{
		specular = vec4(1.0f);

		diffuse = colour * diffuseIntensity * diffuseAngle * ambient;

		vec4 reflectAngle = reflect(lightDirection, normal);
		float specularAngle = pow(max(0.0, dot(viewVec, reflectAngle)), 32.0);

		specular = specularMap * specularAngle;
	}

	return (diffuse + specular);
}


vec3 CalculateNormalMap()
{
	vec3 newNormal, calcNormal, tangent, bitangent, bumpMapNormal, bumpOffset;
	
	bumpOffset = vec3(0.5f);

	calcNormal = normalize(outNormal);

	tangent = normalize(outTangent);
	tangent = normalize(tangent - dot(tangent, calcNormal) * calcNormal);

	bitangent = cross(tangent, calcNormal);

	bumpMapNormal = texture(texNormal, outUV).xyz;
	bumpMapNormal = 2 * (bumpMapNormal - bumpOffset);

	mat3 TBNmatrix = mat3(tangent, bitangent, calcNormal);

	newNormal = TBNmatrix * bumpMapNormal;
	newNormal = normalize(newNormal);

	return newNormal;
}


vec4 CalculateDirectionalLight(vec4 normal)
{
	return CalculateLight(vec4(directionalLight.colour, 1.0f),
						 directionalLight.diffuseIntensity,
						 vec4(directionalLight.direction, 0.0f), normal);
}




void main()
{
	//float distance = length(lightVec - outPosition);
	//diffuseAngle = diffuseAngle * (1.0/ (1.0 + (0.25 * distance * distance)));

	vec4 ambient = vec4(0.3, 0.3, 0.3, 1.0);

	vec4 eye = vec4((normalize(viewVec) - vertexPos).xyz, 0.0f);

	vec4 normal = vec4(CalculateNormalMap(), 0.0);
	vec4 light = ambient + CalculateDirectionalLight(normal);

	outFrag = light;

}