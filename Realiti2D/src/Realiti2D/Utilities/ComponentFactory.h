#pragma once
#include <rapidjson/document.h>

namespace Realiti2D {

	class Entity;

	class ComponentFactory {
	public:
		static void AddTransformComponent(Entity& e, const rapidjson::Value& TransformComponentJSON);
		static void AddSpriteComponent(Entity& e, const rapidjson::Value& SpriteComponentJSON);
		static void AddAnimatedSpriteComponent(Entity& e, const rapidjson::Value& AnimatedSpriteComponentJSON);
	};
}