#version 460 core

layout (location = 0) in dvec2 v_position;

uniform dmat3 u_transformation;

void main()
{
	gl_Position = vec4(u_transformation * vec3(v_position, 1.0f), 1.0f);
}