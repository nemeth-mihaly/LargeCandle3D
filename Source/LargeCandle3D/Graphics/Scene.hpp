#pragma once

#include <stdint.h>
#include <vector>
#include <memory>
#include "LargeCandle3D/Graphics/SceneNodes.hpp"
#include "LargeCandle3D/Graphics/Light.hpp"

/*-------------------------------------------------------------------------
 *  Scene.hpp
 *-----------------------------------------------------------------------*/

/*
 *  Scene
 */
class Scene
{
  public:
    std::shared_ptr<SceneMeshNode> m_pCrates[3];

    LightManager* m_pLightManager;

    Scene();
    ~Scene();

    void OnUpdate(float deltaTime);
    void OnRender();

    void SetCamera(const std::shared_ptr<CameraNode>& pCamera)
    {
      m_pCamera = pCamera;
    }

    const std::shared_ptr<CameraNode>& GetCamera() const
    {
      return m_pCamera;
    }

  private:
    std::shared_ptr<SceneNode>    m_pRoot;
    std::shared_ptr<CameraNode>   m_pCamera;
};