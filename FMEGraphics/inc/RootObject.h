#ifndef ROOTOBJECT_H_
#define ROOTOBJECT_H_

#include "GameObject.h"

namespace FME
{
	namespace Graphics
	{
		/** \class RootObject
		*  \brief A class that implements the root node in a scengraph
		*/

		class RootObject : public GameObject
		{
		public:
			virtual void Draw();
			virtual void Update();

		
		private:
			std::vector<std::shared_ptr<GameObject>> m_children;
		};
	}
}


#endif

