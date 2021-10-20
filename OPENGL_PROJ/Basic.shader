#shader vertex
#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec3 icolor;
layout(location = 2) in vec2 aTex;



uniform float gScale;

out vec3 jcolor;
out vec2 texCor;
void main()
{
	
	//gl_Position = vec4(gScale*pos.x,gScale*pos.y,0.0f, 1.0f);
	gl_Position = vec4(pos, 0.0f, 1.0f);
	jcolor = icolor;
	texCor = aTex;
}

#shader fragment
#version 330 core
out vec4 colors;
//out vec4 texCord;

in vec3 jcolor;
in vec2 texCor;

uniform sampler2D tex0;
void main()
{
	//colors = vec4(jcolor, 1.0f);
	colors = texture(tex0, texCor);

}
