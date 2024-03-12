#include "LargeCandle3D/Graphics/Scene.h"

#include "LargeCandle3D/Applv/Application.h"

//-----------------------------------------------
//    Impl. of Scene class
//-----------------------------------------------

Scene::Scene()
{
  m_pRoot.reset(new SceneNode());

  pObjectA.reset(new SceneMeshNode(g_pApp->pCubeMesh));
  pObjectA->Position = glm::vec3(0.0f, 0.0f, 0.0f);
  pObjectA->Color = glm::vec3(0.1f, 0.4f, 0.1f);
  m_pRoot->VAddChild(pObjectA);

  pLight.reset(new SceneMeshNode(g_pApp->pCubeMesh));
  pLight->bIsLightSource = true;
  pLight->Position = glm::vec3(1.2f, 1.0f, 2.0f);
  pLight->Scale = glm::vec3(0.1f, 0.1f, 0.1f);
  m_pRoot->VAddChild(pLight);
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

    g_pShader->SetUniform3f("u_LightSourcePos", pLight->Position);
    g_pShader->SetUniform3f("u_LightSourceColor", pLight->Color);
    
    g_pShader->SetUniform3f("u_ViewPos", pCamera->GetPosition());

    m_pRoot->VPreRender();

      m_pRoot->VRender();
      m_pRoot->VRenderChild();

    m_pRoot->VPostRender();
  }
}