#ifndef IRENDERCOMPONENT_H_
#define IRENDERCOMPONENT_H_

#include "IComponent.h"
#include "IModel.h"

namespace FME
{
	namespace Graphics
	{
		/*enum GameType
		{
			RENDER2D,
			RENDER3D
		};*/


		/** \class RenderComponent
		*  \brief a component dedicated to rendering objects
		*/
		class RenderComponent : public IComponent
		{
		public:

			RenderComponent(std::shared_ptr<IModel> model);

			virtual void Update();

			virtual void Draw();

			std::string GetShaderName() const;

			virtual void SetGameType(GameType type) { m_gameType = type; };

			virtual GameType GetGameType() const { return m_gameType; };

		private:

			std::shared_ptr<IModel> m_model;
			GameType m_gameType;
		};
	}
}

#endif