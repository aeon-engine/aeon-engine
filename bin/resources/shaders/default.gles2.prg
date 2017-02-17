[vertex]
uniform mat4 projection_matrix;
uniform mat4 model_matrix;
uniform mat4 view_matrix;

attribute vec3 in_position;
attribute vec3 in_normal;
attribute vec3 in_uvw;
attribute vec4 in_color;
attribute vec3 in_tangent;
attribute vec3 in_bitangent;
 
varying vec3 frag_uvw;

void main()
{
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_position, 1.0);
    frag_uvw = in_uvw;
}

[fragment]
precision mediump float;
varying vec3 frag_uvw;
uniform sampler2D texture0;

void main()
{
    gl_FragColor = texture2D(texture0, frag_uvw.xy);
}
