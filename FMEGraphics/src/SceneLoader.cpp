#include "SceneLoader.h"
#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include <memory>
#include "ResourceManager.h"
#include "OBJModel.h"
#include "SkyboxModel.h"
#include "GeometryModel.h"
#include "GameObject.h"
#include "GroupObject.h"
#include "Engine.h"
#include "LightComponent.h"
#include "LightObject.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include <experimental/filesystem>
#include "RenderComponent.h"


#ifdef _DEBUG
#define DEBUG 1
#endif
#ifndef _DEBUG
#define DEBUG 0
#endif


using namespace FME::Graphics;

SceneLoader::SceneLoader(const std::string& JSONPath) //called only once in the beginning of the app, loading the scene graph
{
	std::ifstream is(JSONPath, std::ifstream::in);

	if (is) 
	{
		is.seekg(0, is.end);
		int length = is.tellg();
		is.seekg(0, is.beg);

		std::shared_ptr<char> buffer(new char[length]);
		is.read(buffer.get(), length);

		if (is) std::cout << "all characters read successfully.";
		else std::cout << "error: only " << is.gcount() << " could be read" << std::endl;
		is.close();

		std::string str = std::string(buffer.get());
		std::string out = parse(m_root, str);

		if (!m_root.is<picojson::object>())
		{
			std::cerr << "file is not a json file!" << std::endl;
		}
	}
	else
	{
		std::cerr << "could not find json file!" << std::endl;
	}
}

void SceneLoader::LoadAssets()
{
	std::string libraryPath;
	picojson::value::object& rootObj = m_root.get<picojson::object>();
	if (m_root.contains("Assets"))
	{
		picojson::value assets = m_root.get("Assets");
		if (assets.contains("Textures"))
		{
			picojson::value textures = assets.get("Textures");
			loadTextures(textures);
		}
		if (assets.contains("Shaders"))
		{
			picojson::value shaders = assets.get("Shaders");
			loadShaders(shaders);
		}
		if (assets.contains("Models"))
		{
			picojson::value models = assets.get("Models");
			loadModels(models);
		}
		if (assets.contains("LibraryPath"))
		{
			picojson::value libPathVal = assets.get("LibraryPath");
			std::string libraryPath = libPathVal.get<std::string>();
			loadEngineShaders(libraryPath + "/FMEGraphics/shaders/");
		}
	}	
}

void SceneLoader::loadEngineShaders(const std::string& libraryPath)
{
	std::map<std::string, std::string> shaderNames;
	std::pair<std::map<std::string, std::string>::iterator, bool> ret;

	std::experimental::filesystem::directory_iterator path_it(libraryPath);
	std::experimental::filesystem::directory_iterator end_it;

	while (path_it != end_it)
	{
		std::string shaderPath = path_it->path().string();
		std::string shaderName = path_it->path().filename().string();
		shaderName = shaderName.substr(0, shaderName.find_last_of('.'));
		ret = shaderNames.insert(std::pair<std::string, std::string>(shaderName, shaderPath));
		if (true == ret.second)
		{
			ResourceManager::Instance()->LoadShader(std::string(libraryPath + shaderName + ".vert").c_str(), std::string(libraryPath + shaderName + ".frag").c_str(), nullptr, shaderName);
		}

		++path_it;
	}
}

void SceneLoader::loadShaders(picojson::value shaders)
{
	if (shaders.is<picojson::array>())
	{
		picojson::array arr = shaders.get<picojson::array>();
		for (int i = 0; i < arr.size(); ++i)
		{
			picojson::value::object& arrObj = arr[i].get<picojson::object>();
			std::string shaderName;
			std::string shaderPath;
			for (picojson::value::object::const_iterator it = arrObj.begin(); it != arrObj.end(); ++it)
			{
				if (DEBUG) std::cout << it->first << " : " << it->second.to_str() << std::endl;
				if (it->first == "Name")
				{
					shaderName = it->second.to_str();
				}
				else if (it->first == "Path")
				{
					shaderPath = it->second.to_str();
				}
			}
			ResourceManager::Instance()->LoadShader(std::string(shaderPath + ".vert").c_str(), std::string(shaderPath + ".frag").c_str(), nullptr, shaderName);
		}
	}
	else
	{
		std::cerr << "shaders are not an array!" << std::endl;
	}
}

void SceneLoader::loadTextures(picojson::value textures)
{
	if (textures.is<picojson::array>())
	{
		picojson::array arr = textures.get<picojson::array>();
		for (int i = 0; i < arr.size(); ++i)
		{
			picojson::value::object& arrObj = arr[i].get<picojson::object>();
			std::string textureName;
			std::string texturePath;
			std::string textureType;
			unsigned int textureWidth;
			unsigned int textureHeight;

			for (picojson::value::object::const_iterator it = arrObj.begin(); it != arrObj.end(); ++it)
			{
				if(DEBUG) std::cout << it->first << " : " << it->second.to_str() << std::endl;

				if (it->first == "Name")
				{
					textureName = it->second.to_str();
				}
				else if (it->first == "Path")
				{
					texturePath = it->second.to_str();
				}
				else if (it->first == "Type")
				{
					textureType = it->second.to_str();
				}
				else if (it->first == "Width")
				{
					textureWidth = std::stoi(it->second.to_str());
				}
				else if (it->first == "Height")
				{
					textureHeight = std::stoi(it->second.to_str());
				}
			}
			if (textureType == "2D")
			{
				if ("" == texturePath) //empty texture
				{
					ResourceManager::Instance()->LoadTexture(textureWidth, textureHeight, nullptr, true, textureName);
				}
				else ResourceManager::Instance()->LoadTexture(texturePath.c_str(), true, textureName);
			}
			else if (textureType == "3D")
			{
				std::vector<std::string> faces{ 
					texturePath + "posx.jpg",
					texturePath + "negx.jpg",
					texturePath + "posy.jpg",
					texturePath + "negy.jpg",
					texturePath + "posz.jpg",
					texturePath + "negz.jpg"
				};
				ResourceManager::Instance()->LoadTexture(faces, true, textureName);
			}
		}
	}
	else
	{
		std::cerr << "textures are not an array!" << std::endl;
	}
}

void SceneLoader::loadModels(picojson::value models)
{
	if (models.is<picojson::object>())
	{
		if (models.contains("OBJ"))
		{
			picojson::value objs = models.get("OBJ");
			if (objs.is<picojson::array>())
			{
				picojson::array arr = objs.get<picojson::array>();
				for (int i = 0; i < arr.size(); ++i)
				{
					picojson::value::object& arrObj = arr[i].get<picojson::object>();
					std::string objName;
					std::string objPath;
					for (picojson::value::object::const_iterator it = arrObj.begin(); it != arrObj.end(); ++it)
					{
						if (DEBUG) std::cout << it->first << " : " << it->second.to_str() << std::endl;
						if (it->first == "Name")
						{
							objName = it->second.to_str();
						}
						else if (it->first == "Path")
						{
							objPath = it->second.to_str();
						}
					}
					OBJModel objm(objPath);
					ResourceManager::Instance()->LoadModel(std::make_shared<OBJModel>(objm), objName);
				}
			}
		}
		if (models.contains("Skybox"))
		{
			picojson::value skyboxes = models.get("Skybox");
			if (skyboxes.is<picojson::array>())
			{
				picojson::array arr = skyboxes.get<picojson::array>();
				for (int i = 0; i < arr.size(); ++i)
				{
					picojson::value::object& arrObj = arr[i].get<picojson::object>();
					std::string skyboxName;
					std::string textureName;
					for (picojson::value::object::const_iterator it = arrObj.begin(); it != arrObj.end(); ++it)
					{
						if (DEBUG) std::cout << it->first << " : " << it->second.to_str() << std::endl;
						if (it->first == "Name")
						{
							skyboxName = it->second.to_str();
						}
						else if (it->first == "Texture")
						{
							textureName = it->second.to_str();
						}
					}
					SkyboxModel skymodel(textureName);
					ResourceManager::Instance()->LoadModel(std::make_shared<SkyboxModel>(skymodel), skyboxName);
				}
			}
		}
		if (models.contains("Geometry"))
		{
			picojson::value geometries = models.get("Geometry");
			if (geometries.is<picojson::array>())
			{
				picojson::array arr = geometries.get<picojson::array>();
				for (int i = 0; i < arr.size(); ++i)
				{
					picojson::value::object& arrObj = arr[i].get<picojson::object>();
					std::string geometryName;
					std::string geometryType;
					std::string textureName;
					glm::vec4 geometryColor;
					bool isColor = false;
					for (picojson::value::object::const_iterator it = arrObj.begin(); it != arrObj.end(); ++it)
					{
						if (DEBUG) std::cout << it->first << " : " << it->second.to_str() << std::endl;
						if (it->first == "Name")
						{
							geometryName = it->second.to_str();
						}
						else if (it->first == "Texture")
						{
							textureName = it->second.to_str();
						}
						else if (it->first == "Type")
						{
							geometryType = it->second.to_str();
						}
						else if (it->first == "Color")
						{
							geometryColor = loadColor(arr[i].get("Color"));
							isColor = true;
						}
					}
					if (geometryType == "Plane")
					{
						if (isColor)
						{
							GeometryModel geometryModel(GeometryType::PLANE, geometryColor);
							ResourceManager::Instance()->LoadModel(std::make_shared<GeometryModel>(geometryModel), geometryName);
						}
						else
						{
							GeometryModel geometryModel(GeometryType::PLANE, textureName);
							ResourceManager::Instance()->LoadModel(std::make_shared<GeometryModel>(geometryModel), geometryName);
						}
					}
					else if (geometryType == "Cube")
					{
						GeometryModel geometryModel(GeometryType::CUBE, textureName);
						ResourceManager::Instance()->LoadModel(std::make_shared<GeometryModel>(geometryModel), geometryName);
					}	
					else if (geometryType == "Cylinder")
					{
						GeometryModel geometryModel(GeometryType::CYLINDER, textureName);
						ResourceManager::Instance()->LoadModel(std::make_shared<GeometryModel>(geometryModel), geometryName);
					}
				}
			}
		}
	}	
	else
	{
		std::cerr << "models are not an array!" << std::endl;
	}
}

void SceneLoader::LoadLevels(std::vector<std::vector<std::shared_ptr<IObject>>>& children)
{
	picojson::value::object& rootObj = m_root.get<picojson::object>();
	if (m_root.contains("Levels"))
	{
		picojson::value levels = m_root.get("Levels");
		if (levels.is<picojson::array>())
		{
			picojson::array arr = levels.get<picojson::array>();
			children = std::vector<std::vector<std::shared_ptr<IObject>>>(arr.size(), std::vector<std::shared_ptr<IObject>>());
			std::vector<std::pair<glm::vec3, glm::vec3>> cameraPresets(arr.size(), std::pair<glm::vec3, glm::vec3>());

			for (int level = 0; level < arr.size(); ++level)
			{
				if (arr[level].contains("Camera"))
				{
					glm::vec3 position, POI;
					picojson::value camera = arr[level].get("Camera");
					loadCamera(camera, position, POI);
					cameraPresets[level] = std::pair<glm::vec3, glm::vec3>(position, POI);
				}
				if (arr[level].contains("GameObjects"))
				{
					picojson::value gameObjects = arr[level].get("GameObjects");
					picojson::array GOarr = gameObjects.get<picojson::array>();
					for (int i = 0; i < GOarr.size(); ++i)
					{
						std::shared_ptr<IObject> go = loadGameObject(GOarr[i]);
						children[level].push_back(go);
					}
				}
				if (arr[level].contains("GroupObjects"))
				{
					picojson::value gameObjects = arr[level].get("GroupObjects");
					picojson::array GOarr = gameObjects.get<picojson::array>();
					for (int i = 0; i < GOarr.size(); ++i)
					{
						std::shared_ptr<IObject> go = loadGroupObject(GOarr[i]);
						children[level].push_back(go);
					}
				}
			}
			Engine::Instance()->SetCameraPresets(cameraPresets);
		}
	}
}

std::shared_ptr<IObject> SceneLoader::loadGroupObject(picojson::value groupObjectVal)
{
	picojson::value::object& arrObj = groupObjectVal.get<picojson::object>();

	std::string modelName;
	std::string goName;
	std::string modelType;
	Transform trans;
	bool fixed = false;
	for (picojson::value::object::const_iterator it = arrObj.begin(); it != arrObj.end(); ++it)
	{
		if (it->first == "Transform")
		{
			picojson::value transVal = groupObjectVal.get("Transform");
			trans = loadTransform(transVal);
		}
		else if (it->first == "FixedTransform")
		{
			if ("true" == it->second.to_str()) fixed = true;
		}
		else if (it->first == "Name")
		{
			goName = it->second.to_str();
		}
	}

	GroupObject groupObject(goName);
	groupObject.GetTransformComponent()->SetFixedTransform(trans);

	for (picojson::value::object::const_iterator it = arrObj.begin(); it != arrObj.end(); ++it)
	{
		if (it->first == "GameObjects")
		{
			picojson::value gameObjects = groupObjectVal.get("GameObjects");
			picojson::array GOarr = gameObjects.get<picojson::array>();
			for (int i = 0; i < GOarr.size(); ++i)
			{
				std::shared_ptr<GameObject> go = loadGameObject(GOarr[i]);
				go->GetTransformComponent()->SetParent(groupObject.GetTransformComponent());
				groupObject.AddChild(go->GetName(), go);
			}
		}
	}

	return std::make_shared<GroupObject>(groupObject);
}

std::shared_ptr<GameObject> SceneLoader::loadGameObject(picojson::value gameObject)
{
		picojson::value::object& arrObj = gameObject.get<picojson::object>();
		std::string modelName;
		std::string goName;
		std::string modelType;
		Transform trans{ glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f) };
		bool fixed = false;
		std::vector<std::shared_ptr<LightObject>> lights;

		for (picojson::value::object::const_iterator it = arrObj.begin(); it != arrObj.end(); ++it)
		{
			if (DEBUG) std::cout << it->first << " : " << it->second.to_str() << std::endl;
			if (it->first == "Model")
			{
				modelName = it->second.to_str();
			}
			else if (it->first == "Transform")
			{
				picojson::value transVal = gameObject.get("Transform");
				trans = loadTransform(transVal);
			}
			else if (it->first == "FixedTransform")
			{
				if ("true" == it->second.to_str()) fixed = true;
			}
			else if (it->first == "Name")
			{
				goName = it->second.to_str();
			}
			else if (it->first == "Type")
			{
				modelType = it->second.to_str();
			}
			else if (it->first == "Light")
			{
				lights = loadLights(gameObject.get("Light"));
			}
		}
		GameObject go(goName);
		if (modelName.size())
		{
			RenderComponent rc(ResourceManager::Instance()->GetModel(modelName));
			if ("2D" == modelType) rc.SetGameType(GameType::RENDER2D);
			go.AddComponent(std::make_shared<RenderComponent>(rc));
		}
		if (!fixed) go.GetTransformComponent()->SetTransform(trans);
		else go.GetTransformComponent()->SetFixedTransform(trans);
		if (lights.size())
		{
			LightComponent lc(lights);
			lc.SetShader(ResourceManager::Instance()->GetModel(modelName)->GetShaderName());
			go.AddComponent(std::make_shared<LightComponent>(lc));
		}

		return std::make_shared<GameObject>(go);
}

std::vector<std::shared_ptr<LightObject>> SceneLoader::loadLights(picojson::value lightsVal)
{
	std::vector<std::shared_ptr<LightObject>> lights;

	picojson::value::object& lightsObj = lightsVal.get<picojson::object>();
	for (picojson::value::object::const_iterator it = lightsObj.begin(); it != lightsObj.end(); ++it)
	{
		std::shared_ptr<LightObject> lightObject = parseLights(lightsVal.get(it->first), it->first);
		lights.push_back(lightObject);
	}

	return lights;
}

std::shared_ptr<LightObject> SceneLoader::parseLights(picojson::value lightsVal, const std::string& lightType)
{
	std::vector<LightInfo> lightInfoVec;
	std::shared_ptr<LightObject> lightObject;

	picojson::array lightsArr = lightsVal.get<picojson::array>();
	for (int i = 0; i < lightsArr.size(); ++i)
	{
		LightInfo lightInfo;
		picojson::value::object& lightObj = lightsArr[i].get<picojson::object>();
		for (picojson::value::object::const_iterator it = lightObj.begin(); it != lightObj.end(); ++it)
		{
			if (it->first == "direction")
			{
				lightInfo.direction = parseVec3(lightsArr[i].get("direction"));
			}
			if (it->first == "position")
			{
				lightInfo.position = parseVec3(lightsArr[i].get("position"));
			}
			if (it->first == "ambient")
			{
				lightInfo.ambient = parseVec3(lightsArr[i].get("ambient"));
			}
			if (it->first == "diffuse")
			{
				lightInfo.diffuse = parseVec3(lightsArr[i].get("diffuse"));
			}
			if (it->first == "specular")
			{
				lightInfo.specular = parseVec3(lightsArr[i].get("specular"));
			}
			if (it->first == "cutOff")
			{
				lightInfo.cutOff = std::stof(it->second.to_str());
			}
			if (it->first == "outerCutOff")
			{
				lightInfo.outerCutOff = std::stof(it->second.to_str());
			}
			if (it->first == "constant")
			{
				lightInfo.constant = std::stof(it->second.to_str());
			}
			if (it->first == "linear")
			{
				lightInfo.linear = std::stof(it->second.to_str());
			}
			if (it->first == "quadratic")
			{
				lightInfo.quadratic = std::stof(it->second.to_str());
			}
		}
		lightInfoVec.push_back(lightInfo);
	}

	if (lightType == "DirectionalLight")
	{
		DirectionalLight dl(lightInfoVec);
		lightObject = std::make_shared<DirectionalLight>(dl);
	}
	if (lightType == "SpotLight")
	{
		SpotLight sp(lightInfoVec);
		lightObject = std::make_shared<SpotLight>(sp);
	}
	if (lightType == "PointLight")
	{
		PointLight pl(lightInfoVec);
		lightObject = std::make_shared<PointLight>(pl);
	}

	return lightObject;
}

glm::vec3 SceneLoader::parseVec3(picojson::value vec)
{
	glm::vec3 parsedVec;
	picojson::value::object& vecsObj = vec.get<picojson::object>();
	for (picojson::value::object::const_iterator it = vecsObj.begin(); it != vecsObj.end(); ++it)
	{
		if (it->first == "x")
		{
			parsedVec.x = std::stof(it->second.to_str());
		}
		if (it->first == "y")
		{
			parsedVec.y = std::stof(it->second.to_str());
		}
		if (it->first == "z")
		{
			parsedVec.z = std::stof(it->second.to_str());
		}
		if (it->first == "r")
		{
			parsedVec.x = std::stof(it->second.to_str());
		}
		if (it->first == "g")
		{
			parsedVec.y = std::stof(it->second.to_str());
		}
		if (it->first == "b")
		{
			parsedVec.z = std::stof(it->second.to_str());
		}
	}

	return parsedVec;
}


Transform SceneLoader::loadTransform(picojson::value transformVal)
{
	Transform trans{glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f) };

	picojson::value::object& transObj = transformVal.get<picojson::object>();
	for (picojson::value::object::const_iterator it = transObj.begin(); it != transObj.end(); ++it)
	{
		if (it->first == "x")
		{
			trans.Translation.x = std::stof(it->second.to_str());
		}
		if (it->first == "y")
		{
			trans.Translation.y = std::stof(it->second.to_str());
		}
		if (it->first == "z")
		{
			trans.Translation.z = std::stof(it->second.to_str());
		}
		if (it->first == "rx")
		{
			trans.Rotation.x = std::stof(it->second.to_str());
		}
		if (it->first == "ry")
		{
			trans.Rotation.y = std::stof(it->second.to_str());
		}
		if (it->first == "rz")
		{
			trans.Rotation.z = std::stof(it->second.to_str());
		}
		if (it->first == "sx")
		{
			trans.Scale.x = std::stof(it->second.to_str());
		}
		if (it->first == "sy")
		{
			trans.Scale.y = std::stof(it->second.to_str());
		}
		if (it->first == "sz")
		{
			trans.Scale.z = std::stof(it->second.to_str());
		}
	}
	
	return trans;
}


glm::vec4 SceneLoader::loadColor(picojson::value colorVal)
{
	glm::vec4 color(0.0f);

	picojson::value::object& colorObj = colorVal.get<picojson::object>();
	for (picojson::value::object::const_iterator it = colorObj.begin(); it != colorObj.end(); ++it)
	{
		if (it->first == "r")
		{
			color.x = std::stof(it->second.to_str());
		}
		if (it->first == "g")
		{
			color.y = std::stof(it->second.to_str());
		}
		if (it->first == "b")
		{
			color.z = std::stof(it->second.to_str());
		}
		if (it->first == "a")
		{
			color.w = std::stof(it->second.to_str());
		}
	}

	return color;
}


void SceneLoader::loadCamera(picojson::value camera, glm::vec3& position, glm::vec3& POI)
{
	if (camera.is<picojson::object>())
	{
		picojson::value::object& camObj = camera.get<picojson::object>();
		picojson::value posVal;
		picojson::value POIVal;

		for (picojson::value::object::const_iterator it = camObj.begin(); it != camObj.end(); ++it)
		{
			if (DEBUG) std::cout << it->first << " : " << it->second.to_str() << std::endl;
			if (it->first == "Position")
			{
				posVal = camera.get("Position");
			}
			else if (it->first == "POI")
			{
				POIVal = camera.get("POI");
			}
		}
		parseCameraPreset(posVal, POIVal, position, POI);

	}

}

void SceneLoader::parseCameraPreset(picojson::value posVal, picojson::value POIVal, glm::vec3& position, glm::vec3& POI)
{
	if (posVal.is<picojson::object>())
	{
		picojson::value::object& posObj = posVal.get<picojson::object>();
		for (picojson::value::object::const_iterator it = posObj.begin(); it != posObj.end(); ++it)
		{
			if (it->first == "x")
			{
				position.x = std::stof(it->second.to_str());
			}
			if (it->first == "y")
			{
				position.y = std::stof(it->second.to_str());
			}
			if (it->first == "z")
			{
				position.z = std::stof(it->second.to_str());
			}
		}
	}
	if (POIVal.is<picojson::object>())
	{
		picojson::value::object& POIObj = POIVal.get<picojson::object>();
		for (picojson::value::object::const_iterator it = POIObj.begin(); it != POIObj.end(); ++it)
		{
			if (it->first == "x")
			{
				POI.x = std::stof(it->second.to_str());
			}
			if (it->first == "y")
			{
				POI.y = std::stof(it->second.to_str());
			}
			if (it->first == "z")
			{
				POI.z = std::stof(it->second.to_str());
			}
		}
	}
}