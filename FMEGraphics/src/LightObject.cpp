#include "LightObject.h"

using namespace FME::Graphics;

LightObject::LightObject()
{
	
}

void LightObject::SetShader(const std::string& shaderName)
{
	m_shaderName = shaderName;
}
