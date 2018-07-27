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
			void Update(double deltaTime); 
			void Draw() ; 

			void SetWindowSize(glm::ivec2 windowSize);
			void SetScene(const std::string& jsonPath);
			void SetEffects(const std::string& jsonPath);

			void SetFPS(double fps = 30) { m_maxTimeStep = 1.0 / fps; };
			double GetFPS() const {return double(1.0 / m_maxTimeStep);};
			glm::ivec2 GetWindowSize() const { return m_windowSize; };

			void SetCameraPresets(std::vector<std::pair<glm::vec3, glm::vec3>> cameraPresets) { m_cameraPresets = cameraPresets; };
			void GetCamera(glm::mat4& view, glm::mat4& proj) const;
			void SetActiveCamera(unsigned int index) { m_activeCamera = index; };
			unsigned int GetActiveCamera() const {return  m_activeCamera; };
			glm::vec3 GetCameraPosition() const {return m_cameras[m_activeCamera]->GetPosition(); };

			void PushFrame(const std::vector<unsigned char*>& image, int width, int height, bool alpha = false, int frameNum = -1);

			Transform GetControllerUpdate(const char key) const;
			
		protected:
			
			Engine();

			void updateOnce(double deltaTime);
			void updateInput(std::vector<bool> keys, double deltaTime);
			unsigned int updateGameLevel(std::vector<bool> keys);
			void updateCamera(std::vector<bool> keys, double deltaTime);

			static std::shared_ptr<Engine> _instance;
			std::vector<std::shared_ptr<Camera>> m_cameras;
			unsigned int m_activeCamera;
			std::shared_ptr<OpenGLWindow> m_app;
			std::shared_ptr<SceneObject> m_scene;
			std::shared_ptr<DecoderComponent> m_decoder;			
			std::shared_ptr<Pipeline> m_pipeline;

			double m_deltaTime = 0.0;

			std::vector<unsigned int> m_gameLevels;
			unsigned int m_currentGameLevel;
			std::vector<std::pair<glm::vec3, glm::vec3>> m_cameraPresets; //per level
			double m_accumulator;
			double m_maxTimeStep;
			double m_simulationTime;
			std::string m_jsonPath;
			glm::ivec2 m_windowSize;
		};
	}
}

#endif
