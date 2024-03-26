#include "LargeCandle3D/Graphics/Scene.hpp"

#include <string>
#include "LargeCandle3D/Applv/Application.hpp"
#include "Maths/Matrix.hpp"

/*-------------------------------------------------------------------------
 *  Scene.cpp
 *-----------------------------------------------------------------------*/

/*
 *  Impl. of Scene
 */

Scene::Scene()
{
  m_pLightManager = new LightManager();

  m_pRoot.reset(new SceneNode());

  m_pCrates[0].reset(new SceneMeshNode(g_pApp->m_pCubeMesh));
  m_pRoot->VAddChild(m_pCrates[0]);
}

Scene::~Scene()
{
  if (m_pLightManager)
    delete m_pLightManager;
}

void Scene::OnUpdate(float deltaTime)
{
  m_pRoot->VOnUpdate(deltaTime);
}

void Scene::OnRender()
{
  if (m_pRoot && m_pCamera)
  {
    g_pShader->Use();

    //m_pLightManager->CalcLighting(this);

//    for (i32 i = 0; i < 4; i++)
//    {
//      g_pShader->SetUniform3f(std::string("u_PointLights[" + std::to_string(i) + "].Position").c_str(), pointLightPositions[i]);
//      g_pShader->SetUniform3f(std::string("u_PointLights[" + std::to_string(i) + "].Ambient").c_str(), glm::vec3(0.05f, 0.05f, 0.05f));
//      g_pShader->SetUniform3f(std::string("u_PointLights[" + std::to_string(i) + "].Diffuse").c_str(), glm::vec3(0.4f, 0.4f, 0.4f));
//      g_pShader->SetUniform3f(std::string("u_PointLights[" + std::to_string(i) + "].Specular").c_str(), glm::vec3(0.5f, 0.5f, 0.5f));
//      g_pShader->SetUniform1f(std::string("u_PointLights[" + std::to_string(i) + "].Constant").c_str(), 1.0f);
//      g_pShader->SetUniform1f(std::string("u_PointLights[" + std::to_string(i) + "].Linear").c_str(), 0.09f);
//      g_pShader->SetUniform1f(std::string("u_PointLights[" + std::to_string(i) + "].Quadratic").c_str(), 0.032f);
//    }

//    g_pShader->SetUniform3f("u_ViewPos", pCamera->GetPosition());

    m_pRoot->VPreRender();
    m_pRoot->VRender(this);
    m_pRoot->VRenderChild(this);
    m_pRoot->VPostRender();
  }
}