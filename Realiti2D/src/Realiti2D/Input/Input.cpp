#include "Input.h"
#include "Realiti2D/Log.h"
#include "Realiti2D/Math/Math.h"
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
	// Controller State
	// -------------------------------------------
	bool ControllerState::GetButtonValue(SDL_GameControllerButton button) const {
		return m_CurrentButtons[button] == 1;
	}

	EButtonState ControllerState::GetButtonState(SDL_GameControllerButton button) const {
		if (m_PreviousButtons[button] == 0) {
			if (m_CurrentButtons[button] == 0) { return ENone; }
			else { return EPressed; }
		}
		else {
			if (m_CurrentButtons[button] == 0) { return EReleased; }
			else { return EHeld; }
		}
	}

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

		// Controller
		m_Controller = SDL_GameControllerOpen(0);
		m_State.Controller.m_IsConnected = (m_Controller != nullptr);
		memset(m_State.Controller.m_CurrentButtons, 0, SDL_CONTROLLER_BUTTON_MAX);
		memset(m_State.Controller.m_CurrentButtons, 0, SDL_CONTROLLER_BUTTON_MAX);

		CORE_INFO("[input] input system initialized");
		return true;
	}

	void InputSystem::Shutdown() { }

	void InputSystem::PrepareForUpdate() {
		memcpy(m_State.Keyboard.m_PreviousState, m_State.Keyboard.m_CurrentState, SDL_NUM_SCANCODES);

		// Mouse
		m_State.Mouse.m_MouseButtonsLastFrame = m_State.Mouse.m_MouseButtons;
		m_State.Mouse.m_IsRelative = false;
		m_State.Mouse.m_ScrollWheel = Vector2::Zero;
		
		// Controller
		memcpy(m_State.Controller.m_PreviousButtons, m_State.Controller.m_CurrentButtons, SDL_CONTROLLER_BUTTON_MAX);
	}

	void InputSystem::Update() {
		// Mouse
		int x = 0, y = 0;
		if (m_State.Mouse.m_IsRelative) { m_State.Mouse.m_MouseButtons = SDL_GetRelativeMouseState(&x, &y); }
		else { m_State.Mouse.m_MouseButtons = SDL_GetMouseState(&x, &y); }

		m_State.Mouse.m_MousePosition.x = static_cast<float>(x);
		m_State.Mouse.m_MousePosition.y = static_cast<float>(y);

		// Controller
		for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++) {
			m_State.Controller.m_CurrentButtons[i] = SDL_GameControllerGetButton(m_Controller, SDL_GameControllerButton(i));
		}

		m_State.Controller.m_LeftTrigger = Filter1D(SDL_GameControllerGetAxis(m_Controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT));
		m_State.Controller.m_LeftTrigger = Filter1D(SDL_GameControllerGetAxis(m_Controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT));

		x = SDL_GameControllerGetAxis(m_Controller, SDL_CONTROLLER_AXIS_LEFTX);
		y = -SDL_GameControllerGetAxis(m_Controller, SDL_CONTROLLER_AXIS_LEFTY);
		m_State.Controller.m_LeftStick = Filter2D(x, y);

		x = SDL_GameControllerGetAxis(m_Controller, SDL_CONTROLLER_AXIS_RIGHTX);
		y = -SDL_GameControllerGetAxis(m_Controller, SDL_CONTROLLER_AXIS_RIGHTY);
		m_State.Controller.m_RightStick = Filter2D(x, y);
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

	float InputSystem::Filter1D(int Input) {
		// A value < dead zone is interpreted as 0%
		const int deadZone = 250;
		// A value > max value is interpreted as 100%
		const int maxValue = 30000;

		float retVal = 0.0f;

		// Take absolute value of input
		int absValue = Input > 0 ? Input : -Input;
		// Ignore input within dead zone
		if (absValue > deadZone) {
			// Compute fractional value between dead zone and max value
			retVal = static_cast<float>(absValue - deadZone) / (maxValue - deadZone);
			// Make sure sign matches original value
			retVal = Input > 0 ? retVal : (-1.0f * retVal);

			// Clamp between -1.0f and 1.0f
			Math::Clamp(retVal, -1.0f, 1.0f);
		}

		return retVal;
	}

	Vector2 InputSystem::Filter2D(int InputX, int InputY) {
		const float deadZone = 8000.0f;
		const float maxValue = 30000.0f;

		// Make into a 2D Vector
		Vector2 dir;
		dir.x = static_cast<float>(InputX);
		dir.y = static_cast<float>(InputY);

		float length = dir.Length();

		// If length < deadZone, should be no input
		if (length < deadZone) {
			dir = Vector2::Zero;
		}
		else {
			// Calculate the fractional value between dead zone and max value circles
			float f = (length - deadZone) / (maxValue - deadZone);

			// Clamp f between 0.0f and 1.0f
			Math::Clamp(f, -1.0f, 1.0f);

			// Normalize the vector, and then scale it to the fractional value
			dir *= f / length;
		}

		return dir;
	}

}