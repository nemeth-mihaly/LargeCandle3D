#pragma once

#include <vector>
#include <map>
#include <memory>

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Graphics/SceneNodes.h"
#include "LargeCandle3D/Graphics/Camera.h"

//-----------------------------------------------
//
//-----------------------------------------------

using SceneNodeMap = std::map<u32, std::shared_ptr<SceneNode>>;

//
// class Scene
//

class Scene
{
  public:
    std::shared_ptr<Camera> pCamera;

    std::shared_ptr<SceneMeshNode> pFloor;
    std::shared_ptr<SceneMeshNode> pCrates[10];
    std::shared_ptr<SceneMeshNode> pPointLights[4];

    Scene();
    ~Scene();

    void OnRender();

  private:
    std::shared_ptr<SceneNode> m_pRoot;
};