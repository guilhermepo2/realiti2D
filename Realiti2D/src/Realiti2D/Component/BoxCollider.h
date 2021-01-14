#pragma once
#include "Realiti2D/Component/Component.h"
#include "Realiti2D/Component/TransformComponent.h"
#include "Realiti2D/Entity/Entity.h"
#include "Realiti2D/Collision/Collider.h"
#include "Realiti2D/Collision/CollisionWorld.h"

#include "Realiti2D/Renderer/Renderer.h"

namespace Realiti2D {
	
	class BoxCollider : public Component {
	public:
		BoxCollider(const Vector2 MinPoint, const Vector2& MaxPoint) {
			m_AABB.MinPoint = MinPoint;
			m_AABB.MaxPoint = MaxPoint;
			CollisionWorld::s_Instance->AddColliderToWorld(this);

		}

		~BoxCollider() {
			CollisionWorld::s_Instance->RemoveColliderFromWorld(this);
		}

		virtual void BeginPlay() {
			m_TransformReference = Owner->GetComponentOfType<Transform>();
		}

		void Render() {
			if (m_TransformReference != nullptr) {
				// TODO: there can be a problem here in case min point is bigger than the max point
				// which in this case, the min is the max, and this should never happen
				// but... you know... stuff happens...
				int Width = Math::Abs(m_AABB.MinPoint.x - m_AABB.MaxPoint.x);
				int Height = Math::Abs(m_AABB.MinPoint.y - m_AABB.MaxPoint.y);

				Renderer::s_Instance->AddQuadToRenderQueue(&(m_TransformReference->Position), Width, Height, &(m_TransformReference->Scale));
			}
		}

		inline AABB* GetBoundingBox()  { return &m_AABB; }
		inline Transform* GetTransform() { return m_TransformReference; }

	private:
		AABB m_AABB;
		Transform* m_TransformReference;
	};

}