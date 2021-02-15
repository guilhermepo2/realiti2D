#include "ComponentFactory.h"
#include "JsonHelper.h"

#include "Realiti2D/Log.h"
#include "Realiti2D/Math/Math.h"
#include "Realiti2D/Entity/Entity.h"
#include "Realiti2D/Component/TransformComponent.h"
#include "Realiti2D/Component/Sprite.h"
#include "Realiti2D/Component/AnimatedSprite.h"
#include "Realiti2D/Component/BoxCollider.h"

namespace Realiti2D {
	void ComponentFactory::AddTransformComponent(Entity& e, const rapidjson::Value& TransformComponentJSON) {
		if (TransformComponentJSON.HasMember("properties")) {
			CORE_INFO("[COMPONENT FACTORY] Adding Transform Component");
			const rapidjson::Value& Properties = TransformComponentJSON["properties"];
			// Get Position
			Vector2 Position;
			JsonHelper::GetVector2(Properties, "position", Position);

			// Get Rotation
			float Rotation = 0;
			JsonHelper::GetFloat(Properties, "rotation", Rotation);

			// Get Scale
			Vector2 Scale;
			JsonHelper::GetVector2(Properties, "scale", Scale);

			e.AddComponent<Realiti2D::Transform>(Position, Rotation, Scale);
		}

	}

	void ComponentFactory::AddSpriteComponent(Entity& e, const rapidjson::Value& SpriteComponentJSON) {
		CORE_INFO("[COMPONENT FACTORY] Adding Sprite Component");
		std::string SpritePath;
		JsonHelper::GetString(SpriteComponentJSON, "path", SpritePath);
		int DrawOrder = 0;
		JsonHelper::GetInt(SpriteComponentJSON, "drawOrder", DrawOrder);
		e.AddComponent<Realiti2D::Sprite>(SpritePath, DrawOrder);
	}

	void ComponentFactory::AddAnimatedSpriteComponent(Entity& e, const rapidjson::Value& AnimatedSpriteComponentJSON) {
		const rapidjson::Value& Properties = AnimatedSpriteComponentJSON["properties"];
		if (Properties.IsObject()) {

			int AnimationFPS;
			JsonHelper::GetInt(Properties, "animationFPS", AnimationFPS);

			std::vector<std::string> Textures;
			if (Properties.HasMember("textures")) {
				const rapidjson::Value& TexturesArray = Properties["textures"];
				if (TexturesArray.IsArray()) {
					for (rapidjson::SizeType i = 0; i < TexturesArray.Size(); i++) {
						Textures.push_back(TexturesArray[i].GetString());
					}
				}
			}

			Realiti2D::AnimatedSprite& AnimationComponent = e.AddComponent<Realiti2D::AnimatedSprite>();
			// TODO: THIS IS BROKEN!
			// the structure of animation component changed to allow having more than one animation
			/*
			AnimationComponent.SetAnimationFPS(AnimationFPS);
			for (int i = 0; i < Textures.size(); i++) {
				AnimationComponent.AddAnimationTexture(Textures[i]);
			}
			*/

		}
	}

	void ComponentFactory::AddBoxColliderComponent(Entity& e, const rapidjson::Value& BoxColliderComponentJSON) {
		if (BoxColliderComponentJSON.HasMember("properties")) {
			const rapidjson::Value& Properties = BoxColliderComponentJSON["properties"];
			Vector2 MinBounds;
			JsonHelper::GetVector2(Properties, "min", MinBounds);
			Vector2 MaxBounds;
			JsonHelper::GetVector2(Properties, "max", MaxBounds);

			e.AddComponent<Realiti2D::BoxCollider>(MinBounds, MaxBounds);
		}
	}
}