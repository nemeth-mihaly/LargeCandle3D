#include "LargeCandle3D/Graphics/Material.hpp"

#include "LargeCandle3D/Applv/Application.hpp"

/*-------------------------------------------------------------------------
 *  Material.cpp
 *-----------------------------------------------------------------------*/

/*
 *  Impl. of Material
 */

Material::Material()
{
  Ambient = Vector3(1.0f);
  Diffuse = Vector3(1.0f);
  Specular = Vector3(1.0f);

  Shininess = 32.0f;

  //Diffuse = g_pTexture;
  //Specular = g_pTexture;
  //Emission = g_pTexture;
}

Material::~Material()
{
}