#pragma once

#include "LargeCandle3D/Core/PrimTypes.h"

//-----------------------------------------------
//
//-----------------------------------------------

//
// class Texture
//

class Texture
{
  public:
    Texture(i32 width, i32 height, i32 numChannels, void* pPixels);
    ~Texture();

    void Bind(u32 unit = 0) const;

  private:
    u32 m_TextureID;
};