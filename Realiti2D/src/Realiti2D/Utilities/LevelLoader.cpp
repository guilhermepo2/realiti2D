#include "LevelLoader.h"
#include "JsonHelper.h"
#include "Realiti2D/Log.h"
#include "Realiti2D/Application.h"
#include "Realiti2D/Entity/Entity.h"
#include "Realiti2D/Component/TransformComponent.h"
#include "Realiti2D/Component/Sprite.h"

#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <fstream>
#include <vector>

#define DEBUG_LEVEL_LOADER 0

namespace Realiti2D {
	bool LevelLoader::LoadLevel(Application* app, std::string FileName) {
		// Loading JSON
		rapidjson::Document doc;
		if (!LoadJSON(FileName, doc)) {
			CORE_ERROR("[LEVEL LOADER] Failed to load level: {0}", FileName.c_str());
			return false;
		}

		CORE_INFO("[LEVEL LOADER] Parsing Level: {0}", FileName.c_str());

#if DEBUG_LEVEL_LOADER
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		CORE_INFO("[DEBUG] Loaded Json: {0}", buffer.GetString());
#endif

		// Getting the version
		int Version = 0;
		if (!JsonHelper::GetInt(doc, "version", Version)) {
			CORE_ERROR("[LEVEL LOADER] Incorrect version for file {0}", FileName.c_str());
			return false;
		}
		CORE_INFO("[LEVEL LOADER] Version: {0}", Version);

		// Getting Global Properties
		const rapidjson::Value& GlobalProperties = doc["globalProperties"];
		if (GlobalProperties.IsObject()) {
			LoadGlobalProperties(GlobalProperties);
		}

		// Getting Actors and their Components
		const rapidjson::Value& Entities = doc["entities"];
		if (Entities.IsArray()) {
			LoadEntities(app, Entities);
		}

		return true;
	}

	bool LevelLoader::LoadJSON(const std::string& FileName, rapidjson::Document& OutDocument) {
		std::ifstream File(FileName, std::ios::in | std::ios::binary | std::ios::ate);
		if (!File.is_open()) {
			CORE_ERROR("[LEVEL LOADER] File {0} not found", FileName.c_str());
			return false;
		}

		// Get the current position in stream buffer, which is the size of the file
		std::ifstream::pos_type FileSize = File.tellg();
		File.seekg(0, std::ios::beg);

		// Create a vector of size + 1 (for null terminator)
		std::vector<char> Bytes(static_cast<size_t>(FileSize) + 1);
		// Read int bytes into vector
		File.read(Bytes.data(), static_cast<size_t>(FileSize));

		// Loading raw data into RapidJSON document
		OutDocument.Parse(Bytes.data());
		if (!OutDocument.IsObject()) {
			CORE_ERROR("[LEVEL LOADER] File {0} is not a valid JSON!", FileName.c_str());
			return false;
		}

		return true;
	}

	void LevelLoader::LoadGlobalProperties(const rapidjson::Value& InObject) {
		// TODO... I have no global properties to load so far!
		return;
	}

	void LevelLoader::LoadEntities(Application* app, const rapidjson::Value& InObject) {
		// We can assume that the InObject is an array.
		for (rapidjson::SizeType i = 0; i < InObject.Size(); i++) {
			const rapidjson::Value& Entity = InObject[i];
			
			if (Entity.IsObject()) {
				std::string EntityName;
				if (JsonHelper::GetString(Entity, "name", EntityName)) {
					CORE_INFO("Entity on Level File: {0}", EntityName.c_str());
					Realiti2D::Entity& e = app->AddEntity(EntityName);

					// Checking for components and calling the function to load the components
					if (Entity.HasMember("components")) {
						const rapidjson::Value& Components = Entity["components"];
						if (Components.IsArray()) {
							LoadComponents(e, Components);
						}
					}

				}
			}

		}
	}

	void LevelLoader::LoadComponents(Entity& e, const rapidjson::Value& InObject) {
		// We can assume that InObject is an array
		for (rapidjson::SizeType i = 0; i < InObject.Size(); i++) {
			const rapidjson::Value& Component = InObject[i];

			if (Component.IsObject()) {
				std::string ComponentType;
				if (JsonHelper::GetString(Component, "type", ComponentType)) {
					CORE_INFO("Entity has component of type {0}", ComponentType.c_str());
					e.AddComponent<Realiti2D::Transform>(Realiti2D::Vector2(50 * (i+1), 0.0f), 0.0f, Realiti2D::Vector2(1.0f, 1.0f));
					e.AddComponent<Realiti2D::Sprite>("assets/tappyplane/PNG/Planes/planeBlue1.png");
				}
			}
		}
	}
}