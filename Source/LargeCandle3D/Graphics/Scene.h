#pragma once

#include <vector>
#include <memory>

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Graphics/SceneNodes.h"
#include "LargeCandle3D/Graphics/Light.h"

class Scene
{
  public:
    std::shared_ptr<CameraNode> m_pCameraNode;

    std::shared_ptr<SceneMeshNode> m_pCrates[3];

    LightManager* m_pLightManager;

    Scene();
    ~Scene();

    void OnUpdate(f32 deltaTime);
    void OnRender();

  private:
    std::shared_ptr<SceneNode> m_pRoot;
};