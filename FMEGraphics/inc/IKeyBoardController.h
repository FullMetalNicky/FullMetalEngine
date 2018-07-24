#ifndef IKEYBOARDCONTROLLER_H_
#define IKEYBOARDCONTROLLER_H_

#include "IController.h"
#include <vector>

namespace FME
{
	namespace Graphics
	{
		class IKeyBoardController : public IController
		{
		public:
			void SetControlKeys(const std::vector<char>& keys);

		protected:
			std::vector<char> m_keys;
		};
	}
}


#endif