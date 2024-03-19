#version 460 core

uniform vec3 u_Color;

out vec4    v_FragColor;

void main()
{
  v_FragColor = vec4(u_Color, 1.0);
}