#pragma once
#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>
#include <vector>

#include "KeyboardInput.h"
#include "MouseInput.h"
#include "Realiti2D/Math/Math.h"

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
		const Vector2& GetPosition() const { return m_MousePosition; }

		bool GetButtonValue(R2D_Mousecode MouseKey) const;
		EButtonState GetButtonState(R2D_Mousecode MouseKey) const;

		bool IsMouseKeyDown					(R2D_Mousecode MouseKey) const;
		bool WasMouseKeyPressedThisFrame	(R2D_Mousecode MouseKey) const;
		bool WasKMouseKeyReleasedThisFrame	(R2D_Mousecode MouseKey) const;


	private:
		Vector2 m_MousePosition;
		Vector2 m_ScrollWheel;
		Uint32 m_MouseButtons;
		Uint32 m_MouseButtonsLastFrame;
		bool m_IsRelative;
	};

	// -------------------------------------------
	// Game Controller State
	// -------------------------------------------
	class ControllerState {
	public:
		friend class InputSystem;
		bool GetButtonValue(SDL_GameControllerButton Button) const;
		EButtonState GetButtonState(SDL_GameControllerButton Button) const;

		bool GetIscConnected()		const { return m_IsConnected;	}
		float GetLeftTrigger()		const { return m_LeftTrigger;	}
		float GetRightTrigger()		const { return m_RightTrigger;	}
		Vector2 GetLeftStick()		const { return m_LeftStick;		}
		Vector2 GetRightStick()		const { return m_RightStick;	}

	private:
		Uint8 m_CurrentButtons[SDL_CONTROLLER_BUTTON_MAX];
		Uint8 m_PreviousButtons[SDL_CONTROLLER_BUTTON_MAX];
		bool m_IsConnected;

		float m_LeftTrigger;
		float m_RightTrigger;

		Vector2 m_LeftStick;
		Vector2 m_RightStick;
	};

	// -------------------------------------------
	// Input State
	// -------------------------------------------
	struct InputState {
		KeyboardState	Keyboard;
		MouseState		Mouse;
		ControllerState Controller;
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
		float Filter1D(int Input);
		Vector2 Filter2D(int InputX, int InputY);
		InputState m_State;
		SDL_GameController* m_Controller;
	};
}