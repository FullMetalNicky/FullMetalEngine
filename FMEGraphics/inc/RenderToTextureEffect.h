#ifndef NOEFFECT_H_
#define NOEFFECT_H_

#include "IEffect.h"

namespace FME
{
	namespace Graphics
	{
		/** \class RenderToTextureEffect
		*  \brief A class for simple, no effect rendering. Can render to texture, or to screen. 
		*/

		class RenderToTextureEffect : public IEffect
		{
		public:
			RenderToTextureEffect(glm::ivec2 screenSize);
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
