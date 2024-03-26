#include "LargeCandle3D/Graphics/SceneNodes.hpp"

#include <stdio.h>
#include "LargeCandle3D/Applv/Application.hpp"
#include "LargeCandle3D/Graphics/Scene.hpp"
#include "LargeCandle3D/Graphics/CameraController.hpp"

/*-------------------------------------------------------------------------
 *  SceneNodes.cpp
 *-----------------------------------------------------------------------*/

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

/*
 *  Impl. of SceneNode
 */

SceneNode::SceneNode()
{
  m_pParent = NULL;
  Color = Vector3(1.0f);
  Size = Vector3(0.2f);
  bIsLightSource = false;

  //Rotation = 0.0f;
}

SceneNode::~SceneNode()
{
}

void SceneNode::VOnUpdate(float deltaTime)
{
  for (size_t i = 0; i < m_Childs.size(); i++)
  {
    std::shared_ptr<ISceneNode>& child = m_Childs[i];
    child->VOnUpdate(deltaTime);
  }
}

void SceneNode::VPreRender()
{
  Transform = Translate(Position) 
    * Scale(Size);

  if (m_pParent)
  {
    //Transform *= m_pParent->Transform;
  }
}

void SceneNode::VRender(Scene* pScene)
{
}

void SceneNode::VRenderChild(Scene* pScene)
{
  for (size_t i = 0; i < m_Childs.size(); i++)
  {
    std::shared_ptr<ISceneNode>& child = m_Childs[i];

    child->VPreRender();

      child->VRender(pScene);
      child->VRenderChild(pScene);

    child->VPostRender();
  }
}

void SceneNode::VPostRender()
{
}

void SceneNode::VAddChild(const std::shared_ptr<ISceneNode>& pChild)
{
  m_Childs.push_back(pChild);
  std::static_pointer_cast<SceneNode>(pChild)->m_pParent = this;
}

void SceneNode::VRemoveChild()
{
}

/*
 *  Impl. of SceneMeshNode
 */

SceneMeshNode::SceneMeshNode(const std::shared_ptr<Mesh>& pMesh)
  : m_pMesh(pMesh)
{
}

SceneMeshNode::~SceneMeshNode()
{
}

void SceneMeshNode::VRender(Scene* pScene)
{
  g_pShader->SetUniformMat4x4("u_ViewProjection", pScene->GetCamera()->GetViewProjection().Data);

  g_pShader->SetUniformMat4x4("u_Model", Transform.Data);

  //g_pShader->SetUniformBool("u_bIsLightSource", bIsLightSource);

  g_pShader->SetUniform3f("u_Color", Color);

 // g_pShader->SetUniform3f("u_Material.Ambient", Material.Ambient);
 // g_pShader->SetUniform3f("u_Material.Diffuse", Material.Diffuse);
 // g_pShader->SetUniform3f("u_Material.Specular", Material.Specular);

//  if (Material.Diffuse && Material.Specular && Material.Emission)
//  {
//    g_pShader->SetUniform1i("u_Material.Diffuse", 0);
//    Material.Diffuse->Bind(0);
//
//    g_pShader->SetUniform1i("u_Material.Specular", 1);
//    Material.Specular->Bind(1);
//
//    g_pShader->SetUniform1i("u_Material.Emission", 2);
//    Material.Emission->Bind(2);
//  }

  g_pShader->SetUniform1f("u_Material.Shininess", Material.Shininess);

  m_pMesh->OnRender();
}

/*
 *  Impl. of SceneLightNode
 */

SceneLightNode::SceneLightNode()
{
}

SceneLightNode::~SceneLightNode()
{
}

//SceneDirLight::SceneDirLight(const Vector3& direction, const Vector3& ambient, 
//      const Vector3& diffuse, const Vector3& specular)
//{
//  Direction = direction;
//
//  Ambient = ambient;
//  Diffuse = diffuse;
//  Specular = specular;
//}
//
//SceneDirLight::~SceneDirLight()
//{
//}
//
//void SceneDirLight::VRender(Scene* pScene)
//{
//  g_pShader->SetUniform3f("u_DirLight.Direction", Direction);
//  g_pShader->SetUniform3f("u_DirLight.Ambient", Ambient);
//  g_pShader->SetUniform3f("u_DirLight.Diffuse", Diffuse);
//  g_pShader->SetUniform3f("u_DirLight.Specular", Specular);
//}
//
//ScenePointLight::ScenePointLight()
//{
//}
//
//ScenePointLight::~ScenePointLight()
//{
//}
//
//void ScenePointLight::VRender(Scene* pScene)
//{
//}
//
//SceneSpotLight::SceneSpotLight()
//{
//}
//
//SceneSpotLight::~SceneSpotLight()
//{
//}
//
//void SceneSpotLight::VRender(Scene* pScene)
//{
//  //g_pShader->SetUniform3f("u_SpotLight.Position", pScene->pCamera->GetPosition());
//  //g_pShader->SetUniform3f("u_SpotLight.Direction", pScene->pCamera->GetDirection());
//  //g_pShader->SetUniform1f("u_SpotLight.CutOff", glm::cos(glm::radians(12.5f)));
//  //g_pShader->SetUniform1f("u_SpotLight.OuterCutOff", glm::cos(glm::radians(17.5f)));
//  //g_pShader->SetUniform3f("u_SpotLight.Ambient", glm::vec3(0.05f, 0.05f, 0.05f));
//  //g_pShader->SetUniform3f("u_SpotLight.Diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
//  //g_pShader->SetUniform3f("u_SpotLight.Specular", glm::vec3(0.5f, 0.5f, 0.5f));
//  //g_pShader->SetUniform1f("u_SpotLight.Constant", 1.0f);
//  //g_pShader->SetUniform1f("u_SpotLight.Linear", 0.09f);
//  //g_pShader->SetUniform1f("u_SpotLight.Quadratic", 0.032f);
//}

/*
 *  Impl. of CameraNode
 */

CameraNode::CameraNode() 
{
  Position.Z = 5.0f;
  m_Orientation.Z = -1.0f;
}

Matrix4x4 CameraNode::GetViewProjection()
{
  m_Projection = Perspective(glm::radians(45.0f), 1280.0f, 720.0f, 0.01f, 100.0f);
  m_View = LookAt(Position, (Position + m_Orientation), Vector3(0.0f, 1.0f, 0.0f));
  
  return m_Projection * m_View; 
}

#pragma GCC diagnostic pop