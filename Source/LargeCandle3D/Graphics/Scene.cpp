#include "LargeCandle3D/Graphics/Scene.h"

#include "LargeCandle3D/Applv/Application.h"

glm::vec3 cratePositions[] = 
{
  glm::vec3( 0.0f,  0.0f,  0.0f),
  glm::vec3( 2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3( 2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3( 1.3f, -2.0f, -2.5f),
  glm::vec3( 1.5f,  2.0f, -2.5f),
  glm::vec3( 1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 pointLightPositions[] =
{
  glm::vec3( 0.7f,  0.2f,  2.0f),
  glm::vec3( 2.3f, -3.3f, -4.0f),
  glm::vec3(-4.0f,  2.0f, -12.0f),
  glm::vec3( 0.0f,  0.0f, -3.0f)
};

//-----------------------------------------------
//    Impl. of Scene class
//-----------------------------------------------

Scene::Scene()
{
  m_pRoot.reset(new SceneNode());

  pFloor.reset(new SceneMeshNode(g_pApp->pPlaneMesh));
  pFloor->Position = glm::vec3(0.0f, -4.0f, 0.0f);
  pFloor->Scale = glm::vec3(10.0f, 1.0f, 10.0f);
  pFloor->bIsLightSource = false;
  pFloor->Material.Diffuse = g_pWoodFloor;
  pFloor->Material.Specular = g_pTexture;
  pFloor->Material.Emission = g_pTexture;
  pFloor->Material.Shininess = 32.0f;
  m_pRoot->VAddChild(pFloor);  

  for (int i = 0; i < 10; i++)
  {
    pCrates[i].reset(new SceneMeshNode(g_pApp->pCubeMesh));
    pCrates[i]->Position = cratePositions[i];
    pCrates[i]->Scale = glm::vec3(1.0f, 1.0f, 1.0f);
    pCrates[i]->bIsLightSource = false;
    pCrates[i]->Material.Diffuse = g_pTexture;
    pCrates[i]->Material.Specular = g_pTexture;
    pCrates[i]->Material.Emission = g_pTexture;
    pCrates[i]->Material.Shininess = 32.0f;
    m_pRoot->VAddChild(pCrates[i]);
  }

  for (int i = 0; i < 4; i++)
  {
    pPointLights[i].reset(new SceneMeshNode(g_pApp->pCubeMesh));
    pPointLights[i]->Position = pointLightPositions[i];
    pPointLights[i]->Scale = glm::vec3(0.2f, 0.2f, 0.2f);
    pPointLights[i]->bIsLightSource = true;
    pPointLights[i]->Material.Diffuse = g_pTextureDiff;
    pPointLights[i]->Material.Specular = g_pTextureSpec;
    pPointLights[i]->Material.Emission = g_pTextureEmission;
    pPointLights[i]->Material.Shininess = 32.0f;
    m_pRoot->VAddChild(pPointLights[i]);
  }
}

Scene::~Scene()
{
}

void Scene::OnRender()
{
  if (m_pRoot && pCamera)
  {
    g_pShader->Use();

    g_pShader->SetUniform3f("u_DirLight.Direction", glm::vec3(-0.2f, -1.0f, -0.3f));
    g_pShader->SetUniform3f("u_DirLight.Ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    g_pShader->SetUniform3f("u_DirLight.Diffuse", glm::vec3(0.2f, 0.2f, 0.2f));
    g_pShader->SetUniform3f("u_DirLight.Specular", glm::vec3(0.25f, 0.25f, 0.25f));

    g_pShader->SetUniform3f("u_PointLights[0].Position", pointLightPositions[0]);
    g_pShader->SetUniform3f("u_PointLights[0].Ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    g_pShader->SetUniform3f("u_PointLights[0].Diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    g_pShader->SetUniform3f("u_PointLights[0].Specular", glm::vec3(0.5f, 0.5f, 0.5f));
    g_pShader->SetUniform1f("u_PointLights[0].Constant", 1.0f);
    g_pShader->SetUniform1f("u_PointLights[0].Linear", 0.09f);
    g_pShader->SetUniform1f("u_PointLights[0].Quadratic", 0.032f);

    g_pShader->SetUniform3f("u_PointLights[1].Position", pointLightPositions[1]);
    g_pShader->SetUniform3f("u_PointLights[1].Ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    g_pShader->SetUniform3f("u_PointLights[1].Diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    g_pShader->SetUniform3f("u_PointLights[1].Specular", glm::vec3(0.5f, 0.5f, 0.5f));
    g_pShader->SetUniform1f("u_PointLights[1].Constant", 1.0f);
    g_pShader->SetUniform1f("u_PointLights[1].Linear", 0.09f);
    g_pShader->SetUniform1f("u_PointLights[1].Quadratic", 0.032f);

    g_pShader->SetUniform3f("u_PointLights[2].Position", pointLightPositions[2]);
    g_pShader->SetUniform3f("u_PointLights[2].Ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    g_pShader->SetUniform3f("u_PointLights[2].Diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    g_pShader->SetUniform3f("u_PointLights[2].Specular", glm::vec3(0.5f, 0.5f, 0.5f));
    g_pShader->SetUniform1f("u_PointLights[2].Constant", 1.0f);
    g_pShader->SetUniform1f("u_PointLights[2].Linear", 0.09f);
    g_pShader->SetUniform1f("u_PointLights[2].Quadratic", 0.032f);

    g_pShader->SetUniform3f("u_PointLights[3].Position", pointLightPositions[3]);
    g_pShader->SetUniform3f("u_PointLights[3].Ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    g_pShader->SetUniform3f("u_PointLights[3].Diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    g_pShader->SetUniform3f("u_PointLights[3].Specular", glm::vec3(0.5f, 0.5f, 0.5f));
    g_pShader->SetUniform1f("u_PointLights[3].Constant", 1.0f);
    g_pShader->SetUniform1f("u_PointLights[3].Linear", 0.09f);
    g_pShader->SetUniform1f("u_PointLights[3].Quadratic", 0.032f);

    g_pShader->SetUniform3f("u_SpotLight.Position", pCamera->GetPosition());
    g_pShader->SetUniform3f("u_SpotLight.Direction", pCamera->GetDirection());
    g_pShader->SetUniform1f("u_SpotLight.CutOff", glm::cos(glm::radians(12.5f)));
    g_pShader->SetUniform1f("u_SpotLight.OuterCutOff", glm::cos(glm::radians(17.5f)));
    g_pShader->SetUniform3f("u_SpotLight.Ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    g_pShader->SetUniform3f("u_SpotLight.Diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    g_pShader->SetUniform3f("u_SpotLight.Specular", glm::vec3(0.5f, 0.5f, 0.5f));
    g_pShader->SetUniform1f("u_SpotLight.Constant", 1.0f);
    g_pShader->SetUniform1f("u_SpotLight.Linear", 0.09f);
    g_pShader->SetUniform1f("u_SpotLight.Quadratic", 0.032f);

    g_pShader->SetUniformMat4x4("u_Projection", pCamera->GetProjection());
    g_pShader->SetUniformMat4x4("u_View", pCamera->GetView());

    g_pShader->SetUniform3f("u_ViewPos", pCamera->GetPosition());

    m_pRoot->VPreRender();

      m_pRoot->VRender();
      m_pRoot->VRenderChild();

    m_pRoot->VPostRender();
  }
}