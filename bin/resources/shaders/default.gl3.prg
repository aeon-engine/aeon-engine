[vertex]
#version 330

uniform mat4 projection_matrix;
uniform mat4 model_matrix;
uniform mat4 view_matrix;

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec3 in_uvw;
layout (location = 3) in vec4 in_color;
layout (location = 4) in vec3 in_tangent;
layout (location = 5) in vec3 in_bitangent;

out vec2 frag_uvw;

void main()
{
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_position, 1.0);
    frag_uvw = in_uvw.xy;
}

[fragment]
#version 330

in vec2 frag_uvw;
out vec4 output_color;

uniform sampler2D texture0;

void main()
{
    output_color = texture(texture0, frag_uvw);
}
