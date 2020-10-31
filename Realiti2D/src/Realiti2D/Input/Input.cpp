#include "Input.h"
#include <SDL.h>
#include <cstring>

namespace Realiti2D {
	// -------------------------------------------
	// Keyboard State
	// -------------------------------------------
	bool KeyboardState::GetKeyValue(R2D_Keycode KeyCode) const {
		return m_CurrentState[KeyCode] == 1;
	}

	EButtonState KeyboardState::GetKeyState(R2D_Keycode KeyCode) const {
		if (m_PreviousState[KeyCode] == 0) {
			if (m_CurrentState[KeyCode] == 0) { return ENone; }
			else { return EPressed; }
		}
		else {
			if (m_CurrentState[KeyCode] == 0) { return EReleased; }
			else { return EHeld; }
		}
	}

	bool KeyboardState::IsKeyDown				(R2D_Keycode KeyCode) const { return ( GetKeyState( KeyCode ) == EPressed || GetKeyState( KeyCode ) == EHeld ); }
	bool KeyboardState::WasKeyPressedThisFrame	(R2D_Keycode KeyCode) const { return ( GetKeyState( KeyCode ) == EPressed); }
	bool KeyboardState::WasKeyReleasedThisFrame	(R2D_Keycode KeyCode) const { return ( GetKeyState( KeyCode ) == EReleased); }

	// -------------------------------------------
	// Input System
	// -------------------------------------------
	bool InputSystem::Initialize() {
		// Assign current state pointer
		m_State.Keyboard.m_CurrentState = SDL_GetKeyboardState(nullptr);
		memset(m_State.Keyboard.m_PreviousState, 0, SDL_NUM_SCANCODES);

		// TODO: Mouse
		// TODO: Controller

		return true;
	}

	void InputSystem::Shutdown() { }

	void InputSystem::PrepareForUpdate() {
		memcpy(m_State.Keyboard.m_PreviousState, m_State.Keyboard.m_CurrentState, SDL_NUM_SCANCODES);
		// TODO: Mouse
		// TODO: Controller
	}

	void InputSystem::Update() {
		// TODO: Mouse
		// TODO: Controller
	}

	void InputSystem::SetRelativeMouseMode(bool Value) {
		SDL_bool ValueToSet = Value ? SDL_TRUE : SDL_FALSE;
		SDL_SetRelativeMouseMode(ValueToSet);
		m_State.Mouse.m_IsRelative = Value;
	}

	void InputSystem::ProcessEvent(SDL_Event& Event) {
		switch (Event.type) {
		default:
			break;
		}
	}

}