#shader vertex
#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 icolor;
layout(location = 2) in vec2 atex;
layout(location = 3) in vec3 aNormal;

uniform float gScale;

out vec2 btex;
out vec3 jcolor;
out vec3 normal;
out vec3 currentPosition;

//uniform mat4 lightPos;
uniform mat4 camMatrix;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
void main()
{
	currentPosition = vec3(model * vec4(pos, 1.0f));
	jcolor = icolor;
	normal = normalize(vec3(model * vec4(pos, 1.0f)));
	//camMatrix=proj*view from cam.matrix
	gl_Position = camMatrix * vec4(currentPosition, 1.0f);
	normal = aNormal;
	btex = atex;

}



#shader fragment
#version 330 core
out vec4 colors;

//uniform sampler2D tex0;
in vec3 jcolor;
in vec2 btex;
in vec3 normal;
in vec3 currentPosition;

uniform sampler2D gsampler;
uniform vec4 lightColor;
uniform vec3 lightPos;
void main()
{
	float ambient = 0.1f;
	vec3 normal = normalize(currentPosition);
	vec3 lightDirection = normalize(lightPos - currentPosition);

	float diffuse = max(dot(normal, lightDirection), 0.0f);

	colors = texture2D(gsampler, btex)*(ambient + diffuse)*lightColor;
	//colors = (ambient + diffuse)*lightColor*vec4(jcolor, 1.0f);
	
}
