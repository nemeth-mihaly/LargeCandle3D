#pragma once

#include <vector>
#include <memory>

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Graphics/SceneNodes.h"
#include "LargeCandle3D/Graphics/Light.h"
#include "LargeCandle3D/Graphics/Camera.h"

class Scene
{
  public:
    std::shared_ptr<Camera> pCamera;
    std::shared_ptr<SceneMeshNode> m_pCrate;

    LightManager* m_pLightManager;

    Scene();
    ~Scene();

    void OnUpdate(f32 deltaTime);
    void OnRender();

  private:
    std::shared_ptr<SceneNode> m_pRoot;
};