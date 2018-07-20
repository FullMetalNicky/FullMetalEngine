#ifndef PIPELINE_H_
#define PIPELINE_H_

#include "IEffect.h"
#include "IModel.h"


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
			~Pipeline();

			void Update();
			void Draw();


		private:

			std::vector<std::shared_ptr<IEffect>> m_effects;
		};
	}
}
#endif
