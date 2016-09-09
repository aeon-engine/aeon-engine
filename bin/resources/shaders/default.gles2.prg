[vertex]
uniform mat4 projection_matrix;
uniform mat4 model_matrix;
uniform mat4 view_matrix;

attribute vec3 in_position;
attribute vec2 in_texture_coord;
attribute vec4 in_color;
 
varying vec2 texture_coordinate;

void main()
{
    // For batched sprites, the real model matrix is ignored in favour of the sprite's own model matrix
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_position, 1.0);

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
