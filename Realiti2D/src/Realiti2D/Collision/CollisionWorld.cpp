#pragma once
#include "CollisionWorld.h"
#include "Collider.h"
#include "LineSegment.h"
#include "Realiti2D/Component/BoxCollider.h"
#include "Realiti2D/Math/Math.h"
#include "Realiti2D/Renderer/Renderer.h"

namespace Realiti2D {
	CollisionWorld* CollisionWorld::s_Instance = nullptr;

	CollisionWorld::CollisionWorld() {}
	CollisionWorld::~CollisionWorld() {}

	bool CollisionWorld::Initialize() {
		if (s_Instance != nullptr) {
			CORE_ERROR("[collision world] are you trying to create two collision worlds?");
			return false;
		}

		s_Instance = this;
		return true;
	}

	// This is mostly a debug feature, should be called only when a certain conditional is true by the application!
	void CollisionWorld::Render() {
		for (size_t i = 0; i < m_WorldColliders.size(); i++) {
			if (m_WorldColliders[i]->GetTransform() != nullptr) {
				AABB* ColliderAABB = m_WorldColliders[i]->GetBoundingBox();

				// TODO: there can be a problem here in case min point is bigger than the max point
				// which in this case, the min is the max, and this should never happen
				// but... you know... stuff happens...
				int Width = Math::Abs(ColliderAABB->MinPoint.x - ColliderAABB->MaxPoint.x);
				int Height = Math::Abs(ColliderAABB->MinPoint.y - ColliderAABB->MaxPoint.y);

				Renderer::s_Instance->AddQuadToRenderQueue(&(m_WorldColliders[i]->GetTransform()->Position), Width, Height, &(m_WorldColliders[i]->GetTransform()->Scale));
			}
		}


	}

	void CollisionWorld::Shutdown() {}
	
	// TODO: Add a raycast function that checks if the cast intersects with any of the box colliders! return a collision info struct

	void CollisionWorld::VerifyAllCollisions() {
		for (size_t i = 0; i < m_WorldColliders.size(); i++) {
			for (size_t j = i + 1; j < m_WorldColliders.size(); j++) {
				BoxCollider* a = m_WorldColliders[i];
				BoxCollider* b = m_WorldColliders[j];
				
				if (Overlaps(a, b)) {
					// CORE_INFO("{0} collided with {1}", a->Owner->Name, b->Owner->Name);
					a->HandleCollisionCallback(b);
					b->HandleCollisionCallback(a);
				}

			}
		}
	}

	bool CollisionWorld::SegmentCast(Vector2 StartingPoint, Vector2 EndingPoint, CollisionInfo& OutCollisionInfo) {

		bool bCollided = false;
		LineSegment l(StartingPoint, EndingPoint);
		float closestT = Math::FloatInfinity;

		// Test against all boxes
		for (BoxCollider* collider : m_WorldColliders) {
			float t;
			
			Vector2 AABBMin = collider->GetTransform()->Position;
			Vector2 MinPoint = collider->GetBoundingBox()->MinPoint;
			MinPoint.x *= collider->GetTransform()->Scale.x;
			MinPoint.y *= collider->GetTransform()->Scale.y;
			AABBMin += MinPoint;

			Vector2 AABBMax = collider->GetTransform()->Position;
			Vector2 MaxPoint = collider->GetBoundingBox()->MaxPoint;
			MaxPoint.x *= collider->GetTransform()->Scale.x;
			MaxPoint.y *= collider->GetTransform()->Scale.y;
			AABBMax += MaxPoint;
			AABB ColliderAABB = { AABBMin, AABBMax };

			// More Debug
			/*
			Vector2* m = new Vector2(AABBMin.x, AABBMin.y);
			Vector2* m2 = new Vector2(AABBMax.x, AABBMax.y);
			Renderer::s_Instance->AddQuadToRenderQueue(m, 2.0, 2.0f, &(collider->GetTransform()->Scale));
			Renderer::s_Instance->AddQuadToRenderQueue(m2, 2.0f, 2.0f, &(collider->GetTransform()->Scale));
			float Width = ((AABBMax.x - AABBMin.x));
			Vector2* m3 = new Vector2(AABBMax.x, AABBMax.y);
			m3->x -= Width / 2.0f;
			Width /= collider->GetTransform()->Scale.x;
			Renderer::s_Instance->AddQuadToRenderQueue(m3, Width, 1.0f, &(collider->GetTransform()->Scale));
			*/
			
			if (CheckLineCollision(l, ColliderAABB, t)) {
				// collided with something...
				if (t < closestT) {
					OutCollisionInfo.PointOfCollision = l.PointOnSegment(t);
					OutCollisionInfo.CollidedWith = collider;
					OutCollisionInfo.CollidedEntity = collider->Owner;
					bCollided = true;
				}
			}

		}

		return bCollided;
	}

	void CollisionWorld::AddColliderToWorld(BoxCollider* Collider) {
		m_WorldColliders.push_back(Collider);
	}

	void CollisionWorld::RemoveColliderFromWorld(BoxCollider* Collider) {
		std::vector<BoxCollider*>::iterator BoxColliderIterator = std::find(m_WorldColliders.begin(), m_WorldColliders.end(), Collider);

		if (BoxColliderIterator != m_WorldColliders.end()) {
			std::iter_swap(BoxColliderIterator, m_WorldColliders.end() - 1);
			m_WorldColliders.pop_back();
		}
	}

	bool CollisionWorld::Overlaps(BoxCollider* a, BoxCollider* b) {
		AABB a_AABB = {
			Vector2(a->GetTransform()->Position.x + a->GetBoundingBox()->MinPoint.x, a->GetTransform()->Position.y + a->GetBoundingBox()->MinPoint.y),
			Vector2(a->GetTransform()->Position.x + a->GetBoundingBox()->MaxPoint.x, a->GetTransform()->Position.y + a->GetBoundingBox()->MaxPoint.y),
		};
		
		AABB b_AABB = {
			Vector2(b->GetTransform()->Position.x + b->GetBoundingBox()->MinPoint.x, b->GetTransform()->Position.y + b->GetBoundingBox()->MinPoint.y),
			Vector2(b->GetTransform()->Position.x + b->GetBoundingBox()->MaxPoint.x, b->GetTransform()->Position.y + b->GetBoundingBox()->MaxPoint.y),
		};

		return CheckCollision(a_AABB, b_AABB);
	}
}