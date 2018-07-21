#ifndef PIPELINE_H_
#define PIPELINE_H_

#include "IEffect.h"
#include <map>

namespace FME
{
	namespace Graphics
	{
		/** \class Pipeline
		*  \brief A class that should act as the manager of IEffects in the engine.
		*/

		class Pipeline
		{
		public:
			Pipeline();
			virtual~Pipeline();

			virtual void Update();
			virtual void RenderToScreen();
			virtual void RenderStart(const std::string& currentEffectName);
			virtual void RenderEnd();
			virtual void ClearScreen();

			void AddEffect(std::shared_ptr<IEffect> effect, const std::string& effectName);


		protected:

			std::string m_currentEffect;
			std::map<std::string, std::shared_ptr<IEffect>> m_effects;
		};
	}
}
#endif
