[vertex]
#version 110

varying vec3 N;
varying vec3 v;
varying vec2 texture_coordinate;

void main(void)
{
   v = vec3(gl_ModelViewMatrix * gl_Vertex);       
   N = normalize(gl_NormalMatrix * gl_Normal);

   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
   
   texture_coordinate = vec2(gl_MultiTexCoord0);
}


[fragment]
#version 110

varying vec3 N;
varying vec3 v;
varying vec2 texture_coordinate;
uniform sampler2D texture0;    

void main (void)  
{  
   vec3 L = normalize(gl_LightSource[0].position.xyz - v);   
   vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)  
   vec3 R = normalize(-reflect(L,N));  
 
   //calculate Ambient Term:  
   vec4 Iamb = gl_FrontLightProduct[0].ambient;    

   //calculate Diffuse Term:  
   vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0);    
   
   // calculate Specular Term:
   vec4 Ispec = gl_FrontLightProduct[0].specular 
                * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);

   // write Total Color:  
   gl_FragColor = texture2D(texture0, texture_coordinate) * (gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec);   
}