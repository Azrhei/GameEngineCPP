#version 460 core
// : primary fragment shader fragmentShader.glsl

in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;
in float visibility;

out vec4 out_Color;

uniform sampler2D modelTexture;
uniform vec3 lightColor;
uniform float shineDamper;
uniform float reflectivity;
uniform vec3 skyColor;

void main(void){
 
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitToLightVector = normalize(toLightVector);

	float nDot1 = dot(unitNormal,  unitToLightVector); 

	float brightness = max(nDot1,0.3);
	vec3 diffuse = brightness * lightColor;

	vec3 unitToCameraVector = normalize(toCameraVector);
	vec3 lightDirection = -unitToLightVector;
	vec3 reflectedLightDirection = reflect(lightDirection,unitNormal);

	float specularFactor = max(dot(reflectedLightDirection,unitToCameraVector),0);
	float dampedFactor = pow(specularFactor,shineDamper);

	vec3 finalSpecular = dampedFactor * reflectivity * lightColor;

	vec4 textureColor = texture(modelTexture,pass_textureCoords);

	if(textureColor.a < 0.5) discard;

	out_Color = vec4(diffuse,1.0) * textureColor + vec4(finalSpecular,1.0);
	out_Color = mix(vec4(skyColor,1.0), out_Color, visibility);
}