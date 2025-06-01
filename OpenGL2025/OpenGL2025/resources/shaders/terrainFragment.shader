#version 410 core

out vec4 FragColor;

in vec2 uv;
in vec3 worldPosition;

uniform sampler2D mainTex;
uniform sampler2D normalTex;

uniform sampler2D dirt, sand, grass, rock, snow;

uniform vec3 lightDirection;
uniform vec3 cameraPosition;
uniform int season;

vec3 lerp(vec3 a, vec3 b, float t)
{
	return a +(b-a) * t;
	}

void main()
{
	// Normal Map

	vec3 normal = texture(normalTex, uv).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	normal.gb = normal.bg;
	normal.r = -normal.r;
	normal.b = -normal.b;


	// Specular data
	vec3 viewDir = normalize(worldPosition - cameraPosition);
	//vec3 reflDir = normalize(reflect(lightDirection, normal));

	// lighting
	float lightValue = max(-dot(normal, lightDirection), 0.0);
	//float specular = pow(max(-dot(reflDir, viewDir),0.0),5);

	// build color
	float y = worldPosition.y;

	float height1 = clamp((y-25) / 10,-1,1) *.5+.5;
	float height2 = clamp((y-50) / 10,-1,1) *.5+.5;
	float height3 = clamp((y-75) / 10,-1,1) *.5+.5;
	float height4 = clamp((y-100) / 10,-1,1) *.5+.5;
	float height5 = clamp((y-125) / 10,-1,1) *.5+.5;
	float height6 = clamp((y-150) / 10,-1,1) *.5+.5;
	float height7 = clamp((y-175) / 10,-1,1) *.5+.5;
	float height8 = clamp((y-200) / 10,-1,1) *.5+.5;
	float height9 = clamp((y-225) / 10,-1,1) *.5+.5;
	float height10 = clamp((y-250) / 10,-1,1) *.5+.5;

	float dist = length(worldPosition.xyz - cameraPosition);
	float uvLerp = clamp((dist - 250) / 150.0 - 1.0, 0.0, 1.0) * 0.5 + 0.5;

	vec3 sandColorClose = texture(sand, uv * 100).rgb;
	vec3 dirtColorClose = texture(dirt, uv * 100).rgb;
	vec3 grassColorClose = texture(grass, uv * 100).rgb;
	vec3 rockColorClose = texture(rock, uv * 100).rgb;
	vec3 snowColorClose = texture(snow, uv * 100).rgb;

	vec3 sandColorFar = texture(sand, uv * 10).rgb;
	vec3 dirtColorFar = texture(dirt, uv * 10).rgb;
	vec3 grassColorFar = texture(grass, uv * 10).rgb;
	vec3 rockColorFar = texture(rock, uv * 10).rgb;
	vec3 snowColorFar = texture(snow, uv * 10).rgb;

	vec3 sandColor = lerp(sandColorClose, sandColorFar, uvLerp);
	vec3 dirtColor = lerp(dirtColorClose, dirtColorFar, uvLerp);
	vec3 grassColor = lerp(grassColorClose, grassColorFar, uvLerp);
	vec3 rockColor = lerp(rockColorClose, rockColorFar, uvLerp);
	vec3 snowColor = lerp(snowColorClose, snowColorFar, uvLerp);

	//spring
	vec3 earlySpringColour = lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(sandColor, dirtColor, height1), dirtColor, height2), grassColor, height3), grassColor, height4), grassColor, height5), grassColor, height6), snowColor, height7), snowColor, height8), snowColor, height9) , snowColor, height10);
	vec3 lateSpringColour = lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(sandColor, dirtColor, height1), dirtColor, height2), grassColor, height3), grassColor, height4), grassColor, height5), grassColor, height6), rockColor, height7), snowColor, height8), snowColor, height9) , snowColor, height10);
	//summer
	vec3 earlySummerColour = lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(sandColor, dirtColor, height1), grassColor, height2), grassColor, height3), grassColor, height4), grassColor, height5), grassColor, height6), rockColor, height7), rockColor, height8), rockColor, height9) , snowColor, height10);
	vec3 lateSummerColour = lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(sandColor, dirtColor, height1), grassColor, height2), grassColor, height3), grassColor, height4), grassColor, height5), grassColor, height6), rockColor, height7), rockColor, height8), rockColor, height9) , snowColor, height10);
	//autum
	vec3 earlyAutumColour = lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(sandColor, dirtColor, height1), grassColor, height2), grassColor, height3), grassColor, height4), grassColor, height5), grassColor, height6), rockColor, height7), rockColor, height8), rockColor, height9) , snowColor, height10);
	vec3 lateAutumColour = lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(sandColor, dirtColor, height1), grassColor, height2), grassColor, height3), grassColor, height4), grassColor, height5), grassColor, height6), rockColor, height7), rockColor, height8), snowColor, height9) , snowColor, height10);
	//winter
	vec3 earlyWinterColour = lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(sandColor, dirtColor, height1), dirtColor, height2), grassColor, height3), grassColor, height4), grassColor, height5), grassColor, height6), rockColor, height7), snowColor, height8), snowColor, height9) , snowColor, height10);
	vec3 lateWinterColour = lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(lerp(sandColor, dirtColor, height1), dirtColor, height2), grassColor, height3), grassColor, height4), grassColor, height5), grassColor, height6), snowColor, height7), snowColor, height8), snowColor, height9) , snowColor, height10);

	float fog = pow(clamp((dist - 250) / 1000.0, 0.0, 1.0), 2.0);

	vec3 topColor = vec3(68.0/255.0, 118.0/255.0, 189.0/255.0);
	vec3 botColor = vec3(188.0/255.0, 214.0/255.0, 231.0/255.0);

	vec3 fogColor = lerp(botColor, topColor, max(viewDir.y, 0.0));

	vec3 seasonalColour;
	switch(season){
		case 0:
		seasonalColour = earlySpringColour;
		break;
		case 1:
		seasonalColour = lateSpringColour;
		break;
		case 2:
		seasonalColour = earlySummerColour;
		break;
		case 3:
		seasonalColour = lateSummerColour;
		break;
		case 4:
		seasonalColour = earlyAutumColour;
		break;
		case 5:
		seasonalColour = lateAutumColour;
		break;
		case 6:
		seasonalColour = earlyWinterColour;
		break;
		case 7:
		seasonalColour = lateWinterColour;
		break;
		}

	vec4 output = vec4(lerp(seasonalColour * min(lightValue + 0.1, 1.0), fogColor, fog),1.0);// + specular * output.rgb;

	FragColor = output;
}