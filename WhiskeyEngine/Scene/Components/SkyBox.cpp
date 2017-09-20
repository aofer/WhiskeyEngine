#include "Skybox.h"

using namespace Rendering;

namespace Scene
{
	namespace Components
	{
		SkyBox::SkyBox(const Rendering::FPSCamera* pCamera)
		{
			m_pCamera = pCamera;
		}

		SkyBox::~SkyBox()
		{

		}

		const FamilyType SkyBox::GetFamilyType()
		{
			return FamilyType::RENDERING;
		}

		bool SkyBox::Init(const std::string& Dir,
			const std::string& PosXFilename,
			const std::string& NegXFilename,
			const std::string& PosYFilename,
			const std::string& NegYFilename,
			const std::string& PosZFilename,
			const std::string& NegZFilename)
		{
			m_pCubeMapTexture = new CubeMapTexture(Dir, PosXFilename, NegXFilename, PosYFilename, NegYFilename, PosZFilename, NegZFilename);
			m_skyboxTech = new SkyboxTechnique();

			if (!m_skyboxTech->Init())
			{
				printf("Error initializing the skybox technique\n");
				return false;
			}
			m_skyboxTech->Enable();
			m_skyboxTech->SetTextureUnit(0);

			if (!m_pCubeMapTexture->Load()) {
				return false;
			}

			m_pMesh = new Models::Mesh();
			m_pMesh->Create("Assets\\sphere.obj");
			return true;
		}

		void SkyBox::Render(const glm::mat4& modelMatrix)
		{
			m_skyboxTech->Enable();
			GLint OldCullFaceMode;
			glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
			GLint OldDepthFuncMode;
			glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);

			glCullFace(GL_FRONT);
			glDepthFunc(GL_LEQUAL);

			m_skyboxTech->SetWVP( m_pCamera->getProjection() * m_pCamera->getView() * modelMatrix/*m_pCamera->getProjection() * m_pCamera->getView()*/);
			m_pCubeMapTexture->Bind(GL_TEXTURE0);
			m_pMesh->Draw();

			glCullFace(OldCullFaceMode);
			glDepthFunc(OldDepthFuncMode);

		}

		void SkyBox::Update(float dt)
		{

		}

	}
}