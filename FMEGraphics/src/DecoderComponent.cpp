#include "DecoderComponent.h"
#include "ResourceManager.h"

using namespace FME::Graphics;


DecoderComponent::DecoderComponent(const std::string& textureName)
{
	m_queue = std::shared_ptr<FME::Utilities::SharedQueue<DataBuffer>>(new FME::Utilities::SharedQueue<DataBuffer>());
	m_textureName = textureName;
	m_type = "Decoder";
}

void DecoderComponent::PushFrame(const DataBuffer& buffer)
{ 
	m_queue->PushBack(buffer);
}

void DecoderComponent::Update()
{
	if (m_queue->Size())
	{
		DataBuffer buffer = m_queue->Front();

		ResourceManager::Instance()->GetTexture(m_textureName)->Update(buffer.width, buffer.height, buffer.dataVec, buffer.alpha);
		
		if (m_queue->Size() > 1)
		{
			m_queue->PopFront();
		}
	}
}