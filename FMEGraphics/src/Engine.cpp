#include "Engine.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "InputManager.h"
#include "ResourceManager.h"
#include "glm/gtx/string_cast.hpp"
#include "RenderToTextureEffect.h"
#include "BloomEffect.h"
#include "ViewPortEffect.h"


using namespace FME::Graphics;

std::shared_ptr<Engine> Engine::_instance = nullptr;


Engine::Engine() 
{
	m_accumulator = 0.0;
	m_simulationTime = 0.0;
	m_jsonPath = "";
	m_currentGameLevel = 0;

	m_decoder = std::shared_ptr<DecoderComponent>(new DecoderComponent("skybox"));
	m_pipeline = std::shared_ptr<Pipeline>(new Pipeline);
}

std::shared_ptr<Engine> Engine::Instance()
{
	if (_instance == nullptr)
	{
		_instance = std::shared_ptr<Engine>(new Engine());
	}
	return _instance;
}


void Engine::SetScene(const std::string& jsonPath)
{
	if (m_jsonPath != jsonPath)
	{
		m_jsonPath = jsonPath;
		m_scene = std::shared_ptr<SceneObject>(new SceneObject(m_jsonPath));
	}
	m_scene->SetGameLevel(m_currentGameLevel);
	m_camera = std::shared_ptr<Camera>(new Camera(m_cameraPresets[m_currentGameLevel].first, m_cameraPresets[m_currentGameLevel].second));

	//update camera to relevant position
}

void Engine::PushFrame(const std::vector<unsigned char*>& image, int width, int height, bool alpha, int frameNum )
{	
	DataBuffer buffer{ image, width, height, alpha , frameNum};
	m_decoder->PushFrame(buffer);		
}


void Engine::GetCamera(glm::mat4& view, glm::mat4& proj) const 
{
	view = m_camera->GetViewMatrix();
	proj = glm::perspective(45.0f, (float)m_windowSize.x / (float)m_windowSize.y, 0.1f, 100.0f);
}

void Engine::SetWindowSize(glm::ivec2 windowSize)
{
	m_windowSize = windowSize;
	m_app = std::shared_ptr<OpenGLWindow>(new OpenGLWindow(m_windowSize, glm::vec2(3, 3), "FullMetalEngine"));
	InputManager::Instance()->SetWindow(m_windowSize, m_app->GetWindow());
	//m_pipeline->AddEffect(std::shared_ptr<BloomEffect>(new BloomEffect(m_windowSize)), "BloomEffect");
	m_pipeline->AddEffect(std::shared_ptr<RenderToTextureEffect>(new RenderToTextureEffect(m_windowSize, "RenderToTextureEffect1")), "RenderToTextureEffect1");
	m_pipeline->AddEffect(std::shared_ptr<RenderToTextureEffect>(new RenderToTextureEffect(m_windowSize, "RenderToTextureEffect2")), "RenderToTextureEffect2");

	std::vector<ViewPortParams> params = { ViewPortParams{ "RenderToTextureEffect1", 
		glm::ivec4(0.5 *  m_windowSize.x, 0.0, 1.0, 1.0),
		//glm::ivec4(0.15, 0.0, 0.7 * m_windowSize.x, m_windowSize.y)},
		glm::ivec4(0.0, 0.0, 0.5 *  m_windowSize.x, m_windowSize.y) },
		ViewPortParams{ "RenderToTextureEffect2",
		glm::ivec4(0, 0.0, 1.0,  1.0),
		glm::ivec4(0.0, 0.0, 0.5 * m_windowSize.x, m_windowSize.y)}};

	m_pipeline->AddEffect(std::shared_ptr<ViewPortEffect>(new ViewPortEffect(m_windowSize, params)), "ViewPortEffect");
}



void Engine::Update(double m_deltaTime)  //update inputs and camera
{
	m_accumulator += m_deltaTime;

	while (m_accumulator > m_maxTimeStep)
	{
		updateOnce(m_maxTimeStep);
		m_accumulator -= m_maxTimeStep;
		m_simulationTime += m_maxTimeStep;
	}
}

void  Engine::updateOnce(double deltaTime)
{
	m_app->Update();
	InputManager::Instance()->Update();

	int level = updateGameLevel(InputManager::Instance()->GetKeys());
	if (level != m_currentGameLevel)
	{
		m_currentGameLevel = level;
		m_scene->SetGameLevel(m_currentGameLevel);		
	}
	else
	{

	}
	updateInput(InputManager::Instance()->GetKeys(), deltaTime);
	m_camera->Update();
	m_decoder->Update();
	m_scene->Update(deltaTime);
}

unsigned int Engine::updateGameLevel(std::vector<bool> keys)
{
	int level = m_currentGameLevel;

	if (keys['0'])
	{
		level = 0;	
	}
	if (keys['1'])
	{
		level = 1;	
	}	
	if (keys['2'])
	{
		level = 2;
	}

	return level;
}


void Engine::updateCamera(std::vector<bool> keys, double deltaTime)
{
	float sensitivity = 10.0f;
	double xoffset, yoffset, zoffset = 0.0;

	if (keys[GLFW_KEY_KP_8] || keys[GLFW_KEY_KP_6] || keys[GLFW_KEY_KP_4] || keys[GLFW_KEY_KP_2] || keys[GLFW_KEY_KP_ADD] || keys[GLFW_KEY_KP_SUBTRACT])
	{
		xoffset = (bool(keys[GLFW_KEY_KP_6]) * deltaTime * sensitivity - bool(keys[GLFW_KEY_KP_4]) * deltaTime * sensitivity);
		yoffset = bool(keys[GLFW_KEY_KP_2]) * deltaTime * sensitivity - bool(keys[GLFW_KEY_KP_8]) * deltaTime * sensitivity;
		zoffset = bool(keys[GLFW_KEY_KP_ADD]) * 0.5f - bool(keys[GLFW_KEY_KP_SUBTRACT]) * 0.5f;
		m_camera->PanTumble(xoffset, yoffset);
		m_camera->Zoom(zoffset);
	//	m_camera->Rotate(xoffset, yoffset);
	}
	if (keys['0'])
	{
		m_camera->SetPosition(m_cameraPresets[0].first);
		m_camera->SetPOI(m_cameraPresets[0].second);
	}
	if (keys['1'])
	{		
		m_camera->SetPosition(m_cameraPresets[1].first);
		m_camera->SetPOI(m_cameraPresets[1].second);
	}	
	if (keys['3'])
	{
		m_camera->SetPosition(glm::vec3(0.0f, 35.0f, 6.0f));
		m_camera->SetPOI(glm::vec3(0.0f, 0.0f, 6.01f));
	}
}


void Engine::updateInput(std::vector<bool> keys, double deltaTime)
{
	float deltaAngle = 0.0f;
	
	int level = updateGameLevel(keys);
	if (level != m_currentGameLevel)
	{
		m_currentGameLevel = level;
		m_scene->SetGameLevel(m_currentGameLevel);
	}
	
	updateCamera(keys, deltaTime);
	m_deltaTime = deltaTime;
}


Transform Engine::GetControllerUpdate(const char key) const
{
	std::vector<bool> keys = InputManager::Instance()->GetKeys();
	Transform deltaMovement = { glm::vec3(0.0f) , glm::vec3(0.0f) , glm::vec3(0.0f) };
	float deltaAngle = 0.0f;
	float sensitivity = 10.0f;

	if (('L' == key) || ('R' == key))
	{
		if (keys[key])
		{
			deltaAngle = sensitivity * m_deltaTime * ('L' == key) - sensitivity * m_deltaTime * ('R' == key);
			deltaMovement = { glm::vec3(0.0f) , glm::vec3(0.0f, deltaAngle, 0.0f) , glm::vec3(0.0f) };
		}
	}
	return deltaMovement;
}



void Engine::Draw()  //render start, draw scene, render end, app draw
{
	m_pipeline->ClearScreen();
	
	m_pipeline->RenderStart("RenderToTextureEffect1");
	m_scene->Draw();	
	m_pipeline->RenderEnd();
	//m_pipeline->RenderToScreen();

	m_camera->SetPosition(glm::vec3(0.0f, 35.0f, 6.0f));
	m_camera->SetPOI(glm::vec3(0.0f, 0.0f, 6.01f));
	m_camera->Update();

	m_pipeline->RenderStart("RenderToTextureEffect2");
	m_scene->Draw();
	m_pipeline->RenderEnd();
//	m_pipeline->RenderToScreen();
	m_pipeline->RenderStart("ViewPortEffect");
	m_pipeline->RenderToScreen();

	m_app->Draw();
}