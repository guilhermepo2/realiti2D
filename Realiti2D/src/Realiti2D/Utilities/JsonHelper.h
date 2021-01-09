#pragma once

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include "Realiti2D/Math/Math.h"

namespace Realiti2D {
	class JsonHelper {
	public:
		static bool GetInt			(const rapidjson::Value& InObject, const char* InProperty, int& OutInt					);
		static bool GetFloat		(const rapidjson::Value& InObject, const char* InProperty, float& OutFloat				);
		static bool GetString		(const rapidjson::Value& InObject, const char* InProperty, std::string& OutString		);
		static bool GetBool			(const rapidjson::Value& InObject, const char* InProperty, bool& OutBool				);
		static bool GetVector2		(const rapidjson::Value& InObject, const char* InProperty, Vector2& OutVector			);
	};
}