#pragma once
#include <vector>
#include "Realiti2D/Math/Math.h"

namespace Realiti2D {
	class BoxCollider;
	class Entity;
	struct LineSegment;

	struct CollisionInfo {
		Vector2 PointOfCollision;
		Vector2 CollisionNormal; // unused (so far)
		BoxCollider* CollidedWith; // Box Collider that collided WITH
		Entity* CollidedEntity; // Entity that owns the box collider
	};

	class CollisionWorld {
	public:
		CollisionWorld();
		~CollisionWorld();

		static CollisionWorld* s_Instance;

		bool Initialize();
		void Render();
		void Shutdown();

		void VerifyAllCollisions();
		bool SegmentCast(Vector2 StartingPoint, Vector2 EndingPoint, CollisionInfo& OutCollisionInfo);

		void AddColliderToWorld(BoxCollider* Collider);
		void RemoveColliderFromWorld(BoxCollider* Collider);


	private:
		std::vector<BoxCollider*> m_WorldColliders;
		bool Overlaps(BoxCollider* a, BoxCollider* b);
	};
}