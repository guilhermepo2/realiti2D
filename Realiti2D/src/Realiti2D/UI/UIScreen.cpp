#include "UIScreen.h"
#include "Realiti2D/Entity/Entity.h"

namespace Realiti2D {
	UIScreen::UIScreen() {}
	UIScreen::~UIScreen() {}

	void UIScreen::Initialize() {}
	void UIScreen::Destroy() {}
	void UIScreen::BeginPlay() {}
	void UIScreen::Update(float DeltaTime) {}
	bool UIScreen::ProcessInput(const InputState& CurrentInputState) { return false; }

	void UIScreen::Render() {
		for (Entity* e : m_UIEntities) {
			e->Render();
		}
	}

	void UIScreen::AddTextElement(const std::string& Name, Vector2 Position, const std::string& FontAsset) {
		// TODO: Add here a callback "update text" with a value?
		// add a key to update the text element? it HAS to be updated somehow lol
		// maybe a value to watch?

		Entity* e = new Entity(Name);
		e->AddComponent<Transform>(Position, 0.0f, Vector2(1.0f, 1.0f));
		FontComponent& fc = e->AddComponent<FontComponent>(FontAsset);
		fc.UpdateText("Points: 0");

		m_UIEntities.push_back(e);
	}
}