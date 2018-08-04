#ifndef PIPELINE_H_
#define PIPELINE_H_

#include "IEffect.h"
#include "SceneObject.h"

#include <map>

namespace FME
{
	namespace Graphics
	{
		/** \class Pipeline
		*  \brief A class that should act as the manager of IEffects in the engine.
		*/

		struct EffectParams
		{
			std::shared_ptr<IEffect> effect;
			std::string type;
			std::string Id;
			int activeCamera;
			bool draw;
			//std::vector<ViewPortParams> viewPortParams;
		};

		class Pipeline
		{
		public:
			Pipeline(const glm::ivec2 & windowSize);
			virtual~Pipeline();

			virtual void Update();
			virtual void ClearScreen();
			virtual void Render(const std::shared_ptr<SceneObject>& scene);

			void AddEffect(EffectParams effect);


		protected:

			std::string m_currentEffect;
			std::vector<EffectParams> m_effects;
			glm::ivec2 m_windowSize;
		};
	}
}
#endif
