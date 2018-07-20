#include "IEffect.h"

using namespace FME::Graphics;


IEffect::IEffect()
{
	
}

void IEffect::SetInputBuffer()
{

}



void IEffect::SetInputTextures(const std::vector<std::string>& textureNames)
{
	m_inputTextureNames = textureNames;
}



IEffect::~IEffect()
{

}