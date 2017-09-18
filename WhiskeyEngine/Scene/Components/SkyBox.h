#pragma once
#include "../../Rendering/FPSCamera.h"
#include "../../Rendering/CubeMapTexture.h"
#include "../../Rendering/Models/Mesh.h"
#include "../../Rendering/SkyboxTechnique.h"
#include "GameComponent.h"

namespace Scene
{
	namespace Components
	{
		class SkyBox : public GameComponent
		{
		public:
			SkyBox(const Rendering::FPSCamera* pCamera);
			~SkyBox();

			virtual const FamilyType GetFamilyType();

			bool Init(const std::string& Dir,
				const std::string& PosXFilename,
				const std::string& NegXFilename,
				const std::string& PosYFilename,
				const std::string& NegYFilename,
				const std::string& PosZFilename,
				const std::string& NegZFilename);

			void Render(const glm::mat4& modelMatrix);
			virtual void Update(float dt);

		private:
			const Rendering::FPSCamera* m_pCamera;
			Rendering::CubeMapTexture* m_pCubeMapTexture;
			Rendering::Models::Mesh* m_pMesh;
			Rendering::SkyboxTechnique* m_skyboxTech;

		};
	}
}
