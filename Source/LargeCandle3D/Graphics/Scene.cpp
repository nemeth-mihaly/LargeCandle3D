#include "LargeCandle3D/Graphics/Scene.h"

#include "LargeCandle3D/Applv/Application.h"

//-----------------------------------------------
//    Impl. of Scene class
//-----------------------------------------------

Scene::Scene()
{
  m_pRoot.reset(new SceneNode());

  m_pPlatform.reset(new SceneMeshNode(g_pApp->pCubeMesh));
  m_pPlatform->Scale = glm::vec3(50.0f, 0.1f, 50.0f);
  m_pPlatform->Color = glm::vec3(0.1f, 0.2f, 0.1f);
  m_pRoot->VAddChild(m_pPlatform);

  m_pStaticObjectA.reset(new SceneMeshNode(g_pApp->pCubeMesh));
  m_pStaticObjectA->Position = glm::vec3(0.0f, 1.0f, 0.0f);
  m_pStaticObjectA->Color = glm::vec3(0.1f, 0.4f, 0.1f);
  m_pRoot->VAddChild(m_pStaticObjectA);

  m_pLight.reset(new SceneMeshNode(g_pApp->pCubeMesh));
  m_pLight->bIsLightSource = true;
  m_pLight->Position = glm::vec3(1.2f, 2.2f, 1.2f);
  m_pLight->Scale = glm::vec3(0.1f, 0.1f, 0.1f);
  m_pRoot->VAddChild(m_pLight);
}

Scene::~Scene()
{
}

void Scene::OnRender()
{
  if (m_pRoot && pCamera)
  {
    g_pShader->Use();
    g_pShader->SetUniformMat4x4("u_Projection", pCamera->GetProjection());
    g_pShader->SetUniformMat4x4("u_View", pCamera->GetView());

    g_pShader->SetUniform3f("u_LightSourcePos", m_pLight->Position);
    g_pShader->SetUniform3f("u_LightSourceColor", m_pLight->Color);
    
    g_pShader->SetUniform3f("u_ViewPos", pCamera->GetPosition());

    m_pRoot->VPreRender();

      m_pRoot->VRender();
      m_pRoot->VRenderChild();

    m_pRoot->VPostRender();
  }
}