#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Realiti2D {
	class Log {
	public:
		static void Initialize();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return s_AppLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_AppLogger;
	};
}

#define CORE_INFO(...)			::Realiti2D::Log::GetCoreLogger()->info		(  __VA_ARGS__ );
#define CORE_WARNING(...)		::Realiti2D::Log::GetCoreLogger()->warn		(  __VA_ARGS__ );
#define CORE_ERROR(...)			::Realiti2D::Log::GetCoreLogger()->error	(  __VA_ARGS__ );

#define DEBUG_INFO(...)			::Realiti2D::Log::GetAppLogger()->info		(  __VA_ARGS__ );
#define DEBUG_WARNING(...)		::Realiti2D::Log::GetAppLogger()->warn		(  __VA_ARGS__ );
#define DEBUG_ERROR(...)		::Realiti2D::Log::GetAppLogger()->error		(  __VA_ARGS__ );

#define ASSERT(x, ...) { if(!(x)) { CORE_ERROR( __VA_ARGS__ ); __debugbreak(); } }