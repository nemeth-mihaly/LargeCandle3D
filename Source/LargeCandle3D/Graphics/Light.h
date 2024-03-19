#pragma once

#include <vector>
#include <list>
#include <memory>

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Graphics/SceneNodes.h"

class Scene;

//-----------------------------------------------
//
//-----------------------------------------------

//
//  class LightManager
//

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