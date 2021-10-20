#version 330 core
out vec4 colors;

in vec3 jcolor;
void main()
{
	colors =vec4(jcolor,0.5f);
	
}
