#include "CubeMapCamera.h"

using namespace Scene::Components;

namespace Rendering
{

	CubMapCamera::CubMapCamera(glm::vec3 camPosition): BaseCamera()
	{
		setFieldOfView(90.0);
		setAspectRatio(1.0);
		position = camPosition;
		lookAt = camPosition + glm::vec3(1.0, 0.0, 0.0);
		updateMatrices();
	}


	void CubMapCamera::SetCameraToFace(int faceIndex)
	{

	}
}
