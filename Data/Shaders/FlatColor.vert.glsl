#version 460 core

in layout(location = 0) vec3 a_Pos;
in layout(location = 1) vec3 a_Normal;
in layout(location = 2) vec2 a_TexCoords;

uniform mat4 u_ViewProjection, u_Model;

void main()
{
  gl_Position = u_ViewProjection * u_Model * vec4(a_Pos, 1.0);
}