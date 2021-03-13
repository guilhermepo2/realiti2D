#pragma once
#include "Realiti2D/Layer/GameLayer.h"
#include "Realiti2D/UI/FontComponent.h"

namespace Realiti2D {

	class GameLayer;

	class UIScreen {
	public:
		enum EUIState {
			EActive,
			EClosing
		};

		UIScreen();
		~UIScreen();

		void Initialize();
		void Destroy();
		void BeginPlay();
		void Update(float DeltaTime);
		bool ProcessInput(const InputState& CurrentInputState);
		void Render();

		void AddTextElement(const std::string& Name, Vector2 Position, const std::string& FontAsset);
	private:
		// TODO: Have UI Entity?
		std::vector<Entity*> m_UIEntities;
		EUIState m_UIState;
	};
}