#ifndef SCENELOADER_H_
#define SCENELOADER_H_

#include <string>
#include "picojson.h"
#include "IObject.h"
#include "GameObject.h"
#include "LightObject.h"
#include <memory>

namespace FME
{
	namespace Graphics
	{
		/** \class SceneLoader
		*  \brief A class that will read a json file, parse it and load the scene -  assests like OBJs, textures, their transforms and the 
		* game level structure, defining which objects are rendered at which state.
		*/

		class SceneLoader
		{
		public:

			SceneLoader(const std::string& JSONPath); //called only once in the beginning of the app, loading the scene graph
			void LoadAssets();
			void LoadLevels(std::vector<std::vector<std::shared_ptr<IObject>>>& children);

		private:

			void loadShaders(picojson::value shaders);
			void loadTextures(picojson::value textures);
			void loadModels(picojson::value models);

			std::shared_ptr<GameObject> loadGameObject(picojson::value gameObject);
			std::shared_ptr<IObject> loadGroupObject(picojson::value groupObject);


			Transform loadTransform(picojson::value transform);
			std::vector<std::shared_ptr<LightObject>> loadLights(picojson::value lights);
			std::shared_ptr<LightObject> parseLights(picojson::value lights, const std::string& lightType);
			glm::vec3 parseVec3(picojson::value vec);
			glm::vec4 loadColor(picojson::value color);
			void loadCamera(picojson::value camera, glm::vec3& position, glm::vec3& POI);
			void parseCameraPreset(picojson::value posVal, picojson::value POIVal, glm::vec3& position, glm::vec3& POI);


			picojson::value m_root;
		};
	}
}
#endif
