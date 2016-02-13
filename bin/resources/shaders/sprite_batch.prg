[vertex]
#version 330

uniform mat4 projection_matrix;
uniform mat4 model_matrix;
uniform mat4 view_matrix;

layout (location = 0) in vec2 in_position;
layout (location = 1) in vec2 in_texture_coord;
layout (location = 2) in vec4 in_color;

// The sprites model matrix is packed in the vertex attributes
// as 4 vec4's, since packing matrices directly is not supported.
layout (location = 3) in vec4 in_sprite_model_mat_col0;
layout (location = 4) in vec4 in_sprite_model_mat_col1;
layout (location = 5) in vec4 in_sprite_model_mat_col2;
layout (location = 6) in vec4 in_sprite_model_mat_col3;

out vec2 texture_coordinate;

void main()
{
    mat4 sprite_model_matrix = mat4(in_sprite_model_mat_col0, in_sprite_model_mat_col1,
        in_sprite_model_mat_col2, in_sprite_model_mat_col3);

    // For batched sprites, the real model matrix is ignored in favour of the sprite's own model matrix
    gl_Position = projection_matrix * view_matrix * sprite_model_matrix * vec4(in_position, 0.0, 1.0);
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

