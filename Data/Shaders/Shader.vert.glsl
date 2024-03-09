#version 460 core
    
in layout(location = 0) vec3 a_Pos;

uniform mat4 u_Projection, u_View, u_Model;

void main()
{
  gl_Position = u_Projection * u_View * u_Model * vec4(a_Pos, 1.0);
}