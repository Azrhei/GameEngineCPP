#version 460
// : general vertex shader : vertexShader.glsl
in vec3 position;
in vec2 textureCoords;
in vec3 normals;

out vec2 pass_textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;
out float visibility;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;
uniform float useFakeLighting;

const float density = 0.00;
const float gradient = 0;

void main(void){

	vec4 worldPosition = transformationMatrix * vec4(position,1.0);
	vec4 positionRelativeToCam =viewMatrix * worldPosition;
	gl_Position = projectionMatrix * positionRelativeToCam;
	pass_textureCoords = textureCoords;

	vec3 actualNormal = normals;
	if(useFakeLighting > 0.5) actualNormal = vec3(0.0,1.0,0.0);

	surfaceNormal = (transformationMatrix * vec4(actualNormal,0.0)).xyz;
	toLightVector = lightPosition - worldPosition.xyz;
	toCameraVector = ( inverse(viewMatrix) * vec4(0,0,0,1) ).xyz - worldPosition.xyz;

	float distance = length(positionRelativeToCam.xyz);
	visibility = clamp(exp(-pow((distance*density),gradient)),0.0,1.0);
}