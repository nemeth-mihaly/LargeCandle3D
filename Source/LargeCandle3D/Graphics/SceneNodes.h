#pragma once

#include <vector>
#include <memory>

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Graphics/Geometry.h"
#include "LargeCandle3D/Graphics/Mesh.h"
#include "LargeCandle3D/Graphics/Material.h"

//-----------------------------------------------
//
//-----------------------------------------------

//
//  Interface class ISceneNode
//

class ISceneNode
{
  public:
    virtual ~ISceneNode() = default;

    virtual void VPreRender() = 0;
    virtual void VRender() = 0;
    virtual void VRenderChild() = 0;
    virtual void VPostRender() = 0;

    virtual void VAddChild(const std::shared_ptr<ISceneNode>& pChild) = 0;
    virtual void VRemoveChild() = 0;
};

//
//  class SceneNode
//

class SceneNode : public ISceneNode
{
  protected:
    SceneNode* m_pParent;
    std::vector<std::shared_ptr<ISceneNode>> m_Childs;

  public:
    glm::vec3 Position;
    glm::vec3 Scale;

    glm::mat4 Transform;

    bool bIsLightSource;
    // glm::vec3 Color;
    Material Material;

    SceneNode();
    virtual ~SceneNode();

    virtual void VPreRender();
    virtual void VRender();
    virtual void VRenderChild();
    virtual void VPostRender();

    virtual void VAddChild(const std::shared_ptr<ISceneNode>& pChild);
    virtual void VRemoveChild();
};

//
//  class SceneMeshNode
//

class SceneMeshNode : public SceneNode
{
  public:
    SceneMeshNode(const std::shared_ptr<Mesh>& pMesh);
    ~SceneMeshNode();

    virtual void VRender();

  private:
    std::shared_ptr<Mesh> m_pMesh;
};

//
//  class SceneLightNode
//

class SceneLightNode : public SceneNode
{
  public:
    SceneLightNode();
    ~SceneLightNode();
};