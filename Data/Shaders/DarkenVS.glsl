#version 330 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 texcoords;

out vec2 tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	tex_coords = texcoords;
}