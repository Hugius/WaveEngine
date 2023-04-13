#version 460 core

in vec2 f_uv;

uniform sampler2D u_texture;

uniform dvec3 u_color;

uniform double u_opacity;
uniform double u_lightness;

uniform bool u_hasTexture;

layout (location = 0) out vec4 o_finalColor;

vec4 calculateTextureColor()
{
	if(u_hasTexture)
	{
		vec4 textureColor = texture(u_texture, f_uv);

		return textureColor;
	}
	else
	{
		return vec4(1.0f);
	}
}

void main()
{
	vec4 textureColor = calculateTextureColor();
	vec4 finalColor = vec4(0.0f);

	finalColor.rgb += textureColor.rgb;
	finalColor.rgb *= vec3(u_color);
	finalColor.rgb *= float(u_lightness);
	finalColor.rgb = clamp(finalColor.rgb, vec3(0.0f), vec3(1.0f));
	finalColor.a += textureColor.a;
	finalColor.a *= float(u_opacity);

	o_finalColor = finalColor;
}