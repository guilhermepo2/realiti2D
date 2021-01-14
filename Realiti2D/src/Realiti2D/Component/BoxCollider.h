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

		inline AABB* GetBoundingBox()  { return &m_AABB; }
		inline Transform* GetTransform() { return m_TransformReference; }
		
		void CollisionCallback() {
			if (m_CollisionCallback) {
				m_CollisionCallback();
			}
		}

	private:
		AABB m_AABB;
		Transform* m_TransformReference;
		std::function<void()> m_CollisionCallback;
	};

}