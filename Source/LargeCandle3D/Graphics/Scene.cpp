#include "LargeCandle3D/Graphics/Scene.h"

#include <string>

#include "LargeCandle3D/Applv/Application.h"

Scene::Scene()
{
  m_pLightManager = new LightManager();

  //m_pCameraNode.reset(new CameraNode());
  //m_pRoot->VAddChild(m_pCameraNode);

  m_pRoot.reset(new SceneNode());

  m_pCrates[0].reset(new SceneMeshNode(g_pApp->m_pCubeMesh));
  m_pCrates[0]->Position = glm::vec3(0.0f, 0.0f, 0.0f);

  //m_pCrates[1].reset(new SceneMeshNode(g_pApp->m_pCubeMesh));
  // m_pCrates[1]->Position.X -= 0.5f;

  //m_pCrates[2].reset(new SceneMeshNode(g_pApp->m_pCubeMesh));
  //m_pCrates[2]->Position.x += 2.0f;


  m_pRoot->VAddChild(m_pCrates[0]);
  //m_pRoot->VAddChild(m_pCrates[1]);
  //m_pRoot->VAddChild(m_pCrates[2]);
}

Scene::~Scene()
{
  if (m_pLightManager)
    delete m_pLightManager;
}

void Scene::OnUpdate(f32 deltaTime)
{
  m_pRoot->VOnUpdate(deltaTime);
}

void Scene::OnRender()
{
  if (m_pRoot && m_pCameraNode)
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

    //g_pShader->SetUniformMat4x4("u_Projection", pCamera->GetProjection());
    //g_pShader->SetUniformMat4x4("u_View", pCamera->GetView());

#if USE_GLM

    m_pCameraNode->m_Projection = glm::perspective(glm::radians(45.0f), (1280.0f / 720.0f), 0.01f, 1000.0f);
    g_pShader->SetUniformMat4x4("u_Projection", m_pCameraNode->m_Projection);

    m_pCameraNode->m_View = glm::lookAt(m_pCameraNode->Position, 
      (m_pCameraNode->Position + m_pCameraNode->m_Forward), glm::vec3(0.0f, 1.0f, 0.0f));

    g_pShader->SetUniformMat4x4("u_View", m_pCameraNode->m_View);

#else

    m_pCameraNode->m_Projection = Matrix4x4::Perspective(Radians(45.0f), 1280.0f, 720.0f, 0.01f, 1000.0f);
    g_pShader->SetUniformMat4x4("u_Projection", m_pCameraNode->m_Projection);

    m_pCameraNode->m_View = Matrix4x4::LookAt(m_pCameraNode->Position, 
      (m_pCameraNode->Position + m_pCameraNode->m_Center), Vector3(0.0f, 1.0f, 0.0f));

    g_pShader->SetUniformMat4x4("u_View", m_pCameraNode->m_View);

#endif

//    g_pShader->SetUniform3f("u_ViewPos", pCamera->GetPosition());

    m_pRoot->VPreRender();
    m_pCameraNode->VPreRender();

      m_pCameraNode->VRender(this);
      m_pRoot->VRender(this);
      m_pRoot->VRenderChild(this);

    m_pRoot->VPostRender();
  }
}