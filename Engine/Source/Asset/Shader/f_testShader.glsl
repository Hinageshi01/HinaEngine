#version 330 core

out vec4 fragColor;

in vec3 v_worldPos;
in vec3 v_normal;
in vec2 v_textureCoord;

uniform sampler2D us_albedo;

void main()
{
	fragColor = texture(us_albedo, v_textureCoord);
}