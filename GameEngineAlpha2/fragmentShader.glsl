#version 400

in vec2 pass_textureCoords;
in  vec3 surfaceNormal;
in vec3 toLightVector;

out vec4 out_Color;

uniform sampler2D modelTexture;
uniform vec3 lightColor;
uniform unsigned int lightIntensity;


void main(void){
 
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitToLightVector = normalize(toLightVector);

	float nDot1 = dot(unitNormal,  unitToLightVector); 

	float brightness = max(nDot1,0.0);
	vec3 diffuse = brightness * lightColor;

	out_Color = vec4(diffuse,1.0) * texture(modelTexture,pass_textureCoords) * lightIntensity;

}