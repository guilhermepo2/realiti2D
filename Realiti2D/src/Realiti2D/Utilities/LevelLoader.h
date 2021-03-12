#pragma once
#include <string>
#include <rapidjson/document.h>

namespace Realiti2D {

	class Application;
	class Entity;
	class GameLayer;

	class LevelLoader {
	public:
		static bool LoadLevel(GameLayer* TheGameLayer, std::string FileName);
		static bool LoadJSON(const std::string& FileName, rapidjson::Document& OutDocument);

	private:
		static void LoadGlobalProperties	(const rapidjson::Value& InObject);
		static void LoadEntities			(GameLayer* TheGameLayer, const rapidjson::Value& InObject);
		static void LoadComponents			(Entity& e, const rapidjson::Value& InObject);
	};
}