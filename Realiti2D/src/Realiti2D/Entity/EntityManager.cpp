#include "EntityManager.h"
#include "Entity.h"

namespace Realiti2D {
	void EntityManager::BeginPlay() {
		for (Entity* e : m_Entities) {
			e->BeginPlay();
		}
	}

	void EntityManager::Update(float DeltaTime) {
		for (Entity* e : m_Entities) {
			e->Update(DeltaTime);
		}
	}

	void EntityManager::Render() {
		for (Entity* e : m_Entities) {
			e->Render();
		}
	}

	void EntityManager::Destroy() {
		for (Entity* e : m_Entities) {
			e->Destroy();
		}
	}

	Entity& EntityManager::AddEntity(std::string EntityName) {
		Entity* NewEntity = new Entity(EntityName);
		m_Entities.push_back(NewEntity);
		return *NewEntity;
	}
}