#ifndef VIEWPORTEEFFECT_H_
#define VIEWPORTEEFFECT_H_

#include "IEffect.h"

namespace FME
{
	namespace Graphics
	{
		/** \class ViewPortEffect
		*  \brief A class for simple texture rendering. Can output the texture to the screen too.
		*/

		struct ViewPortParams
		{
			std::string textureName;
			glm::vec4 textureCropParams; // (x, y, width, height)
			glm::vec4 texturePositionParams; // (x, y, width, height)
		};


		class ViewPortEffect : public IEffect
		{
		public:
			ViewPortEffect(glm::ivec2 screenSize, const std::vector<ViewPortParams>& viewPortParams);
			virtual ~ViewPortEffect();

			virtual void RenderStart();
			virtual void RenderEnd();
			virtual void RenderToScreen();

		private:

			std::string parseShaderParam(const std::string& paramName, int index);


			GLuint m_frameBuffer;
			GLuint m_renderBuffer;
			std::string m_screenShaderName;
			std::vector<ViewPortParams> m_viewPortParams;
		};

	}
}
#endif