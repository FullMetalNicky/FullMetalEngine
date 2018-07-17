#ifndef NOEFFECT_H_
#define NOEFFECT_H_

#include "IEffect.h"

namespace FME
{
	namespace Graphics
	{
		/** \class NoEffect
		*  \brief A class for simple, no effect rendering. Can render to texture, or to screen. 
		*/

		class NoEffect : public IEffect
		{
		public:
			NoEffect(glm::ivec2 screenSize);
			virtual ~NoEffect();

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
