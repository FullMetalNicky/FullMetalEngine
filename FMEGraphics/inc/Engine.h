#ifndef ENGINE_H_
#define ENGINE_H_

#include "Camera.h"
#include "OpenGLWindow.h"
#include "SceneObject.h"
#include "DecoderComponent.h"
#include <memory>
#include "Pipeline.h"


namespace FME
{
	namespace Graphics
	{
		enum GameState
		{
			START,
			RUN,
			PAUSE,
			STOP
		};

		/** \class Engine
		*  \brief A singleton class that implements the default engine. The engine is responsible for the camera, the scene, the OpenGL application and the pipeline
		* the engine is the one managing the update and draw of the scenegraph as well as the effect pipeline
		*/

		class Engine
		{
		public:

			static std::shared_ptr<Engine> Instance();
			
			bool Alive() { return m_app->Alive(); };
			void Update(double m_deltaTime); 
			void Draw() ; 

			void SetWindowSize(glm::ivec2 windowSize);
			void SetScene(const std::string& jsonPath);

			void SetFPS(double fps = 30) { m_maxTimeStep = 1.0 / fps; };
			double GetFPS() const {return double(1.0 / m_maxTimeStep);};

			void SetCameraPresets(std::vector<std::pair<glm::vec3, glm::vec3>> cameraPresets) { m_cameraPresets = cameraPresets; };
			void GetCamera(glm::mat4& view, glm::mat4& proj) const ;
			glm::vec3 GetCameraPosition() const {return m_camera->GetPosition(); };

			void PushFrame(const std::vector<unsigned char*>& image, int width, int height, bool alpha = false, int frameNum = -1);

			
		protected:

			Engine();

			void updateOnce(double deltaTime);
			void updateInput(std::vector<bool> keys, double deltaTime);
			void updateComponents(std::vector<bool> keys, double deltaTime);
			void updateComponentsImp(std::map<std::string, std::shared_ptr<IObject>> subChildren, const Transform& transform);
			unsigned int updateGameLevel(std::vector<bool> keys);
			void updateCamera(std::vector<bool> keys, double deltaTime);

			static std::shared_ptr<Engine> _instance;
			std::shared_ptr<Camera> m_camera;
			std::shared_ptr<OpenGLWindow> m_app;
			std::shared_ptr<SceneObject> m_scene;
			std::shared_ptr<DecoderComponent> m_decoder;			
			std::shared_ptr<Pipeline> m_pipeline;


			std::vector<unsigned int> m_gameLevels;
			std::vector<std::pair<glm::vec3, glm::vec3>> m_cameraPresets; //per level
			double m_accumulator;
			double m_maxTimeStep;
			double m_simulationTime;
			std::string m_jsonPath;
			glm::ivec2 m_windowSize;
			unsigned int m_currentGameLevel;
		};
	}
}

#endif
