#pragma once
#include <vector>
#include <string>

namespace Realiti2D {

	class Entity;
	struct InputState;

	class EntityManager {
	public:
		void BeginPlay();
		void ProcessInput(const InputState& CurrentInputState);
		void Update(float DeltaTime);
		void Render();
		void Destroy();

		Entity& AddEntity(std::string EntityName);
		// TODO: Get Entities?
		inline int GetEntitiesCount() const { return m_Entities.size(); }
		inline bool HasEntities() const { return m_Entities.size() > 0; }
		Entity* GetEntityByName(const std::string& EntityName);

	private:
		std::vector<Entity*> m_Entities;
	};
}