#version 460 core

struct Material
{
  vec3    Ambient;
  vec3    Diffuse;
  vec3    Specular;
  float   Shininess;
};

struct Light
{
  vec3    Position;

  vec3    Ambient;
  vec3    Diffuse;
  vec3    Specular;
};

in vec3     v_FragPos;
in vec3     v_Normal;

uniform vec3        u_ViewPos;
uniform Material    u_Material;
uniform int         u_bIsLightSource;
uniform Light       u_Light;

out vec4    v_FragColor;

void main()
{
  vec3 result = vec3(1.0, 1.0, 1.0);

  if (u_bIsLightSource == 1)
  {
    v_FragColor = vec4(result, 1.0);
    return;
  }

  vec3 ambient = u_Light.Ambient * u_Material.Ambient;

  vec3 normal = normalize(v_Normal);
  vec3 lightDir = normalize(u_Light.Position - v_FragPos);
  vec3 diffuse = u_Light.Diffuse * (max(dot(normal, lightDir), 0.0) * u_Material.Diffuse);

  vec3 viewDir = normalize(u_ViewPos - v_FragPos);
  vec3 reflectDir = reflect(-lightDir, normal);
  vec3 specular = u_Light.Specular * (pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess) * u_Material.Specular);

  result = (ambient + diffuse + specular);

  v_FragColor = vec4(result, 1.0);
}