#pragma once
#include "ShaderManager.h"
#include "ModelsManager.h"
#include "../Core/Init/IListener.h"
#include "../Rendering/Camera.h"
#include "../Rendering/Lighting.h"
namespace Managers
{
	class SceneManager : public Core::IListener

	{
	public:
		SceneManager();
		~SceneManager();

		virtual void NotifyBeginFrame();
		virtual void NotifyDisplayFrame();
		virtual void NotifyEndFrame();
		virtual void NotifyReshape(int width, int height, int previos_width, int previous_height);

		void addPointLight(PointLight light);
		void addSpotLight(SpotLight light);
		void addDirectionalLight(DirectionalLight light);

	private:
		Managers::ShaderManager*		shaderManager;
		Managers::ModelsManager*		modelsManager;
		Camera*							m_activeCamera;
		std::vector<PointLight>			m_pointLights;
		std::vector<SpotLight>			m_spotLights;
		std::vector<DirectionalLight>	m_directionalLights;
	};

}