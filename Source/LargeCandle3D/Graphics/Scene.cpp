#include "LargeCandle3D/Graphics/Scene.h"

#include "LargeCandle3D/Applv/Application.h"

//-----------------------------------------------
//    Impl. of SceneNode class
//-----------------------------------------------

SceneNode::SceneNode()
{
  Transform = glm::mat4(1.0f);
}

SceneNode::~SceneNode()
{
}

void SceneNode::VPreRender()
{
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
  Position = glm::vec3(0.0f, 0.0f, 0.0f);
}

SceneMeshNode::~SceneMeshNode()
{
}

void SceneMeshNode::VRender()
{
  Transform = glm::translate(glm::mat4(1.0f), Position);
  Transform *= m_pParent->Transform;

  g_pShader->SetUniformMat4x4("u_Model", Transform);

  m_pMesh->OnRender();
}