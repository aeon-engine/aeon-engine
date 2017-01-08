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
out vec3 lightsource0_vector;
out vec3 halfVec;

void main()
{
    // For now we hardcode a light here.
    vec3 lightsource0 = vec3(3, 4, 10);

    mat4 model_view_matrix = view_matrix * model_matrix;
    mat3 model_view_matrix_3x3 = mat3(model_view_matrix);
    mat4 normal_matrix = transpose(inverse(model_view_matrix));

    vec3 vertexnormal_cameraspace = model_view_matrix_3x3 * normalize(in_normal);
    vec3 vertextangent_cameraspace = model_view_matrix_3x3 * normalize(in_tangent);
    vec3 vertexbitangent_cameraspace = model_view_matrix_3x3 * normalize(in_bitangent);

    vec3 vertex_position = vec3(model_view_matrix * vec4(in_position, 1.0));
    vec3 lightsource0_direction = normalize(lightsource0 - vertex_position);

    vec3 v;
    v.x = dot(lightsource0_direction, vertextangent_cameraspace);
    v.y = dot(lightsource0_direction, vertexbitangent_cameraspace);
    v.z = dot(lightsource0_direction, vertexnormal_cameraspace);
    lightsource0_vector = normalize(v);

    vec3 halfVector = normalize(vertex_position + lightsource0_direction);
    v.x = dot (halfVector, vertextangent_cameraspace);
    v.y = dot (halfVector, vertexbitangent_cameraspace);
    v.z = dot (halfVector, vertexnormal_cameraspace);

    // No need to normalize, t,b,n and halfVector are normal vectors.
    //normalize(v);
    halfVec = v;

    gl_Position = projection_matrix * model_view_matrix * vec4(in_position, 1.0);
    frag_uvw = in_uvw.xy;
}

[fragment]
#version 330

in vec2 frag_uvw;
out vec4 output_color;

in vec3 lightsource0_vector;
in vec3 halfVec;

uniform sampler2D texture0;
uniform sampler2D normal0;

void main()
{
    vec4 diffuseMaterial = texture(texture0, frag_uvw);
    if(diffuseMaterial.a == 0.0)
    {
        discard;
    }

    vec3 texturenormal_tangentspace = 2.0 * texture(normal0, frag_uvw).rgb - 1.0;
    texturenormal_tangentspace = normalize(texturenormal_tangentspace);

    float lamber_factor = max(dot(lightsource0_vector, texturenormal_tangentspace), 0.0);

    vec4 ambientLight = vec4(0.06, 0.06, 0.06, 1.0); //gl_LightSource[0].ambient;

    if (lamber_factor > 0.0)
    {
        vec4 diffuseLight  = vec4(0.0);

        vec4 specularMaterial = vec4(1.0);
        vec4 specularLight = vec4(1.0);
        float shininess = 0;

        diffuseLight = vec4(0.7, 0.7, 0.7, 1.0); // gl_LightSource[0].diffuse;

        // In doom3, specular value comes from a texture
        specularMaterial = vec4(1.0, 1.0, 1.0, 1.0);
        specularLight = vec4(0.8, 0.8, 0.8, 1.0); // gl_LightSource[0].specular;
        shininess = pow(max(dot(halfVec, texturenormal_tangentspace), 0.0), 2.0);

        output_color = diffuseMaterial * diffuseLight * lamber_factor;
        output_color += specularMaterial * specularLight * shininess;
    }

    output_color += ambientLight;
    output_color.a = texture(texture0, frag_uvw).a;
}
