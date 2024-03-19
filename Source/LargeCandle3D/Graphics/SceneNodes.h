#pragma once

#include <vector>
#include <list>
#include <memory>

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Graphics/Geometry.h"
#include "LargeCandle3D/Graphics/Mesh.h"
#include "LargeCandle3D/Graphics/Material.h"

class Scene;

//-----------------------------------------------
//
//-----------------------------------------------

class SceneLightNode;

using LightList = std::list<std::shared_ptr<SceneLightNode>>;

//
//  Interface class ISceneNode
//

class ISceneNode
{
  public:
    virtual ~ISceneNode() = default;

    virtual void VPreRender() = 0;
    virtual void VRender(Scene* pScene) = 0;
    virtual void VRenderChild(Scene* pScene) = 0;
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
    Vector3 Color;

    Vector3 Position;
    Vector3 Size;

    Matrix4x4 Transform;

    bool bIsLightSource;
    Material Material;

    SceneNode();
    virtual ~SceneNode();

    virtual void VPreRender();
    virtual void VRender(Scene* pScene);
    virtual void VRenderChild(Scene* pScene);
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

    virtual void VRender(Scene* pScene);

  private:
    std::shared_ptr<Mesh> m_pMesh;
};

//
//  class SceneLightNode
//

class SceneLightNode : public SceneNode
{
  public:
    Vector3   Ambient;
    Vector3   Diffuse;
    Vector3   Specular;
    Vector3   Emissive;

    SceneLightNode();
    ~SceneLightNode();
};

//
//  class SceneDirLight
//

class SceneDirLight : public SceneLightNode
{
  public:
    Vector3   Direction;

    SceneDirLight(const Vector3& direction, const Vector3& ambient, 
      const Vector3& diffuse, const Vector3& specular);
    ~SceneDirLight();

    virtual void VRender(Scene* pScene);
};

//
//  class ScenePointLight
//

class ScenePointLight : public SceneLightNode
{
  public:
    f32   ConstantAtten;
    f32   LinearAtten;
    f32   QuadraticAtten;

    ScenePointLight();
    ~ScenePointLight();

    virtual void VRender(Scene* pScene);
};

//
//  class SceneSpotLight
//

class SceneSpotLight : public SceneLightNode
{
  public:
    Vector3       Direction;

    f32           CutOffAngle;
    f32           OuterCutOffAngle;

    f32           ConstantAtten;
    f32           LinearAtten;
    f32           QuadraticAtten;

    SceneSpotLight();
    ~SceneSpotLight();

    virtual void VRender(Scene* pScene);
};