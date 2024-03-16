#pragma once

#include <memory>

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Graphics/Geometry.h"
#include "LargeCandle3D/Graphics/Texture.h"

//-----------------------------------------------
//
//-----------------------------------------------

extern glm::vec3 g_White;
extern glm::vec3 g_Black;
extern glm::vec3 g_Cyan;
extern glm::vec3 g_Red;
extern glm::vec3 g_Green;
extern glm::vec3 g_Blue;
extern glm::vec3 g_Yellow;
extern glm::vec3 g_Gray40;
extern glm::vec3 g_Gray25;
extern glm::vec3 g_Gray65;

//
// class Material
//

class Material
{
  public:
    glm::vec3 AmbientColor;
    glm::vec3 DiffuseColor;
    glm::vec3 SpecularColor;

    f32 Shininess;

    std::shared_ptr<Texture> Diffuse;
    std::shared_ptr<Texture> Specular;
    std::shared_ptr<Texture> Emission;

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