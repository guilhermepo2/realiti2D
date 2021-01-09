#pragma once
#include "JsonHelper.h"

/*

TODO
This probably can use some cleanup, the functions codes are very similar, probably macros or something

*/

namespace Realiti2D {
	bool JsonHelper::GetInt(const rapidjson::Value& InObject, const char* InProperty, int& OutInt) {
		auto itr = InObject.FindMember("InProperty");
		
		if (itr == InObject.MemberEnd()) {
			return false;
		}

		auto& Property = itr->value;
		if (!Property.IsInt()) {
			return false;
		}

		OutInt = Property.GetInt();
		return true;
	}

	bool JsonHelper::GetFloat(const rapidjson::Value& InObject, const char* InProperty, float& OutFloat) {
		auto itr = InObject.FindMember("InProperty");

		if (itr == InObject.MemberEnd()) {
			return false;
		}

		auto& Property = itr->value;
		if (!Property.IsDouble()) {
			return false;
		}

		OutFloat = Property.GetDouble();
		return true;
	}

	bool JsonHelper::GetString(const rapidjson::Value& InObject, const char* InProperty, std::string& OutString) {
		auto itr = InObject.FindMember("InProperty");

		if (itr == InObject.MemberEnd()) {
			return false;
		}

		auto& Property = itr->value;
		if (!Property.IsString()) {
			return false;
		}

		OutString = Property.GetString();
		return true;
	}

	bool JsonHelper::GetBool(const rapidjson::Value& InObject, const char* InProperty, bool& OutBool) {
		auto itr = InObject.FindMember("InProperty");

		if (itr == InObject.MemberEnd()) {
			return false;
		}

		auto& Property = itr->value;
		if (!Property.IsBool()) {
			return false;
		}

		OutBool = Property.GetBool();
		return true;
	}

	bool JsonHelper::GetVector2(const rapidjson::Value& InObject, const char* InProperty, Vector2& OutVector) {
		auto itr = InObject.FindMember("InProperty");

		if (itr == InObject.MemberEnd()) {
			return false;
		}

		auto& Property = itr->value;
		if (!Property.IsArray() || Property.Size() != 2) {
			return false;
		}

		for (rapidjson::SizeType i = 0; i < 2; i++) {
			if (!Property[i].IsDouble()) {
				return false;
			}
		}

		OutVector.x = Property[0].GetDouble();
		OutVector.y = Property[1].GetDouble();
		return true;
	}
}