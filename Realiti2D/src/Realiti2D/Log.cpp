#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Realiti2D {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_AppLogger;

	void Log::Initialize() {
		spdlog::set_pattern("%^[%n] %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("REALITI2D");
		s_CoreLogger->set_level(spdlog::level::trace);
		s_AppLogger = spdlog::stdout_color_mt("APP");
		s_AppLogger->set_level(spdlog::level::trace);
	}
}