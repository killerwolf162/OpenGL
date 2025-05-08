#version 410 core

out vec4 FragColor;

in vec3 worldPosition;

uniform vec3 lightDirection;
uniform vec3 cameraPosition;

vec3 lerp3(vec3 a, vec3 b, float t)
{
	return a +(b-a) * t;
	}

void main()
{
	vec3 topColor = vec3(68.0/255.0, 118.0/255.0, 189.0/255.0);
	vec3 botColor = vec3(188.0/255.0, 214.0/255.0, 231.0/255.0);
	vec3 sunColor = vec3(1, 200/255.0, 50/255.0);

	vec3 viewDir = normalize(worldPosition - cameraPosition);
	float sun = max(pow(dot(-viewDir, lightDirection),128), 0.0);

	FragColor = vec4(lerp3(botColor, topColor, abs(viewDir.y)) + sun * sunColor, 1);
} 