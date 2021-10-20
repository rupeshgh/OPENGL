#shader vertex
#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec3 icolor;




uniform float gScale;

out vec3 jcolor;

void main()
{
	
	gl_Position = vec4(gScale*pos.x,gScale*pos.y,0.0f, 1.0f);
	
	jcolor = icolor;
	
}

#shader fragment
#version 330 core
out vec4 colors;


in vec3 jcolor;



void main()
{
	colors = vec4(jcolor, 1.0f);
	

}
