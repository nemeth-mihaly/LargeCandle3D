#pragma once

#include <vector>
#include <memory>

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Graphics/SceneNodes.h"
#include "LargeCandle3D/Graphics/Camera.h"

//-----------------------------------------------
//
//-----------------------------------------------

//
// class Scene
//

class Scene
{
  public:
    std::shared_ptr<Camera> pCamera;

    Scene();
    ~Scene();

    void OnRender();

  private:
    std::shared_ptr<SceneNode> m_pRoot;
    std::shared_ptr<SceneMeshNode> m_pPlatform;
    std::shared_ptr<SceneMeshNode> m_pStaticObjectA;
    std::shared_ptr<SceneMeshNode> m_pLight;
};