#pragma once

#include <stdint.h>
#include <vector>
#include <list>
#include <memory>
#include "LargeCandle3D/Graphics/Mesh.hpp"
#include "LargeCandle3D/Graphics/Material.hpp"
#include "Maths/Matrix.hpp"

/*-------------------------------------------------------------------------
 *  SceneNodes.hpp
 *-----------------------------------------------------------------------*/

class Scene;
class SceneLightNode;

using LightList = std::list<std::shared_ptr<SceneLightNode>>;

/*
 *  ISceneNode
 */
class ISceneNode
{
  public:
    virtual ~ISceneNode() = default;

    virtual void VOnUpdate(float deltaTime) = 0;

    virtual void VPreRender() = 0;
    virtual void VRender(Scene* pScene) = 0;
    virtual void VRenderChild(Scene* pScene) = 0;
    virtual void VPostRender() = 0;

    virtual void VAddChild(const std::shared_ptr<ISceneNode>& pChild) = 0;
    virtual void VRemoveChild() = 0;
};

/*
 *  SceneNode
 */
class SceneNode : public ISceneNode
{
  protected:
    SceneNode* m_pParent;
    std::vector<std::shared_ptr<ISceneNode>> m_Childs;

  public:
    Vector3 Color;

    Vector3 Position;
    Vector3 Rotation;
    Vector3 Size;

    Matrix4x4 Transform;

    bool bIsLightSource;
    Material Material;

    SceneNode();
    virtual ~SceneNode();

    virtual void VOnUpdate(float deltaTime);

    virtual void VPreRender();
    virtual void VRender(Scene* pScene);
    virtual void VRenderChild(Scene* pScene);
    virtual void VPostRender();

    virtual void VAddChild(const std::shared_ptr<ISceneNode>& pChild);
    virtual void VRemoveChild();
};

/*
 *  SceneMeshNode
 */
class SceneMeshNode : public SceneNode
{
  public:
    SceneMeshNode(const std::shared_ptr<Mesh>& pMesh);
    ~SceneMeshNode();

    virtual void VRender(Scene* pScene);

  private:
    std::shared_ptr<Mesh> m_pMesh;
};

/*
 *  SceneLightNode
 */
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
//    float   ConstantAtten;
//    float   LinearAtten;
//    float   QuadraticAtten;
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
//    float           CutOffAngle;
//    float           OuterCutOffAngle;
//
//    float           ConstantAtten;
//    float           LinearAtten;
//    float           QuadraticAtten;
//
//    SceneSpotLight();
//    ~SceneSpotLight();
//
//    virtual void VRender(Scene* pScene);
//};

/*
 *  CameraNode
 */
class CameraNode : public SceneNode
{
  friend class CameraController;

  public:
    CameraNode();
    
    Matrix4x4 GetViewProjection();

    Matrix4x4     m_Projection;
    Matrix4x4     m_View;

    Vector3       m_Orientation;
};