#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 icolor;
layout(location = 2) in vec2 atex;

uniform float gScale;

out vec2 btex;
out vec3 jcolor;


uniform mat4 camMatrix;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
void main()
{
	
	jcolor = icolor;
	gl_Position = camMatrix * proj * view* model * vec4(pos, 1.0f);
	//gl_Position = camMatrix*vec4(pos, 1.0f);
			
}



#version 330 core
out vec4 colors;


in vec3 jcolor;
in vec2 btex;


void main()
{
	colors = vec4(jcolor, 1.0f);
	

}
