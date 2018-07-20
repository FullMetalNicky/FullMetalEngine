#ifndef IEFFECT_H_
#define IEFFECT_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "GeometryMesh.h"

namespace FME
{
	namespace Graphics
	{
		/** \class IEffect
		*  \brief An interface for shader effects.
		*/

		class IEffect 
		{
		public:
			IEffect();
			virtual ~IEffect();

			virtual void RenderStart() = 0;
			virtual void RenderEnd() = 0;
			virtual void RenderToScreen() = 0;

			void SetInputBuffer();
			void SetInputTextures(const std::vector<std::string>& textureNames);

			GLuint GetOutputBuffer() const { return m_outputFrameBuffer; };
			std::vector<std::string> GetOutputTextures() const { return m_outputTextureNames; };

		protected:
			
			std::vector<std::string> m_inputTextureNames;
			std::vector<std::string> m_outputTextureNames;
			std::shared_ptr<FME::Graphics::GeometryMesh> m_renderQuad;

			GLuint m_inputFrameBuffer;
			GLuint m_outputFrameBuffer;
		};

	}
}

#endif

