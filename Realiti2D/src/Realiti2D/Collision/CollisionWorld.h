#pragma once
#include <vector>

namespace Realiti2D {

	class BoxCollider;

	class CollisionWorld {
	public:
		CollisionWorld();
		~CollisionWorld();

		static CollisionWorld* s_Instance;

		bool Initialize();
		void Draw();
		void Shutdown();

		void VerifyAllCollisions();
		void AddColliderToWorld(BoxCollider* Collider);
		void RemoveColliderFromWorld(BoxCollider* Collider);

	private:
		std::vector<BoxCollider*> m_WorldColliders;
		bool Overlaps(BoxCollider* a, BoxCollider* b);
	};
}