#ifndef RENDERTOTEXTUREEFFECT_H_
#define RENDERTOTEXTUREEFFECT_H_

#include "IEffect.h"

namespace FME
{
	namespace Graphics
	{
		/** \class RenderToTextureEffect
		*  \brief A class for simple texture rendering. Can output the texture to the screen too.
		*/

		class RenderToTextureEffect : public IEffect
		{
		public:
			RenderToTextureEffect(glm::ivec2 screenSize, const std::string& textureName = "");
			virtual ~RenderToTextureEffect();

			virtual void RenderStart();
			virtual void RenderEnd();
			virtual void RenderToScreen();

		private:
		
			GLuint m_frameBuffer;
			GLuint m_renderBuffer;			
			std::string m_screenShaderName;
		};

	}
}
#endif
