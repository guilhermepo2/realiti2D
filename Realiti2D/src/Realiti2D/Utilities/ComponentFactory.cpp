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

			Realiti2D::AnimatedSprite& AnimationComponent = e.AddComponent<Realiti2D::AnimatedSprite>();
			// Iterate throught animation list, animation contains: name, FPS, shouldloop, and a list of textures
			const rapidjson::Value& AnimationList = Properties["animationList"];
			if (AnimationList.IsArray()) {
				for (auto& AnimationObject : AnimationList.GetArray()) {
					int AnimationFPS;
					bool bShouldLoop;
					JsonHelper::GetInt(AnimationObject, "animationFPS", AnimationFPS);
					JsonHelper::GetBool(AnimationObject, "shouldLoop", bShouldLoop);

					AnimationClip* anim = new AnimationClip(AnimationFPS, bShouldLoop);

					if (AnimationObject["animationTextures"].IsArray()) {
						for (auto& texture : AnimationObject["animationTextures"].GetArray()) {
							anim->AddAnimationTexture(texture.GetString());
						}
					}

					std::string AnimationName;
					JsonHelper::GetString(AnimationObject, "animationName", AnimationName);
					AnimationComponent.AddAnimationClip(AnimationName, anim);
				}
			}

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