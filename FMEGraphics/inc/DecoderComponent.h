#ifndef DECODERCOMPONENT_H_
#define DECODERCOMPONENT_H_

#include "IComponent.h"
#include "SharedQueue.h"
#include <memory>
#include <vector>

namespace FME
{
	namespace Graphics
	{
		struct DataBuffer
		{
			//std::vector<unsigned char> data;
			std::vector<unsigned char*> dataVec;
			unsigned int width;
			unsigned int height;
			bool alpha;
			int frameNum;
		};

		class DecoderComponent : public IComponent
		{
		public:
			DecoderComponent(const std::string& textureName);

			void Update();

			void PushFrame(const DataBuffer& buffer);

		private:
			std::shared_ptr<FME::Utilities::SharedQueue<DataBuffer>> m_queue;
			std::string m_textureName;
		};
	}
}



#endif
