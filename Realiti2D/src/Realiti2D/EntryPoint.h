#pragma once
#define SDL_MAIN_HANDLED
#include "Log.h"
#include "Renderer/Renderer.h"

// this is temporary
extern void RunApplication();

int main(int argc, char** argv) {
	Realiti2D::Log::Initialize();
	CORE_INFO("[ENTRY POINT] Initialized log");
	Renderer* renderer = new Renderer();
	
	if (renderer->Initialize(1024.0f, 768.0f)) {
		CORE_INFO("[ENTRY POINT] Initialized renderer");
	}
	else {
		CORE_ERROR("[ENTRY POINT] Unable to initialize renderer");
		return 1;
	}

	RunApplication();

	renderer->Shutdown();
	return 0;
}