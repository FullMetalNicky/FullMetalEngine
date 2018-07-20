#ifndef TRANSFORMCOMPONENT_H_
#define TRANSFORMCOMPONENT_H_

#include <glm/glm.hpp>
#include "IComponent.h"
#include <memory>


namespace FME
{
	namespace Graphics
	{
		struct Transform {
			glm::vec3 Translation;
			glm::vec3 Rotation;
			glm::vec3 Scale;
		};

		/** \class TransformComponent
		*  \brief A class implementing a transform component, indicating the location, orientation and scale of each IObject in a 3D world. 
		*/

		class TransformComponent : public IComponent
		{
		public:

			TransformComponent();

			virtual void Update();

			void ResetTransform();
			void SetTransform(const Transform& transform);
			void SetFixedTransform(const Transform& transform);

			void SetScale(glm::vec3 scale) { m_scale = scale; };
			void SetRotation(glm::vec3 rotation) { m_rotation = rotation; };
			void SetTranslation(glm::vec3 translation) { m_translation = translation; };
			void SetParent(const std::shared_ptr<TransformComponent>& parent) { m_parent = parent; };

			glm::vec3 GetScale() const { return m_scale; };
			glm::vec3 GetRotation() const { return m_rotation; };
			glm::vec3 GetTranslation() const { return m_translation; };
			const Transform& GetTransform() const { return m_transform; };
			glm::mat4 GetModelMatrix() const;

			bool IsFixed() const { return m_fixedTransform; };

		private:

			Transform m_transform;
			glm::vec3 m_translation;
			glm::vec3 m_rotation;
			glm::vec3 m_scale;
			bool m_fixedTransform = false;
			std::shared_ptr<TransformComponent> m_parent = nullptr;
		};
	}
}
#endif