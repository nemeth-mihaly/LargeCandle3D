#version 460 core

in vec3 v_FragPos;
in vec3 v_Normal;

uniform int u_bIsLightSource;
uniform vec3 u_LightSourcePos;
uniform vec3 u_ObjectColor, u_LightSourceColor;
uniform vec3 u_ViewPos;

out vec4 v_FragColor;

void main()
{
  float ambientStrength = 0.2;
  vec3 ambient = ambientStrength * u_LightSourceColor;

  vec3 diffuse = max(dot(normalize(v_Normal), normalize(u_LightSourcePos - v_FragPos)), 0.0) * u_LightSourceColor;

  float specularStrength = 0.5;
  vec3 viewDirection = normalize(u_ViewPos - v_FragPos);
  vec3 reflectDirection = reflect(-normalize(u_LightSourcePos - v_FragPos), normalize(v_Normal));

  vec3 specular = specularStrength * pow(max(dot(viewDirection, reflectDirection), 0.0), 32) * u_LightSourceColor;

  vec3 result = vec3(1.0, 1.0, 1.0);

  if (u_bIsLightSource == 0)
    result = (ambient + diffuse + specular) * u_ObjectColor;

  v_FragColor = vec4(result, 1.0);
}