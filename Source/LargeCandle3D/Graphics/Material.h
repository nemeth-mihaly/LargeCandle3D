#pragma once

#include <memory>

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Graphics/Geometry.h"
#include "LargeCandle3D/Graphics/Texture.h"

//-----------------------------------------------
//
//-----------------------------------------------

extern  Vector3  g_White;
extern  Vector3  g_Black;
extern  Vector3  g_Cyan;
extern  Vector3  g_Red;
extern  Vector3  g_Green;
extern  Vector3  g_Blue;
extern  Vector3  g_Yellow;
extern  Vector3  g_Gray40;
extern  Vector3  g_Gray25;
extern  Vector3  g_Gray65;

//
// class Material
//

class Material
{
  public:
    Vector3     Ambient;
    Vector3     Diffuse;
    Vector3     Specular;

    f32           Shininess;

    //std::shared_ptr<Texture> Diffuse;
    //std::shared_ptr<Texture> Specular;
    //std::shared_ptr<Texture> Emission;

    Material();
    ~Material();
};

//-----------------------------------------------
//    Real-world Materials
//      from: http://devernay.free.fr/cours/opengl/materials.html
//-----------------------------------------------
// Name        Ambient               Diffuse                    Specular                     Shininess
//-----------------------------------------------
// Emerald     (5.48, 44.50, 5.48)   (19.30, 156.63, 19.30)     (161.42, 185.59. 161.42)     76.8
// Jade
// Obsidian
// Pearl
// Ruby
// Turquoise
// Brass
// Bronze
// Chrome
// Copper
// Gold
// Silver
// Black Plastic
// Cyan Plastic
// Green Plastic
// Red Plastic
// White Plastic
// Yellow Plastic
// Black Rubber
// Cyan Rubber
// Green Rubber
// Red Rubber
// White Rubber
// Yellow Rubber