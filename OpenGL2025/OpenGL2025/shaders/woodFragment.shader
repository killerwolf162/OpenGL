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

	//specular -> going for wood
	float specularStrength = 0.1;
    float shininess = 16.0;
    float spec = pow(max(dot(reflDir, viewDir), 0.0), shininess) * specularStrength;

	vec4 albedo = vec4(color, 1.0) * texture(mainTex, uv);

	vec3 warmAmbient = vec3(0.1, 0.07, 0.05);  // soft warm ambient tone
	vec3 lighting = (albedo.rgb * lightValue + warmAmbient) + spec;

	FragColor = vec4(lighting, 1.0);;
}