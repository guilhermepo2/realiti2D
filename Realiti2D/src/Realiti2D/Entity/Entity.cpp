#include "Entity.h"
#include "Realiti2D/Log.h"
#include "Realiti2D/Renderer/Renderer.h"
#include "Realiti2D/Component/Component.h"
#include "Realiti2D/Component/TransformComponent.h"
#include "Realiti2D/Component/Sprite.h"

namespace Realiti2D {
	Entity::Entity(std::string InName) : Name(InName) {}

	void Entity::BeginPlay() {
		for (Component* c : m_Components) {
			c->BeginPlay();
		}
	}

	void Entity::ProcessInput(const InputState& CurrentInputState) {
		for (Component* c : m_Components) {
			c->ProcessInput(CurrentInputState);
		}
	}

	void Entity::Update(float DeltaTime) {
		for (Component* c : m_Components) {
			c->Update(DeltaTime);
		}
	}

	void Entity::Render() {

		// Should this really be here?!
		if (HasComponentOfType<Transform>() && HasComponentOfType<Sprite>()) {
			Transform* t = GetComponentOfType<Transform>();
			Sprite* s = GetComponentOfType<Sprite>();

			Renderer::s_Instance->AddToRenderQueue(s->tex, &(t->Position), t->Rotation, &(t->Scale), s->DrawOrder);
		}

		for (Component* c : m_Components) {
			c->Render();
		}
	}

	void Entity::Destroy() {
		for (Component* c : m_Components) {
			c->Destroy();
		}

		// TODO: Properly destroy and mark for destruction ?!
		this->m_bIsActive = false;
	}
}