#pragma once

#include <stdint.h>

/*-------------------------------------------------------------------------
 *  Texture.hpp
 *-----------------------------------------------------------------------*/

/*
 *  Texture
 */
class Texture
{
  public:
    Texture(int width, int height, int numChannels, void* pPixels);
    ~Texture();

    void Bind(uint32_t unit = 0) const;

  private:
    uint32_t    m_TextureID;
};