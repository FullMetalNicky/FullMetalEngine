#ifndef FULLMETALENGINE_H_
#define FULLMETALENGINE_H_

#include <string>

namespace FME
{
	namespace Graphics
	{
		class FullMetalEngine
		{
		public:

			bool Alive();
			void Update(double deltaTime);
			void Draw();

			void SetWindowSize(int windowWidth, int windowHeight);
			void SetScene(const std::string& jsonPath);
			void SetEffects(const std::string& jsonPath);

			void SetFPS(double fps);
		};
	}
}


#endif
