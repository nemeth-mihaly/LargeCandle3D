#include "LargeCandle3D/Graphics/SceneNodes.h"

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
  Color = glm::vec3(1.0f, 1.0f, 1.0f);
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
  g_pShader->SetUniform3f("u_ObjectColor", Color);
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