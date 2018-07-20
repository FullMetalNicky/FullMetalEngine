#ifndef ICOMPONENT_H_
#define ICOMPONENT_H_

#include <string>

namespace FME
{
	namespace Graphics
	{
		/** \class ICamera
		*  \brief general interface for a component.
		*/

		class IComponent
		{
		public:

			virtual ~IComponent() {};

			virtual void Update() {};

			virtual void Draw() {};

			const std::string& GetType() const { return m_type; };

		protected:

			std::string m_type = "";
		};
	}
}

#endif
