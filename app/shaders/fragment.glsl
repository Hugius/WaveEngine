#version 460 core

in vec2 f_uv;

uniform sampler2D u_texture;

uniform vec3 u_color;

uniform float u_opacity;
uniform float u_lightness;

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
	finalColor.rgb *= u_color;
	finalColor.rgb *= u_lightness;
	finalColor.rgb = clamp(finalColor.rgb, vec3(0.0f), vec3(1.0f));
	finalColor.a += textureColor.a;
	finalColor.a *= u_opacity;

	o_finalColor = finalColor;
}