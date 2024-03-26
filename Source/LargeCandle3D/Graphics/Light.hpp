#pragma once

#include <vector>
#include <list>
#include <memory>

#include "LargeCandle3D/Graphics/SceneNodes.hpp"

/*-------------------------------------------------------------------------
 *  Light.hpp
 *-----------------------------------------------------------------------*/

class Scene;

/*
 *  LightManager
 */
class LightManager
{
    friend class Scene;

  public:
    LightManager();
    ~LightManager();

    void CalcLighting(Scene* pScene);

  private:
    LightList   m_Lights;
};