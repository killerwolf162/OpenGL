#version 410 core

out vec4 FragColor;

in vec3 color;
in vec2 uv;
in mat3 TBN;
in vec3 worldPosition;

uniform sampler2D mainTex;
uniform sampler2D normalTex;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;

void main()
{
	// Normal Map

	vec3 normal = texture(normalTex, uv).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	normal = TBN * normal;

	// Specular data
	vec3 lightDir = normalize(lightPosition - worldPosition);
	vec3 viewDir = normalize(cameraPosition - worldPosition);
	vec3 reflDir = reflect(-lightDir, normal);

	// lighting
	float lightValue = max(dot(normal, lightDir), 0.0);
	
	//specular -> going for metal
	float specularStrength = 1;
    float shininess = 1024.0;
    float spec = pow(max(dot(reflDir, viewDir), 0.0), shininess) * specularStrength;

	// Texture and color
	vec4 albedo = vec4(color, 1.0) * texture(mainTex, uv);

	vec3 coldAmbient = vec3(0.05, 0.08, 0.15);
	vec3 lighting = (albedo.rgb * lightValue + coldAmbient) + spec;

	FragColor = vec4(lighting, 1.0);;
}