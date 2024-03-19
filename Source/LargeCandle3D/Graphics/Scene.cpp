#include "LargeCandle3D/Graphics/Scene.h"

#include <string>

#include "LargeCandle3D/Applv/Application.h"

Vector3 cratePositions[] = 
{
  Vector3( 0.0f,  0.0f,  0.0f),
  Vector3( 2.0f,  5.0f, -15.0f),
  Vector3(-1.5f, -2.2f, -2.5f),
  Vector3(-3.8f, -2.0f, -12.3f),
  Vector3( 2.4f, -0.4f, -3.5f),
  Vector3(-1.7f,  3.0f, -7.5f),
  Vector3( 1.3f, -2.0f, -2.5f),
  Vector3( 1.5f,  2.0f, -2.5f),
  Vector3( 1.5f,  0.2f, -1.5f),
  Vector3(-1.3f,  1.0f, -1.5f)
};

Vector3 pointLightPositions[] =
{
  Vector3( 0.7f,  0.2f,  2.0f),
  Vector3( 2.3f, -3.3f, -4.0f),
  Vector3(-4.0f,  2.0f, -12.0f),
  Vector3( 0.0f,  0.0f, -3.0f)
};

//-----------------------------------------------
//    Impl. of Scene class
//-----------------------------------------------

Scene::Scene()
{
  m_pLightManager = new LightManager();

  m_pRoot.reset(new SceneNode());

  for (int i = 0; i < 10; i++)
  {
    pCrates[i].reset(new SceneMeshNode(g_pApp->pCubeMesh));
    pCrates[i]->Position.X = cratePositions[i].X;
    pCrates[i]->Position.Y = cratePositions[i].Y;
    pCrates[i]->Position.Z = cratePositions[i].Z;

    pCrates[i]->bIsLightSource = false;

    //pCrates[i]->Material.Diffuse = g_pTexture;
    //pCrates[i]->Material.Specular = g_pTexture;
    //pCrates[i]->Material.Emission = g_pTexture;
    //pCrates[i]->Material.Shininess = 32.0f;

    m_pRoot->VAddChild(pCrates[i]);
  }

//  pDirLight.reset(new SceneDirLight({-0.2f, -1.0f, -0.3f}, 
//    {0.05f, 0.05f, 0.05f}, {0.2f, 0.2f, 0.2f}, {0.25f, 0.25f, 0.25f}));
//  m_pRoot->VAddChild(pDirLight);
//  //m_Lights.push_back(pDirLight);
//
//  pSpotLight.reset(new SceneSpotLight());
//  m_pRoot->VAddChild(pSpotLight);
//  //m_Lights.push_back(pSpotLight);

//  for (int i = 0; i < 4; i++)
//  {
//    pPointLights[i].reset(new SceneMeshNode(g_pApp->pCubeMesh));
//    pPointLights[i]->Position = pointLightPositions[i];
//    pPointLights[i]->Scale = glm::vec3(0.2f, 0.2f, 0.2f);
//    pPointLights[i]->bIsLightSource = true;
//    pPointLights[i]->Material.Diffuse = g_pTextureDiff;
//    pPointLights[i]->Material.Specular = g_pTextureSpec;
//    pPointLights[i]->Material.Emission = g_pTextureEmission;
//    pPointLights[i]->Material.Shininess = 32.0f;
//    m_pRoot->VAddChild(pPointLights[i]);
//  }
}

Scene::~Scene()
{
  if (m_pLightManager)
    delete m_pLightManager;
}

void Scene::OnRender()
{
  if (m_pRoot && pCamera)
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

    g_pShader->SetUniformMat4x4("u_Projection", pCamera->GetProjection());
    g_pShader->SetUniformMat4x4("u_View", pCamera->GetView());

//    g_pShader->SetUniform3f("u_ViewPos", pCamera->GetPosition());

    m_pRoot->VPreRender();

      m_pRoot->VRender(this);
      m_pRoot->VRenderChild(this);

    m_pRoot->VPostRender();
  }
}