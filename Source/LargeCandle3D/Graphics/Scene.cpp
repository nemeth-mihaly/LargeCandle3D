#include "LargeCandle3D/Graphics/Scene.h"

#include "LargeCandle3D/Applv/Application.h"

//-----------------------------------------------
//    Impl. of Scene class
//-----------------------------------------------

Scene::Scene()
{
  m_pRoot.reset(new SceneNode());

    m_pNodeA.reset(new SceneMeshNode(g_pApp->pMesh));
    
    {
      m_pNodeA->Position = glm::vec3(-5.0f, 0.0f, 0.0f);
      
      m_pNodeA->Color = glm::vec3(0.3f, 0.7f, 0.3f);
    }

    m_pRoot->VAddChild(m_pNodeA);

      m_pNodeB.reset(new SceneMeshNode(g_pApp->pMesh));
      
      {
        m_pNodeB->Position = glm::vec3(5.0f, 0.0f, 0.0f);

        m_pNodeB->Color = glm::vec3(0.1f, 0.1f, 0.7f);
      }

      m_pNodeA->VAddChild(m_pNodeB);

    m_pNodeC.reset(new SceneMeshNode(g_pApp->pMesh)); 
    
    {
      m_pNodeC->Position = glm::vec3(2.5f, 2.5f, 2.5f);
      m_pNodeC->Scale = glm::vec3(0.2f, 0.2f, 0.2f);

      m_pNodeC->bIsLightSource = true;
    }

    m_pRoot->VAddChild(m_pNodeC);
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

    g_pShader->SetUniform3f("u_LightSourcePos", m_pNodeC->Position);
    g_pShader->SetUniform3f("u_LightSourceColor", m_pNodeC->Color);
    
    g_pShader->SetUniform3f("u_ViewPos", pCamera->GetPosition());

    m_pRoot->VPreRender();

      m_pRoot->VRender();
      m_pRoot->VRenderChild();

    m_pRoot->VPostRender();
  }
}