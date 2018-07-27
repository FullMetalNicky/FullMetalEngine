#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include <memory>

#include "EffectLoader.h"
#include "Engine.h"


#ifdef _DEBUG
#define DEBUG 1
#endif
#ifndef _DEBUG
#define DEBUG 0
#endif


using namespace FME::Graphics;


EffectLoader::EffectLoader(const std::string& JSONPath)
{
	std::ifstream is(JSONPath, std::ifstream::in);

	if (is)
	{
		is.seekg(0, is.end);
		int length = is.tellg();
		is.seekg(0, is.beg);

		std::shared_ptr<char> buffer(new char[length]);
		is.read(buffer.get(), length);

		if (is) std::cout << "all characters read successfully.";
		else std::cout << "error: only " << is.gcount() << " could be read" << std::endl;
		is.close();

		std::string str = std::string(buffer.get());
		std::string out = parse(m_root, str);

		if (!m_root.is<picojson::object>())
		{
			std::cerr << "file is not a json file!" << std::endl;
		}
	}
	else
	{
		std::cerr << "could not find json file!" << std::endl;
	}
}


void EffectLoader::LoadEffects(std::shared_ptr<Pipeline>& pipeline)
{
	glm::ivec2 windowSize = Engine::Instance()->GetWindowSize();
	picojson::value::object& rootObj = m_root.get<picojson::object>();
	if (m_root.contains("Effects"))
	{
		picojson::value effects = m_root.get("Effects");
		if (effects.is<picojson::array>())
		{
			picojson::array arr = effects.get<picojson::array>();
			for (int i = 0; i < arr.size(); ++i)
			{
				picojson::value::object& arrObj = arr[i].get<picojson::object>();
				EffectParams ep;				

				for (picojson::value::object::const_iterator it = arrObj.begin(); it != arrObj.end(); ++it)
				{
					if (DEBUG) std::cout << it->first << " : " << it->second.to_str() << std::endl;
					if (it->first == "Type")
					{
						ep.type = it->second.to_str();
					}
					else if (it->first == "Id")
					{
						ep.Id = it->second.to_str();
					}
					else if (it->first == "Draw")
					{						
						ep.draw = std::stoi(it->second.to_str());
					}
					else if (it->first == "ActiveCamera")
					{
						ep.activeCamera = std::stoi(it->second.to_str());
					}
				}
				pipeline->AddEffect(ep);
			}
		}
	}
}