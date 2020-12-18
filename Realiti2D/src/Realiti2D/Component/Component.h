#pragma once

namespace Realiti2D {
	class Entity;
	struct InputState;

	class Component {
	public:
		Entity* Owner;

		Component() {}
		virtual ~Component		() {}
		virtual void Initialize	() {}
		virtual void BeginPlay	() {}
		virtual void ProcessInput(const InputState& CurrentInputState) {}
		virtual void Update		(float DeltaTime) {}
		virtual void Render		() {}
		virtual void Destroy	() {}
	};
}