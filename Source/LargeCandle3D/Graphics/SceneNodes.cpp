#include "LargeCandle3D/Graphics/SceneNodes.h"

#include <stdio.h>

#include "LargeCandle3D/Applv/Application.h"

#include "LargeCandle3D/Graphics/CameraController.h"

//-----------------------------------------------
//    Impl. of SceneNode class
//-----------------------------------------------

SceneNode::SceneNode()
{
  m_pParent = NULL;

  Position = glm::vec3(0.0f, 0.0f, 0.0f);
  Scale = glm::vec3(1.0f, 1.0f, 1.0f);

  Transform = glm::mat4(1.0f);

  bIsLightSource = false;
}

SceneNode::~SceneNode()
{
}

void SceneNode::VPreRender()
{
  Transform = glm::translate(glm::mat4(1.0f), Position)
    * glm::scale(glm::mat4(1.0f), Scale);

  if (m_pParent)
    Transform *= m_pParent->Transform;

  g_pShader->SetUniformMat4x4("u_Model", Transform);

  g_pShader->SetUniformBool("u_bIsLightSource", bIsLightSource);

  //g_pShader->SetUniform3f("u_Material.Ambient", Material.Ambient);
  //g_pShader->SetUniform3f("u_Material.Diffuse", Material.Diffuse);
  //g_pShader->SetUniform3f("u_Material.Specular", Material.Specular);

  if (Material.Diffuse && Material.Specular && Material.Emission)
  {
    g_pShader->SetUniform1i("u_Material.Diffuse", 0);
    Material.Diffuse->Bind(0);

    g_pShader->SetUniform1i("u_Material.Specular", 1);
    Material.Specular->Bind(1);

    g_pShader->SetUniform1i("u_Material.Emission", 2);
    Material.Emission->Bind(2);
  }

  g_pShader->SetUniform1f("u_Material.Shininess", Material.Shininess);
}

void SceneNode::VRender()
{
}

void SceneNode::VRenderChild()
{
  for (usize i = 0; i < m_Childs.size(); i++)
  {
    auto child = m_Childs[i];

    child->VPreRender();

      child->VRender();
      child->VRenderChild();

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

void SceneMeshNode::VRender()
{
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