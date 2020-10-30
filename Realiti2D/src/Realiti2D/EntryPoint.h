#pragma once
#include "Log.h"

// this is temporary
extern void RunApplication();

int main(int argc, char** argv) {
	Realiti2D::Log::Initialize();
	
	CORE_INFO("[ENTRY POINT] Initialized Log...");
	RunApplication();

	return 0;
}