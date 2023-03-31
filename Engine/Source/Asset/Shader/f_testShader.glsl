#version 330 core

out vec4 fragColor;

in vec3 v_worldPos;
in vec3 v_normal;
in vec3 v_tangent;
in vec3 v_bitangent;
in vec2 v_textureCoord;

uniform sampler2D s_albedo;
uniform sampler2D s_normal;
uniform sampler2D s_orm;
uniform sampler2D s_emissive;

void main()
{
	fragColor = texture(s_albedo, v_textureCoord);
	fragColor = vec4(v_normal, 1.0);
}
