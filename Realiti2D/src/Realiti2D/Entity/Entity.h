#pragma once
#include <string>
#include <vector>
#include <map>
#include <typeinfo>

namespace Realiti2D {
	class Component;
	struct InputState;

	class Entity {
	public:
		std::string Name;
		Entity(std::string InName);
		// TODO: Layer Type (?!) and EntityManager (maybe)
		
		inline bool IsActive() const { return m_bIsActive; }

	protected:
		bool m_bIsActive;
		std::vector<Component*> m_Components;
		std::map<const std::type_info*, Component*> m_TypeInfoToComponentMap;

	public:
		virtual void BeginPlay();
		virtual bool ProcessInput(const InputState& CurrentInputState);
		virtual void Update(float DeltaTime);
		virtual void Render();
		virtual void Destroy();

		template<typename T, typename... TArgs>
		T& AddComponent(TArgs&&... Args) {
			T* NewComponent(new T(std::forward<TArgs>(Args)...));
			NewComponent->Owner = this;
			m_Components.push_back(NewComponent);
			m_TypeInfoToComponentMap[&typeid(*NewComponent)] = NewComponent;
			NewComponent->Initialize();
			return *NewComponent;
		}

		template<typename T>
		T* GetComponentOfType() {
			return static_cast<T*>(m_TypeInfoToComponentMap[&typeid(T)]);
		}

		template<typename T>
		bool HasComponentOfType() const {
			return m_TypeInfoToComponentMap.count(&typeid(T));
		}
	};
}