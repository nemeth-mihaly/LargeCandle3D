#pragma once

#include <vector>
#include <list>
#include <memory>

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Graphics/Geometry.h"
#include "LargeCandle3D/Graphics/Mesh.h"
#include "LargeCandle3D/Graphics/Material.h"

class Scene;
class SceneLightNode;

using LightList = std::list<std::shared_ptr<SceneLightNode>>;

class ISceneNode
{
  public:
    virtual ~ISceneNode() = default;

    virtual void VOnUpdate(f32 deltaTime) = 0;

    virtual void VPreRender() = 0;
    virtual void VRender(Scene* pScene) = 0;
    virtual void VRenderChild(Scene* pScene) = 0;
    virtual void VPostRender() = 0;

    virtual void VAddChild(const std::shared_ptr<ISceneNode>& pChild) = 0;
    virtual void VRemoveChild() = 0;
};

class SceneNode : public ISceneNode
{
  protected:
    SceneNode* m_pParent;
    std::vector<std::shared_ptr<ISceneNode>> m_Childs;

  public:
#if USE_GLM
    glm::vec3 Color;

    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;

    glm::mat4 Transform;
#else
    Vector3 Color;

    Vector3 Position;
    Vector3 Rotation;
    Vector3 Scale;

    Matrix4x4 Transform;
#endif

    bool bIsLightSource;
    Material Material;

    SceneNode();
    virtual ~SceneNode();

    virtual void VOnUpdate(f32 deltaTime);

    virtual void VPreRender();
    virtual void VRender(Scene* pScene);
    virtual void VRenderChild(Scene* pScene);
    virtual void VPostRender();

    virtual void VAddChild(const std::shared_ptr<ISceneNode>& pChild);
    virtual void VRemoveChild();
};

class SceneMeshNode : public SceneNode
{
  public:
    SceneMeshNode(const std::shared_ptr<Mesh>& pMesh);
    ~SceneMeshNode();

    virtual void VRender(Scene* pScene);

  private:
    std::shared_ptr<Mesh> m_pMesh;
};

class SceneLightNode : public SceneNode
{
  public:
#if USE_GLM

    glm::vec3   Ambient;
    glm::vec3   Diffuse;
    glm::vec3   Specular;
    glm::vec3   Emissive;

#else

    Vector3   Ambient;
    Vector3   Diffuse;
    Vector3   Specular;
    Vector3   Emissive;

#endif

    SceneLightNode();
    ~SceneLightNode();
};

//class SceneDirLight : public SceneLightNode
//{
//  public:
//#if USE_GLM
//
//    glm::vec3   Direction;
//
//#else
//
//    Vector3   Direction;
//
//#endif
//
//    SceneDirLight(const Vector3& direction, const Vector3& ambient, 
//      const Vector3& diffuse, const Vector3& specular);
//    ~SceneDirLight();
//
//    virtual void VRender(Scene* pScene);
//};
//
//class ScenePointLight : public SceneLightNode
//{
//  public:
//    f32   ConstantAtten;
//    f32   LinearAtten;
//    f32   QuadraticAtten;
//
//    ScenePointLight();
//    ~ScenePointLight();
//
//    virtual void VRender(Scene* pScene);
//};
//
//class SceneSpotLight : public SceneLightNode
//{
//  public:
//    Vector3       Direction;
//
//    f32           CutOffAngle;
//    f32           OuterCutOffAngle;
//
//    f32           ConstantAtten;
//    f32           LinearAtten;
//    f32           QuadraticAtten;
//
//    SceneSpotLight();
//    ~SceneSpotLight();
//
//    virtual void VRender(Scene* pScene);
//};

class CameraNode : public SceneNode
{
  friend class CameraController;

  public:
    CameraNode() 
    {
      Position.z = 5.0f;
    }

    ~CameraNode() {}

    void VOnUpdate(f32 deltaTime)
    {

    }

    void VRender(Scene* pScene);

#if USE_GLM

    glm::mat4 m_Projection;
    glm::mat4 m_View;
    glm::vec3 m_Forward = glm::vec3(0.0f, 0.0f, -1.0f);

#else

    Matrix4x4 m_Projection;
    Matrix4x4 m_View;
    Vector3 m_Center;

#endif

};