#include "SphericalHarmonicsScene.h"
#include "../Core/Init/Common.h"
#include "../Rendering/FPSCamera.h"
#include "../Rendering/Models/Mesh.h"
#include "../Rendering/Lighting.h"
#include "GameObject.h"
#include "../Managers/ModelsManager.h"
#include <memory>
#include <GLFW\glfw3.h> // for key enum
#include "../Managers/InputManager.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace Rendering;

const unsigned int CUBEMAP_SIZE = 1024;
const unsigned int MAX_BOUNCES = 3;

namespace Scene
{
	SphericalHarmonicsScene::SphericalHarmonicsScene() : GameScene(), m_numOfBounces(0)
	{
		Managers::InputManager::getInstance().AddInputListener(this);
	}
	SphericalHarmonicsScene::~SphericalHarmonicsScene()
	{
		delete m_cubeCam;
	}

	void SphericalHarmonicsScene::Init()
	{
		glm::vec3 camPos = glm::vec3(0.0, 5.0f, -13.0);
		m_pActiveCamera->setPosition(camPos);
		m_pActiveCamera->setLookAt(glm::vec3(0.0, 5.0, 0.0));

		glm::vec3 cubeMapCenter = glm::vec3(0.0, 5.0, 0.0);
		m_cubeCam = new CubeMapCamera(cubeMapCenter);

		m_shCoeff[0].resize(9);

		//int test = GLCheckError(); //TODO 

		if (!m_shTech.Init())
		{
			printf("Error initializing sh technique\n");
		}

		m_shTech.Enable();

		m_shTech.SetTextureUnit(0);


		SpotLight spotLights[1];
		spotLights[0].m_color = glm::vec3(1.0, 1.0, 1.0);
		spotLights[0].m_diffuseIntensity = 0.3f;
		spotLights[0].m_direction = glm::vec3(0.0, -1.0, 0.0);
		spotLights[0].Attenuation.Linear = 0.1f;
		spotLights[0].m_ambientIntensity = 0.0f;
		spotLights[0].m_cutoff = 25.5f;
		spotLights[0].m_position = glm::vec3(-2.0, 15.0, -2.0);

		m_shTech.SetSpotLights(1, spotLights);



		Models::Mesh* boxMesh = new Models::Mesh();
		boxMesh->Create("Assets\\box.obj");
		Models::Mesh* roomMesh = new Models::Mesh();
		roomMesh->Create("Assets\\room.obj");
		m_pModelsManager->AddModel("room", roomMesh);

		Scene::GameObject* room = new GameObject();
		room->SetModel(roomMesh);
		room->SetPosition(glm::vec3(0.0, 0.0, 0.0));
		room->SetScale(2.0f);
		m_gameObjectsFlat.push_back(room);


		m_shTech.SetDiffuseColor(glm::vec3(0.8, 0.8, 0.8));
		m_shTech.SetSpecularColor(glm::vec3(1.0, 1.0, 1.0));
		m_shTech.SetAmbientColor(glm::vec3(1.0, 1.0, 1.0));
		m_shTech.SetShininess(2);

		//Scene::GameObject* box2 = new GameObject();
		//box2->SetModel(boxMesh);
		//box2->SetPosition(glm::vec3(0.0, 3.4, 0.0));
		//box2->SetScale(0.8f);
		//m_gameObjectsFlat.push_back(box2);


		initEnvironmentMapTexture();
		initEnvironmentRendering();
		bakeSphericalHarmonics();
	}

	void SphericalHarmonicsScene::Update(float dt)
	{

	}

	void SphericalHarmonicsScene::sphericalHarmonicsFromTexture(GLuint cubeTexture,
		std::vector<glm::vec3> & output, const unsigned int order)
	{
		const uint sqOrder = order*order;

		// allocate memory for calculations
		output.resize(sqOrder);
		std::vector<float> resultR(sqOrder);
		std::vector<float> resultG(sqOrder);
		std::vector<float> resultB(sqOrder);

		// variables that describe current face of cube texture
		std::unique_ptr<GLubyte> data;
		GLint width, height;
		GLint internalFormat;
		GLint numComponents;

		// initialize values
		float fWt = 0.0f;
		for (uint i = 0; i < sqOrder; i++)
		{
			output[i].x = 0;
			output[i].y = 0;
			output[i].z = 0;
			resultR[i] = 0;
			resultG[i] = 0;
			resultB[i] = 0;
		}
		std::vector<float> shBuff(sqOrder);
		std::vector<float> shBuffB(sqOrder);

		// bind current texture
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture);
		// for each face of cube texture
		for (int face = 0; face < 6; face++)
		{
			// get width and height
			glGetTexLevelParameteriv(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, 0, GL_TEXTURE_WIDTH, &width);
			glGetTexLevelParameteriv(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, 0, GL_TEXTURE_HEIGHT, &height);

			if (width != height)
			{
				return;
			}

			// get format of data in texture
			glGetTexLevelParameteriv(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, 0,
				GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);

			// get data from texture
			if (internalFormat == GL_RGBA)
			{
				numComponents = 4;
				data = std::unique_ptr<GLubyte>(new GLubyte[numComponents * width * width]);
			}
			else if (internalFormat == GL_RGB)
			{
				numComponents = 3;
				data = std::unique_ptr<GLubyte>(new GLubyte[numComponents * width * width]);
			}
			else
			{
				return;
			}
			glGetTexImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, 0, internalFormat, GL_UNSIGNED_BYTE, data.get());

			// step between two texels for range [0, 1]
			float invWidth = 1.0f / float(width);
			// initial negative bound for range [-1, 1]
			float negativeBound = -1.0f + invWidth;
			// step between two texels for range [-1, 1]
			float invWidthBy2 = 2.0f / float(width);

			for (int y = 0; y < width; y++)
			{
				// texture coordinate V in range [-1 to 1]
				const float fV = negativeBound + float(y) * invWidthBy2;

				for (int x = 0; x < width; x++)
				{
					// texture coordinate U in range [-1 to 1]
					const float fU = negativeBound + float(x) * invWidthBy2;

					// determine direction from center of cube texture to current texel
					glm::vec3 dir;
					switch (GL_TEXTURE_CUBE_MAP_POSITIVE_X + face)
					{
					case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
						dir.x = 1.0f;
						dir.y = 1.0f - (invWidthBy2 * float(y) + invWidth);
						dir.z = 1.0f - (invWidthBy2 * float(x) + invWidth);
						dir = -dir;
						break;
					case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
						dir.x = -1.0f;
						dir.y = 1.0f - (invWidthBy2 * float(y) + invWidth);
						dir.z = -1.0f + (invWidthBy2 * float(x) + invWidth);
						dir = -dir;
						break;
					case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
						dir.x = -1.0f + (invWidthBy2 * float(x) + invWidth);
						dir.y = 1.0f;
						dir.z = -1.0f + (invWidthBy2 * float(y) + invWidth);
						dir = -dir;
						break;
					case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
						dir.x = -1.0f + (invWidthBy2 * float(x) + invWidth);
						dir.y = -1.0f;
						dir.z = 1.0f - (invWidthBy2 * float(y) + invWidth);
						dir = -dir;
						break;
					case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
						dir.x = -1.0f + (invWidthBy2 * float(x) + invWidth);
						dir.y = 1.0f - (invWidthBy2 * float(y) + invWidth);
						dir.z = 1.0f;
						break;
					case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
						dir.x = 1.0f - (invWidthBy2 * float(x) + invWidth);
						dir.y = 1.0f - (invWidthBy2 * float(y) + invWidth);
						dir.z = -1.0f;
						break;
					default:
						return;
					}

					// normalize direction
					dir = glm::normalize(dir);

					// scale factor depending on distance from center of the face
					const float fDiffSolid = 4.0f / ((1.0f + fU*fU + fV*fV) *
						sqrtf(1.0f + fU*fU + fV*fV));
					fWt += fDiffSolid;

					// calculate coefficients of spherical harmonics for current direction
					sphericalHarmonicsEvaluateDirection(shBuff.data(), order, dir);

					// index of texel in texture
					uint pixOffsetIndex = (x + y * width) * numComponents;
					// get color from texture and map to range [0, 1]
					glm::vec3 clr(
						float(data.get()[pixOffsetIndex]) / 255,
						float(data.get()[pixOffsetIndex + 1]) / 255,
						float(data.get()[pixOffsetIndex + 2]) / 255
						);
				

					// scale color and add to previously accumulated coefficients
					sphericalHarmonicsScale(shBuffB.data(), order,
						shBuff.data(), clr.r * fDiffSolid);
					sphericalHarmonicsAdd(resultR.data(), order,
						resultR.data(), shBuffB.data());
					sphericalHarmonicsScale(shBuffB.data(), order,
						shBuff.data(), clr.g * fDiffSolid);
					sphericalHarmonicsAdd(resultG.data(), order,
						resultG.data(), shBuffB.data());
					sphericalHarmonicsScale(shBuffB.data(), order,
						shBuff.data(), clr.b * fDiffSolid);
					sphericalHarmonicsAdd(resultB.data(), order,
						resultB.data(), shBuffB.data());
				}
			}
		}

		// final scale for coefficients
		const float fNormProj = (4.0f * M_PI) / fWt;
		sphericalHarmonicsScale(resultR.data(), order, resultR.data(), fNormProj);
		sphericalHarmonicsScale(resultG.data(), order, resultG.data(), fNormProj);
		sphericalHarmonicsScale(resultB.data(), order, resultB.data(), fNormProj);

		// save result
		for (uint i = 0; i < sqOrder; i++)
		{
			output[i].r = resultR[i];
			output[i].g = resultG[i];
			output[i].b = resultB[i];
		}
	}


	void SphericalHarmonicsScene::sphericalHarmonicsEvaluateDirection(float * result, int order,
		const glm::vec3 & dir)
	{
		// calculate coefficients for first 3 bands of spherical harmonics
		double p_0_0 = 0.282094791773878140;
		double p_1_0 = 0.488602511902919920 * dir.z;
		double p_1_1 = -0.488602511902919920;
		double p_2_0 = 0.946174695757560080 * dir.z * dir.z - 0.315391565252520050;
		double p_2_1 = -1.092548430592079200 * dir.z;
		double p_2_2 = 0.546274215296039590;
		result[0] = p_0_0;
		result[1] = p_1_1 * dir.y;
		result[2] = p_1_0;
		result[3] = p_1_1 * dir.x;
		result[4] = p_2_2 * (dir.x * dir.y + dir.y * dir.x);
		result[5] = p_2_1 * dir.y;
		result[6] = p_2_0;
		result[7] = p_2_1 * dir.x;
		result[8] = p_2_2 * (dir.x * dir.x - dir.y * dir.y);

	}

	void SphericalHarmonicsScene::sphericalHarmonicsAdd(float * result, int order,
		const float * inputA, const float * inputB)
	{
		const int numCoeff = order * order;
		for (int i = 0; i < numCoeff; i++)
		{
			result[i] = inputA[i] + inputB[i];
		}
	}

	void SphericalHarmonicsScene::sphericalHarmonicsScale(float * result, int order,
		const float * input, float scale)
	{
		const int numCoeff = order * order;
		for (int i = 0; i < numCoeff; i++)
		{
			result[i] = input[i] * scale;
		}
	}

	void SphericalHarmonicsScene::Draw()
	{
		m_shTech.Enable();

		renderScene(m_pActiveCamera->getPosition(), m_pActiveCamera->getViewProjection(),m_numOfBounces);

	}

	void SphericalHarmonicsScene::bakeSphericalHarmonics()
	{
		m_shTech.Enable();
		for (int bounceIndex = 1; bounceIndex <= MAX_BOUNCES; ++bounceIndex)
		{
			renderEnvironmentMap(bounceIndex-1);
			sphericalHarmonicsFromTexture(m_EnvMapTexture, m_shCoeff[bounceIndex], 3);
		}
	}

	void SphericalHarmonicsScene::initEnvironmentMapTexture()
	{
		glGenTextures(1, &m_EnvMapTexture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_EnvMapTexture);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		for (int i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, CUBEMAP_SIZE,
				CUBEMAP_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		}

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;

		glBindTexture(GL_TEXTURE_CUBE_MAP,0);

	}

	void SphericalHarmonicsScene::initEnvironmentRendering()
	{
		glGenFramebuffers(1, &m_fboId);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

		GLuint depthBufferId;
		glGenRenderbuffers(1, &depthBufferId);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, CUBEMAP_SIZE, CUBEMAP_SIZE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X, m_EnvMapTexture, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferId);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X, m_EnvMapTexture, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	void SphericalHarmonicsScene::renderEnvironmentMap(unsigned int coeffIndex)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

		for (int faceIndex = 0; faceIndex < 6; ++faceIndex)
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + faceIndex, m_EnvMapTexture, 0);
			glClear(GL_DEPTH_BUFFER_BIT);
			m_cubeCam->SetCameraToFace(faceIndex);
			renderScene(m_cubeCam->getPosition(), m_cubeCam->getViewProjection(), coeffIndex);
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void SphericalHarmonicsScene::renderScene(glm::vec3 camPosition, glm::mat4 viewProjection, unsigned int coeffIndex)
	{

		m_shTech.SetEyeWorldPos(camPosition);
		m_shTech.SetMatSpecularIntensity(0.0f);
		m_shTech.SetMatSpecularPower(0);
		m_shTech.SetCoefficients(&m_shCoeff[coeffIndex][0]);

		for (auto nodeIter = m_gameObjectsFlat.begin(); nodeIter != m_gameObjectsFlat.end(); nodeIter++)
		{
			m_shTech.SetWVP(viewProjection* (*nodeIter)->GetModelMatrix());
			m_shTech.SetWorldMatrix((*nodeIter)->GetModelMatrix());
			(*nodeIter)->GetModel()->Draw();
		}
	}


	void SphericalHarmonicsScene::onKeyRepeated(int key, int scancode)
	{
		handleKey(key);
	}
	void SphericalHarmonicsScene::onKeyReleased(int key, int scancode)
	{

	}

	void SphericalHarmonicsScene::onKeyPressed(int key, int scancode)
	{
		handleKey(key);
	}
	void SphericalHarmonicsScene::handleKey(int key)
	{
		if (key == GLFW_KEY_0)
		{
			m_numOfBounces = 0;
		}
		else if (key == GLFW_KEY_1)
		{
			m_numOfBounces = 1;
		}
		else if (key == GLFW_KEY_2)
		{
			m_numOfBounces = 2;
		}
		else if (key == GLFW_KEY_3)
		{
			m_numOfBounces = 3;
		}

	}
	/*void SphericalHarmonicsScene::renderScene(glm::vec3 camPosition, glm::mat4 viewProjection)
	{

		m_lighting.SetEyeWorldPos(camPosition);
		m_lighting.SetMatSpecularIntensity(0.0f);
		m_lighting.SetMatSpecularPower(0);

		for (auto nodeIter = m_gameObjectsFlat.begin(); nodeIter != m_gameObjectsFlat.end(); nodeIter++)
		{
			m_lighting.SetWVP(viewProjection* (*nodeIter)->GetModelMatrix());
			m_lighting.SetWorldMatrix((*nodeIter)->GetModelMatrix());
			(*nodeIter)->GetModel()->Draw();
		}
	}*/
}

