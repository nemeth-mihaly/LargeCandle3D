#version 460 core
    
in layout(location = 0) vec3 a_Pos;
in layout(location = 1) vec3 a_Normal;

uniform mat4 u_Projection, u_View, u_Model;

out vec3 v_FragPos;
out vec3 v_Normal;

void main()
{
  gl_Position = u_Projection * u_View * u_Model * vec4(a_Pos, 1.0);
  v_FragPos = vec3(u_Model * vec4(a_Pos, 1.0));
  v_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
}