#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec3 a_tangent;
layout(location = 3) in vec2 a_textureCoord;

out vec3 v_worldPos;
out vec3 v_normal;
out vec3 v_tangent;
out vec3 v_bitangent;
out vec2 v_textureCoord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
	
	v_worldPos = vec3(u_model * vec4(a_position, 1.0));
	
	mat3 modelInvTrans = mat3(transpose(inverse(u_model)));
	v_normal = normalize(modelInvTrans * a_normal);
	v_tangent = normalize(modelInvTrans * a_tangent);
	v_bitangent = normalize(cross(v_normal, v_tangent));

	v_textureCoord = a_textureCoord;
}
