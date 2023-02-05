#version 330 core

out vec4 fragColor;

in vec3 v_worldPos;
in vec3 v_normal;

void main()
{
	fragColor = vec4(v_worldPos, 1.0);
}
