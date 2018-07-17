#ifndef IMODEL_H_
#define IMODEL_H_

#include "IMesh.h"
#include "Shader.h"

namespace FME
{
	namespace Graphics
	{

		enum GameType
		{
			RENDER2D,
			RENDER3D
		};

		/** \class IModel
		*  \brief An interface class for all model - containing meshes and the appropraite shader.
		*/

		class IModel
		{
		public:

			IModel() {};
			virtual ~IModel();

			virtual void Update();
			virtual void Draw() = 0;
		
			virtual void SetGameType(GameType type) { m_gameType = type; };
			virtual GameType GetGameType() { return m_gameType; };
			virtual std::string GetShaderName() const { return m_shaderName; };
			virtual void SetRenderState(bool state) { m_render = state; };
			virtual bool GetRenderState() { return m_render; };
			 
		protected:

			std::vector<std::shared_ptr<IMesh>> m_meshes;
			std::string m_shaderName;
			GLuint m_instancing;
			GameType m_gameType;
			bool m_render;
		};
	}
}
#endif 
