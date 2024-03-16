#include "LargeCandle3D/Graphics/Material.h"

#include "LargeCandle3D/Applv/Application.h"

glm::vec3 g_White(1.0f, 1.0f, 1.0f);	
glm::vec3 g_Black(0.0f, 0.0f, 0.0f);
glm::vec3 g_Cyan(0.0f, 1.0f, 1.0f);	
glm::vec3 g_Red(1.0f, 0.0f, 0.0f);
glm::vec3 g_Green(0.0f, 1.0f, 0.0f);
glm::vec3 g_Blue(0.0f, 0.0f, 1.0f);
glm::vec3 g_Yellow(1.0f, 1.0f, 0.0f);	
glm::vec3 g_Gray40(0.4f, 0.4f, 0.4f);
glm::vec3 g_Gray25(0.25f, 0.25f, 0.25f);
glm::vec3 g_Gray65(0.65f, 0.65f, 0.65f);

//-----------------------------------------------
//    Impl. of Material class
//-----------------------------------------------

Material::Material()
{
  AmbientColor = g_White;
  DiffuseColor = g_White;
  SpecularColor = g_White;

  Shininess = 32.0f;

  Diffuse = g_pTexture;
  Specular = g_pTexture;
  Emission = g_pTexture;
}

Material::~Material()
{
}