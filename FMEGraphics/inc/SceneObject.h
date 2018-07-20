#ifndef SCENEOBJECT_H_
#define SCENEOBJECT_H_

#include <string>
#include <vector>
#include <memory>
#include <IObject.h>

namespace FME
{
	namespace Graphics
	{
		/** \class SceneObject
		*  \brief A class containing the entire scene information, as loaded using the SceneLoader.
		*/

		class SceneObject
		{
		public:

			SceneObject(const std::string& jsonPath);

			void SetGameLevel(unsigned int gameLevel);

			void Update(double deltaTime);
			void Draw();

			std::vector<std::vector<std::shared_ptr<IObject>>> GetChildren() { return m_children; };

		private:

			unsigned int m_gameLevel;
			std::vector<std::vector<std::shared_ptr<IObject>>> m_children;
		};
	}
}
#endif