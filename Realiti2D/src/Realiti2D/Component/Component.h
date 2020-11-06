#pragma once

namespace Realiti2D {
	class Entity;

	class Component {
	public:
		Entity* Owner;

		Component() {}
		virtual ~Component		() {}
		virtual void Initialize	() {}
		virtual void BeginPlay	() {}
		virtual void Update		(float DeltaTime) {}
		virtual void Render		() {}
		virtual void Destroy	() {}
	};
}