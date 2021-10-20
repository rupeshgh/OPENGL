#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 icolor;

out vec3 jcolor;
void main()
{
	gl_Position =vec4(pos,0.5f);
	jcolor=icolor;
}