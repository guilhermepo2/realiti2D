#include "EntityManager.h"
#include "Entity.h"

namespace Realiti2D {
	void EntityManager::BeginPlay() {
		for (Entity* e : m_Entities) {
			e->BeginPlay();
		}
	}

	bool EntityManager::ProcessInput(const InputState& CurrentInputState) {
		for (Entity* e : m_Entities) {
			if (e->ProcessInput(CurrentInputState)) {
				return true;
			}
		}

		return false;
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

	Entity* EntityManager::GetEntityByName(const std::string& EntityName) {
		for (int i = 0; i < m_Entities.size(); i++) {
			if (m_Entities[i]->Name == EntityName) {
				return m_Entities[i];
			}
		}

		return nullptr;
	}
}