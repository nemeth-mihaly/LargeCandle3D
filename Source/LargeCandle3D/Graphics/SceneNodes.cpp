#include "LargeCandle3D/Graphics/SceneNodes.h"

#include <stdio.h>

#include "LargeCandle3D/Applv/Application.h"

#include "LargeCandle3D/Graphics/Scene.h"
#include "LargeCandle3D/Graphics/CameraController.h"

//-----------------------------------------------
//    Impl. of SceneNode class
//-----------------------------------------------

SceneNode::SceneNode()
{
  m_pParent = NULL;

  Color = g_White;
  Size = Vector3(1.0f, 1.0f, 1.0f);

  bIsLightSource = false;
}

SceneNode::~SceneNode()
{
}

void SceneNode::VPreRender()
{
  Transform = Translate(Position);
  Transform = Transform.Multiply(Scale(Size));

  if (m_pParent)
    Transform = Transform.Multiply(m_pParent->Transform);
}

void SceneNode::VRender(Scene* pScene)
{
}

void SceneNode::VRenderChild(Scene* pScene)
{
  for (usize i = 0; i < m_Childs.size(); i++)
  {
    auto child = m_Childs[i];

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

//-----------------------------------------------
//    Impl. of SceneMeshNode class
//-----------------------------------------------

SceneMeshNode::SceneMeshNode(const std::shared_ptr<Mesh>& pMesh)
  : m_pMesh(pMesh)
{
}

SceneMeshNode::~SceneMeshNode()
{
}

void SceneMeshNode::VRender(Scene* pScene)
{
  g_pShader->SetUniformMat4x4("u_Model", Transform);

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

//-----------------------------------------------
//    Impl. of SceneLightNode class
//-----------------------------------------------

SceneLightNode::SceneLightNode()
{
}

SceneLightNode::~SceneLightNode()
{
}

//-----------------------------------------------
//    Impl. of SceneDirLight class
//-----------------------------------------------

SceneDirLight::SceneDirLight(const Vector3& direction, const Vector3& ambient, 
      const Vector3& diffuse, const Vector3& specular)
{
  Direction = direction;

  Ambient = ambient;
  Diffuse = diffuse;
  Specular = specular;
}

SceneDirLight::~SceneDirLight()
{
}

void SceneDirLight::VRender(Scene* pScene)
{
  g_pShader->SetUniform3f("u_DirLight.Direction", Direction);
  g_pShader->SetUniform3f("u_DirLight.Ambient", Ambient);
  g_pShader->SetUniform3f("u_DirLight.Diffuse", Diffuse);
  g_pShader->SetUniform3f("u_DirLight.Specular", Specular);
}

//-----------------------------------------------
//    Impl. of ScenePointLight class
//-----------------------------------------------

ScenePointLight::ScenePointLight()
{
}

ScenePointLight::~ScenePointLight()
{
}

void ScenePointLight::VRender(Scene* pScene)
{
}

//-----------------------------------------------
//    Impl. of SceneSpotLight class
//-----------------------------------------------

SceneSpotLight::SceneSpotLight()
{
}

SceneSpotLight::~SceneSpotLight()
{
}

void SceneSpotLight::VRender(Scene* pScene)
{
  //g_pShader->SetUniform3f("u_SpotLight.Position", pScene->pCamera->GetPosition());
  //g_pShader->SetUniform3f("u_SpotLight.Direction", pScene->pCamera->GetDirection());
  //g_pShader->SetUniform1f("u_SpotLight.CutOff", glm::cos(glm::radians(12.5f)));
  //g_pShader->SetUniform1f("u_SpotLight.OuterCutOff", glm::cos(glm::radians(17.5f)));
  //g_pShader->SetUniform3f("u_SpotLight.Ambient", glm::vec3(0.05f, 0.05f, 0.05f));
  //g_pShader->SetUniform3f("u_SpotLight.Diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
  //g_pShader->SetUniform3f("u_SpotLight.Specular", glm::vec3(0.5f, 0.5f, 0.5f));
  //g_pShader->SetUniform1f("u_SpotLight.Constant", 1.0f);
  //g_pShader->SetUniform1f("u_SpotLight.Linear", 0.09f);
  //g_pShader->SetUniform1f("u_SpotLight.Quadratic", 0.032f);
}