#pragma once
#include <glm/glm.hpp>
#include "BaseCamera.h"
/*
This class represents a basic camera with all of its camera controls
*/
namespace Rendering
{
	class CubMapCamera : public Rendering::BaseCamera{
	private:


	public:
	
		CubMapCamera(glm::vec3 camPosition);

		void SetCameraToFace(int faceIndex);

		//virtual void Update(float dt);

	};

}
