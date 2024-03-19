#pragma once

#include <vector>
#include <memory>

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Graphics/SceneNodes.h"
#include "LargeCandle3D/Graphics/Light.h"
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

    //std::shared_ptr<SceneDirLight> pDirLight;
    //std::shared_ptr<SceneSpotLight> pSpotLight;

    std::shared_ptr<SceneMeshNode> pCrates[10];
    //std::shared_ptr<SceneMeshNode> pPointLights[4];

    LightManager* m_pLightManager;

    Scene();
    ~Scene();

    void OnRender();

  private:
    std::shared_ptr<SceneNode> m_pRoot;
};