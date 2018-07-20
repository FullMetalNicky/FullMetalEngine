#ifndef BLOOMEFFECT_H_
#define BLOOMEFFECT_H_

#include "IEffect.h"
#include <map>

namespace FME
{
	namespace Graphics
	{
		/** \class BloomEffect
		*  \brief A class that implements a bloom effect via shaders - identifying the the objects with the highest luma and creating
		* a blurred aura around then using a second pass of Gaussian blur
		*/

		class BloomEffect : public IEffect
		{
		public:
			BloomEffect(glm::ivec2 screenSize);
			virtual ~BloomEffect();

			virtual void RenderStart();
			virtual void RenderEnd();
			virtual void RenderToScreen();

		private:
			
			
			GLuint m_hdrFBO;
			GLuint m_hdrFBOAfterHPF;
			GLuint m_rboDepth;
			GLuint m_rboDepthAfterHPF;
			GLuint m_pingpongFBO[2];
			
			glm::uvec2 m_windowSize;
			std::string m_screenShaderName;
			std::string m_bloomEffectShader;
			std::string m_guassianShader;
			std::string m_HPFShader;
			std::map<std::string, std::shared_ptr<Texture2D>> m_textures;
		};

	}
}

#endif

