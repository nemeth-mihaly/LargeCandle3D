#version 460 core

struct Material
{
  //vec3    Ambient;
  //vec3    Diffuse;
  sampler2D   Diffuse;
  //vec3        Specular;
  sampler2D   Specular;
  sampler2D   Emission;
  float       Shininess;
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
in vec2     v_TexCoords;

uniform vec3        u_ViewPos;
uniform Material    u_Material;
uniform int         u_bIsLightSource;
uniform Light       u_Light;
uniform float       u_EmissionStrength;

out vec4    v_FragColor;

void main()
{
  vec4 result = vec4(1.0, 1.0, 1.0, 1.0);

  if (u_bIsLightSource == 1)
  {
    v_FragColor = result;
    return;
  }

  //vec3 ambient = u_Light.Ambient * u_Material.Ambient;
  
  vec3 ambient = u_Light.Ambient * texture(u_Material.Diffuse, v_TexCoords).rgb;

  vec3 normal = normalize(v_Normal);
  vec3 lightDir = normalize(u_Light.Position - v_FragPos);
  
  //vec3 diffuse = u_Light.Diffuse * (max(dot(normal, lightDir), 0.0) * u_Material.Diffuse);
  
  vec3 diffuse = u_Light.Diffuse * (max(dot(normal, lightDir), 0.0) * texture(u_Material.Diffuse, v_TexCoords).rgb);

  vec3 viewDir = normalize(u_ViewPos - v_FragPos);
  vec3 reflectDir = reflect(-lightDir, normal);
  
  //vec3 specular = u_Light.Specular * (pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess) * u_Material.Specular);
  
  vec3 specular = u_Light.Specular 
    * (pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess) 
      * texture(u_Material.Specular, v_TexCoords).rgb);

  vec3 emission = texture(u_Material.Emission, v_TexCoords).rgb 
    * step(vec3(1.0), vec3(1.0) - texture(u_Material.Specular, v_TexCoords).rgb);

  emission *= u_EmissionStrength;

  result = vec4(ambient + diffuse + specular + emission, 1.0);
  v_FragColor = result;
}