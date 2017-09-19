#include "CubeMapCamera.h"

using namespace Scene::Components;

namespace Rendering
{

	CubeMapCamera::CubeMapCamera(glm::vec3 camPosition): BaseCamera()
	{
		setFieldOfView(90.0);
		setAspectRatio(1.0);
		position = camPosition;
		lookAt = camPosition + glm::vec3(1.0, 0.0, 0.0);
		updateMatrices();
	}


	void CubeMapCamera::SetCameraToFace(int faceIndex)
	{
		glm::vec3 camPosition = getPosition();
		switch (faceIndex)
		{
		case 0:
			setUp(glm::vec3(0.0, 1.0, 0.0));
			setLookAt(camPosition + glm::vec3(1.0, 0.0, 0.0));
			break;
		case 1:
			setUp(glm::vec3(0.0, 1.0, 0.0));
			setLookAt(camPosition + glm::vec3(-1.0, 0.0, 0.0));
			break;
		case 2:
			setUp(glm::vec3(0.0, 0.0, -1.0));
			setLookAt(camPosition + glm::vec3(0.0, 1.0, 0.0));
			break;
		case 3:
			setUp(glm::vec3(0.0, 0.0, 1.0));
			setLookAt(camPosition + glm::vec3(0.0, -1.0, 0.0));
			break;
		case 4:
			setUp(glm::vec3(0.0, 1.0, 0.0));
			setLookAt(camPosition + glm::vec3(0.0, 0.0, 1.0));
			break;
		case 5:
			setUp(glm::vec3(0.0, 1.0, 0.0));
			setLookAt(camPosition + glm::vec3(0.0, 0.0, -1.0));
			break;
		}


	}
}
