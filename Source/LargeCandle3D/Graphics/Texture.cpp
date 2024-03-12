#include "LargeCandle3D/Graphics/Texture.h"

#include "LargeCandle3D/Vendor/glad/glad.h"

Texture::Texture(i32 width, i32 height, i32 numChannels, u8* pPixels)
{
  glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);

  glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  if (numChannels == 1)
  {
    glTextureStorage2D(m_TextureID, 1, GL_R8, width, height);
    glTextureSubImage2D(m_TextureID, 0, 0, 0, width, height, GL_RED, GL_UNSIGNED_BYTE, pPixels);
  }
  else
  if (numChannels == 3)
  {
    glTextureStorage2D(m_TextureID, 1, GL_RGB8, width, height);
    glTextureSubImage2D(m_TextureID, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pPixels);
  }
  else
  if (numChannels == 4)
  {
    glTextureStorage2D(m_TextureID, 1, GL_RGBA8, width, height);
    glTextureSubImage2D(m_TextureID, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pPixels);
  }

  glGenerateTextureMipmap(m_TextureID);
}

Texture::~Texture()
{
  glDeleteTextures(1, &m_TextureID);
}

void Texture::Bind(u32 unit) const
{
  glBindTextureUnit(unit, m_TextureID);
}