#pragma once
#include "Model.h"
#include<time.h>
#include <stdarg.h>
#include "../Texture.h"


namespace Rendering
{
	namespace Models
	{
		class Cube : public Models::Model
		{
		public:
			Cube();
			~Cube();

			void Create();
			virtual void Draw()
				override final;
			virtual void Update() override final;

		private:
			glm::vec3 rotation, rotation_speed;
			time_t timer;
			Texture m_texture;
		};
	}
}
