#version 460 core

//
//  struct Material
//

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

//
//  struct DirLight
//

struct DirLight
{
  vec3  Direction;

  vec3  Ambient;
  vec3  Diffuse;
  vec3  Specular;
};

//
//  struct PointLight
//

struct PointLight
{
  vec3    Position;

  vec3    Ambient;
  vec3    Diffuse;
  vec3    Specular;

  float   Constant;
  float   Linear;
  float   Quadratic;
};

//
//  struct SpotLight
//

struct SpotLight
{
  vec3    Position;
  vec3    Direction;
  float   CutOff;
  float   OuterCutOff;

  vec3    Ambient;
  vec3    Diffuse;
  vec3    Specular;

  float   Constant;
  float   Linear;
  float   Quadratic;
};

in vec3     v_FragPos;

in vec3     v_Normal;
in vec2     v_TexCoords;

uniform DirLight    u_DirLight;

#define MAXIMUM_POINT_LIGHTS 4
uniform PointLight  u_PointLights[MAXIMUM_POINT_LIGHTS];

uniform SpotLight   u_SpotLight;

uniform vec3        u_ViewPos;
uniform Material    u_Material;
uniform int         u_bIsLightSource;

out vec4    v_FragColor;

//
//  CalcDirLight()
//

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

//
//  CalcPointLight()
//

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir); 

//
//  CalcSpotLight()
//

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

//
//  Main()
//

void main()
{
  vec4 result = vec4(1.0, 1.0, 1.0, 1.0);

  if (u_bIsLightSource == 1)
  {
    v_FragColor = result;
    return;
  }

  vec3 normal = normalize(v_Normal);
  vec3 viewDir = normalize(u_ViewPos - v_FragPos);

  result = vec4(CalcDirLight(u_DirLight, normal, viewDir), 1.0);

  for (int i = 0; i < MAXIMUM_POINT_LIGHTS; i++)
    result += vec4(CalcPointLight(u_PointLights[i], normal, v_FragPos, viewDir), 1.0);

  result += vec4(CalcSpotLight(u_SpotLight, normal, v_FragPos, viewDir), 1.0);

  //  Emission

  vec3 emission = texture(u_Material.Emission, v_TexCoords).rgb 
    * step(vec3(1.0), vec3(1.0) - texture(u_Material.Specular, v_TexCoords).rgb);

  result += vec4(emission, 1.0);

  v_FragColor = result;
}

//
//  Impl. of CalcDirLight()
//

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
  vec3 ambient = light.Ambient * texture(u_Material.Diffuse, v_TexCoords).rgb;

  vec3 lightDir = normalize(-light.Direction);
  vec3 diffuse = light.Diffuse * (max(dot(normal, lightDir), 0.0) * texture(u_Material.Diffuse, v_TexCoords).rgb);

  vec3 reflectDir = reflect(-lightDir, normal);

  vec3 specular = light.Specular 
    * (pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess) 
      * texture(u_Material.Specular, v_TexCoords).rgb);

  return (ambient + diffuse + specular);
}

//
//  Impl. of CalcPointLight()
//

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
  vec3 ambient = light.Ambient * texture(u_Material.Diffuse, v_TexCoords).rgb;

  vec3 lightDir = normalize(light.Position - fragPos);
  vec3 diffuse = light.Diffuse * (max(dot(normal, lightDir), 0.0) * texture(u_Material.Diffuse, v_TexCoords).rgb);

  vec3 reflectDir = reflect(-lightDir, normal);

  vec3 specular = light.Specular 
    * (pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess) 
      * texture(u_Material.Specular, v_TexCoords).rgb);  

  float dist = length(light.Position - v_FragPos);
  float attenuation = 1.0 / (light.Constant + light.Linear * dist + light.Quadratic * (dist * dist));

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  return (ambient + diffuse + specular);
}

//
//  Impl. of CalcSpotLight()
//

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
  vec3 ambient = light.Ambient * texture(u_Material.Diffuse, v_TexCoords).rgb;

  vec3 lightDir = normalize(light.Position - fragPos);
  vec3 diffuse = light.Diffuse * (max(dot(normal, lightDir), 0.0) * texture(u_Material.Diffuse, v_TexCoords).rgb);

  vec3 reflectDir = reflect(-lightDir, normal);

  vec3 specular = light.Specular 
    * (pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess) 
      * texture(u_Material.Specular, v_TexCoords).rgb);    

  float theta = dot(lightDir, normalize(-light.Direction));
  float epsilon = light.CutOff - light.OuterCutOff;
  float intensity = clamp((theta - light.OuterCutOff) / epsilon, 0.0, 1.0);
  
  diffuse *= intensity;
  specular *= intensity;

  float dist = length(light.Position - v_FragPos);
  float attenuation = 1.0 / (light.Constant + light.Linear * dist + light.Quadratic * (dist * dist));

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  return (ambient + diffuse + specular);
}