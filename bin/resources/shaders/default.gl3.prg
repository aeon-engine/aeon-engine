[vertex]
#version 330

uniform mat4 projection_matrix;
uniform mat4 model_matrix;
uniform mat4 view_matrix;

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_texture_coord;
layout (location = 2) in vec4 in_color;

out vec2 texture_coordinate;

void main()
{
    // For batched sprites, the real model matrix is ignored in favour of the sprite's own model matrix
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_position, 1.0);
    texture_coordinate = in_texture_coord;
}

[fragment]
#version 330

in vec2 texture_coordinate;
out vec4 output_color;

uniform sampler2D texture0;

void main()
{
    output_color = texture(texture0, texture_coordinate);
}
