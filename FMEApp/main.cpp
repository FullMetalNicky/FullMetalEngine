
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <chrono>
#include <experimental/filesystem>
#include "SOIL.h"

#include "Commons.h"
#include "ResourceManager.h"
#include "Engine.h"

#include <thread>         // std::this_thread::sleep_for
#include <chrono>   


#pragma region mesh generation 

glm::vec3 shapeFunc(glm::vec3 gridElm, glm::vec3 gridDim)
{
	glm::vec3 gridCenter(0.5f);
	glm::vec3 res;

	//Sphere
	float latitude = glm::radians(180.0f);
	float longitude = glm::radians(360.0f);
	res.x = cos(longitude * (gridElm.x - gridCenter.x)) * cos(latitude * (gridElm.y - gridCenter.y));
	res.y = sin(longitude * (gridElm.x - gridCenter.x)) * cos(latitude * (gridElm.y - gridCenter.y));
	res.z = sin(latitude * (gridElm.y - gridCenter.y));

	//res = glm::vec3(gridElm.x - gridCenter.x, gridElm.y - gridCenter.y, 0.0f);

	return res;
}

#pragma endregion 


void frameLoader()
{
	std::vector<unsigned char*> texturesToUpdate;
	std::vector<std::string> texturePaths;
	std::string path = "D:/Dev/Data/video/CarCameraRigTop/";

	std::experimental::filesystem::directory_iterator path_it(path);
	std::experimental::filesystem::directory_iterator end_it;
	int width, height, channels;
	int i = 0;

	while (path_it != end_it)
	{
		++i;
		if (i < 55) continue;
		if (i > 100) break;
		std::vector<unsigned char*> vec;
		texturePaths.push_back(path_it->path().string());
		std::string texturePath = path_it->path().string();
		++path_it;
		unsigned char* image = SOIL_load_image(texturePath.c_str(), &width, &height, &channels, false);
		//texturesToUpdate.push_back(image);		
		vec.push_back(image);
		//FME::Graphics::Engine::Instance()->PushFrame(texturesToUpdate[texturesToUpdate.size() - 1], 1920, 1080, true, i  - 1);
		FME::Graphics::Engine::Instance()->PushFrame(vec, width, height, true, i - 1);
		std::this_thread::sleep_for(std::chrono::milliseconds(33));
	}
}

void SkyBoxLoader()
{
	std::vector<unsigned char*> texturesToUpdate;
	std::vector<std::vector<unsigned char*>> textures;
	std::string path = "D:/Dev/Data/video/skybox/Movies/Angle0New/Frame";
	int width, height, channels;

	for (int frame = 0; frame < 70; ++frame)
	{
		std::vector<unsigned char*> data;

		std::string texturePath = path + std::to_string(frame) + "/";
		std::vector<std::string> faces{
			texturePath + "posx.jpg",
			texturePath + "negx.jpg",
			texturePath + "posy.jpg",
			texturePath + "negy.jpg",
			texturePath + "posz.jpg",
			texturePath + "negz.jpg"
		};

		for (int i = 0; i < faces.size(); ++i)
		{
			std::string textureName = texturePath + faces[i];
			unsigned char* image = SOIL_load_image(faces[i].c_str(), &width, &height, &channels, false);
			data.push_back(image);
		}
		textures.push_back(data);
		FME::Graphics::Engine::Instance()->PushFrame(textures[frame], width, height, true, frame);
		//std::this_thread::sleep_for(std::chrono::milliseconds(33));
	}

	/*for(int frame = 0; frame < textures.size(); ++frame)
	{
		FME::Graphics::Engine::Instance()->PushFrame(textures[frame], width, height, true, frame);
		//std::this_thread::sleep_for(std::chrono::milliseconds(33));
	}*/
}

void app1()
{
	FME::Graphics::Engine::Instance()->SetFPS(30.0f);
	FME::Graphics::Engine::Instance()->SetWindowSize(glm::vec2(WIDTH, HEIGHT));
	FME::Graphics::Engine::Instance()->SetScene("scene.json");

	double deltaTime = 0.0;
	double lastFrame = 0.0;

	std::thread thready(SkyBoxLoader);

	while(FME::Graphics::Engine::Instance()->Alive())
	{
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		FME::Graphics::Engine::Instance()->Update(deltaTime);
		FME::Graphics::Engine::Instance()->Draw();
	}

	thready.join();
}


int main()
{
	app1();

	return 0;
}