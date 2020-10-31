#pragma once
#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>

#include "KeyboardInput.h"
#include "MouseInput.h"

union SDL_Event;

namespace Realiti2D {
	enum EButtonState {
		ENone,
		EPressed,
		EReleased,
		EHeld
	};

	// -------------------------------------------
	// Keyboard State
	// -------------------------------------------
	class KeyboardState {
	public:
		friend class InputSystem;
		bool GetKeyValue(R2D_Keycode KeyCode) const;
		EButtonState GetKeyState(R2D_Keycode KeyCode) const;

		bool IsKeyDown					(R2D_Keycode KeyCode) const;
		bool WasKeyPressedThisFrame		(R2D_Keycode KeyCode) const;
		bool WasKeyReleasedThisFrame	(R2D_Keycode KeyCode) const;

	private:
		const Uint8* m_CurrentState;
		Uint8 m_PreviousState[NUM_SCANCODES];
	};

	// -------------------------------------------
	// Mouse State
	// -------------------------------------------
	class MouseState {
	public:
		friend class InputSystem;
		
	private:
		bool m_IsRelative;
	};

	// -------------------------------------------
	// Game Controller State
	// -------------------------------------------
	class ControllerState {
	public:
		friend class InputSystem;
	private:
	};

	// -------------------------------------------
	// Input State
	// -------------------------------------------
	struct InputState {
		KeyboardState	Keyboard;
		MouseState		Mouse;
		// ControllerState Controller;
	};

	// -------------------------------------------
	// Input System
	// -------------------------------------------
	class InputSystem {
	public:
		bool Initialize();
		void Shutdown();
		void PrepareForUpdate();
		void Update();

		void SetRelativeMouseMode(bool Value);
		void ProcessEvent(SDL_Event& Event);
		const InputState& GetState() const { return m_State; }

	private:
		// float Filter1D(int Input);
		// Vector2 Filter2D(int InputX, int InputY);
		InputState m_State;
		SDL_GameController* m_Controller;

	};
}