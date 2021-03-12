#pragma once
#include "Realiti2D/Component/Component.h"
#include "Realiti2D/Component/TransformComponent.h"
#include "Realiti2D/Entity/Entity.h"
#include "Realiti2D/Collision/Collider.h"
#include "Realiti2D/Collision/CollisionWorld.h"

#define BIND_COLLISION(...) std::bind(__VA_ARGS__, this, std::placeholders::_1);

namespace Realiti2D {
	
	class BoxCollider : public Component {
	public:
		BoxCollider(const Vector2& MinPoint, const Vector2& MaxPoint) {
			m_AABB.MinPoint = MinPoint;
			m_AABB.MaxPoint = MaxPoint;
			CollisionWorld::s_Instance->AddColliderToWorld(this);
		}

		BoxCollider(std::string ColliderTag, const Vector2& MinPoint, const Vector2& MaxPoint) : BoxCollider(MinPoint, MaxPoint) {
			m_ColliderTag = ColliderTag;
		}

		~BoxCollider() {
			CollisionWorld::s_Instance->RemoveColliderFromWorld(this);
		}

		virtual void BeginPlay() {
			m_TransformReference = Owner->GetComponentOfType<Transform>();
		}

		inline AABB* GetBoundingBox()  { return &m_AABB; }
		inline Transform* GetTransform() { return m_TransformReference; }
		
		void HandleCollisionCallback(BoxCollider* Other) {
			if (CollisionCallback) {
				CollisionCallback(Other);
			}
		}

		std::function<void(BoxCollider*)> CollisionCallback;
		const std::string& GetTag() const { return m_ColliderTag; }
	private:
		AABB m_AABB;
		Transform* m_TransformReference;
		std::string m_ColliderTag;
	};

}