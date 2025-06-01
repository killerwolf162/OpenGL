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
    vec3 normal = texture(normalTex, uv).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    normal = normalize(TBN * normal);

    // If lightPosition is a direction:
    vec3 lightDir = normalize(-lightPosition);  // Use minus if it's directional light

    // For point light:
    // vec3 lightDir = normalize(lightPosition - worldPosition);

    vec3 viewDir = normalize(cameraPosition - worldPosition);
    vec3 reflDir = reflect(-lightDir, normal);

    float diffuse = max(dot(normal, lightDir), 0.0);

    float specularStrength = 0.6;
    float shininess = 256.0;
    float spec = pow(max(dot(reflDir, viewDir), 0.0), shininess) * specularStrength;

    vec4 texColor = texture(mainTex, uv);
    //vec3 ambient = vec3(0.12, 0.09, 0.07);

    vec3 lighting = (texColor.rgb * diffuse) + spec;

    // Optional gamma correction
    lighting = pow(lighting, vec3(1.0 / 2.2));

    FragColor = vec4(lighting, 1.0);
}