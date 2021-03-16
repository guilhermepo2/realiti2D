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
}