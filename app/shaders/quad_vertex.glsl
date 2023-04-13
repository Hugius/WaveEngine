#version 460 core

layout (location = 0) in dvec2 v_position;
layout (location = 1) in dvec2 v_uv;

uniform dmat3 u_transformation;

uniform dvec2 u_uvMultiplier;
uniform dvec2 u_uvOffset;

out vec2 f_uv;

void main()
{
	gl_Position = vec4(u_transformation * vec3(v_position, 1.0f), 1.0f);

	f_uv.x = float(u_uvOffset.x + (v_uv.x * u_uvMultiplier.x));
	f_uv.y = float(u_uvOffset.y + (v_uv.y * u_uvMultiplier.y));
}