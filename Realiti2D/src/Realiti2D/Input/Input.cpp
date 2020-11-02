#include "Input.h"
#include "Realiti2D/Log.h"
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
	// Mouse State
	// -------------------------------------------
	bool MouseState::GetButtonValue(R2D_Mousecode MouseKey) const { 
		return ( SDL_BUTTON(MouseKey) & m_MouseButtons == 1 );
	}

	EButtonState MouseState::GetButtonState(R2D_Mousecode MouseKey) const {
		int mask = SDL_BUTTON(MouseKey);

		if (mask & m_MouseButtonsLastFrame == 0) {
			if ( mask & m_MouseButtons == 0) { return ENone; }
			else { return EPressed; }
		}
		else {
			if ( mask & m_MouseButtons == 0 ) { return EReleased; }
			else { return EHeld; }
		}
	}

	bool MouseState::IsMouseKeyDown					(R2D_Mousecode MouseKey) const { return ( GetButtonState(MouseKey) == EPressed || GetButtonState( MouseKey ) == EHeld ); }
	bool MouseState::WasMouseKeyPressedThisFrame	(R2D_Mousecode MouseKey) const { return ( GetButtonState(MouseKey) == EPressed  ); }
	bool MouseState::WasKMouseKeyReleasedThisFrame	(R2D_Mousecode MouseKey) const { return ( GetButtonState(MouseKey) == EReleased ); }

	// -------------------------------------------
	// Input System
	// -------------------------------------------
	bool InputSystem::Initialize() {
		// Assign current state pointer
		m_State.Keyboard.m_CurrentState = SDL_GetKeyboardState(nullptr);
		memset(m_State.Keyboard.m_PreviousState, 0, SDL_NUM_SCANCODES);

		// Initializing Mouse
		m_State.Mouse.m_MouseButtons = 0;
		m_State.Mouse.m_MouseButtonsLastFrame = 0;

		// TODO: Controller

		CORE_INFO("[input] input system initialized");
		return true;
	}

	void InputSystem::Shutdown() { }

	void InputSystem::PrepareForUpdate() {
		memcpy(m_State.Keyboard.m_PreviousState, m_State.Keyboard.m_CurrentState, SDL_NUM_SCANCODES);

		// Mouse
		m_State.Mouse.m_MouseButtonsLastFrame = m_State.Mouse.m_MouseButtons;
		m_State.Mouse.m_IsRelative = false;
		m_State.Mouse.m_ScrollWheel = Vector2(0, 0); // TODO: shouldn't have to construct a vector2 here...
		
		// TODO: Controller
	}

	void InputSystem::Update() {
		// Mouse
		int x = 0, y = 0;
		if (m_State.Mouse.m_IsRelative) { m_State.Mouse.m_MouseButtons = SDL_GetRelativeMouseState(&x, &y); }
		else { m_State.Mouse.m_MouseButtons = SDL_GetMouseState(&x, &y); }

		m_State.Mouse.m_MousePosition.x = static_cast<float>(x);
		m_State.Mouse.m_MousePosition.y = static_cast<float>(y);

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