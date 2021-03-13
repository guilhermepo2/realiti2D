#pragma once
#include "Layer.h"
#include "Realiti2D/Entity/Entity.h"
#include "Realiti2D/Entity/EntityManager.h"

namespace Realiti2D {

	class CollisionWorld;
	class EntityManager;
	class UIScreen;

	class GameLayer : public Layer {
	public:
		void Initialize();
		void Destroy();

		void BeginPlay();
		void Update(float DeltaTime);
		bool OnSDLEvent(SDL_Event& Event);
		bool OnApplicationEvent(const InputState& CurrentInputState);
		void Render();

		Entity& AddEntity(std::string InName) { return m_EntityManager->AddEntity(InName); };
		Entity* GetEntityByName(std::string InName) { return m_EntityManager->GetEntityByName(InName); }

		inline void PushUIScreen(UIScreen* ui) { m_UIScreenStack.push_back(ui); }

	private:
		std::vector<UIScreen*> m_UIScreenStack;
		EntityManager* m_EntityManager;
		CollisionWorld* m_CollisionWorld;
		bool m_bShowDebugColliders;
	};
}