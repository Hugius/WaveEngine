#version 460 core

uniform dvec3 u_color;

layout (location = 0) out vec4 o_finalColor;

void main()
{
	o_finalColor = vec4(u_color, 1.0f);
}