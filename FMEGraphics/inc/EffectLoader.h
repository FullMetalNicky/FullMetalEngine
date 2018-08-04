#ifndef EFFECTLOADER_H_
#define EFFECTLOADER_H_

#include <string>
#include "picojson.h"
#include "Pipeline.h"

namespace FME
{
	namespace Graphics
	{
		/** \class EffectLoader
		*  \brief A class that will read a json file, parse it and load the effects
		*/

		class EffectLoader
		{
		public:
			EffectLoader(const std::string& JSONPath); //called only once in the beginning of the app, loading the pipeline

			void LoadEffects(std::shared_ptr<Pipeline>& pipeline);

		private:

			picojson::value m_root;
		};
	}
}



#endif