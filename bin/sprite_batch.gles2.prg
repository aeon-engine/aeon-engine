[vertex]
uniform mat4 projection_matrix;
uniform mat4 model_matrix;
uniform mat4 view_matrix;

attribute vec2 in_position;
attribute vec2 in_texture_coord;
attribute vec4 in_color;

// The sprites model matrix is packed in the vertex attributes
// as 4 vec4's, since packing matrices directly is not supported.
attribute vec4 in_sprite_model_mat_col0;
attribute vec4 in_sprite_model_mat_col1;
attribute vec4 in_sprite_model_mat_col2;
attribute vec4 in_sprite_model_mat_col3;
 
varying vec2 texture_coordinate;

void main()
{
    mat4 sprite_model_matrix = mat4(in_sprite_model_mat_col0, in_sprite_model_mat_col1,
        in_sprite_model_mat_col2, in_sprite_model_mat_col3);

    // For batched sprites, the real model matrix is ignored in favour of the sprite's own model matrix
    gl_Position = projection_matrix * view_matrix * sprite_model_matrix * vec4(in_position, 0.0, 1.0);

    texture_coordinate = in_texture_coord;
}

[fragment]
precision mediump float;
varying vec2 texture_coordinate;
uniform sampler2D texture0;

void main()
{
    gl_FragColor = texture2D(texture0, texture_coordinate);
}
