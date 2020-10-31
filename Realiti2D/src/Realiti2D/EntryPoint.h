#pragma once
#define SDL_MAIN_HANDLED
#include "Log.h"
#include "Application.h"

extern Realiti2D::Application* Realiti2D::CreateApplication();

// #include "Renderer/Renderer.h"

int main(int argc, char** argv) {
	Realiti2D::Log::Initialize();
	CORE_INFO("[entry point] log initialized");
	Realiti2D::Application* app = Realiti2D::CreateApplication();

	if (app->s_bIsInitialized) {
		app->Run();
	} else {
		CORE_ERROR("[entry point] error initializing application");
	}

	delete app;
	return 0;
}