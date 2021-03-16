#pragma once

//
// This base control will provide the interface that any derived controls may implement to offer their own behavior.
// Example of controls would be: Labels, Buttons, Lists(?), ...
// Most controls will share the same core set of features, placements, transparency, colors, states...
//


namespace Realiti2D {
	class Control {
	public:
		void SetPosition();
		void Update(float DeltaTime);
		void Draw();
		bool HandleInput();

		// event_handler<const control&> m_OnFocusReceived;
		// event_handler<const control&> m_OnFocusLost;
		// event_handler<const control&> m_OnMouseEnter;
		// event_handler<const control&> m_OnMouseLeave;

	protected:
		// TODO: rectangle to define their bounds on screen

		float m_Alpha;
		// TODO: Colors (background and foreground)

		bool m_Visible;
		bool m_Enabled;
		bool m_Focused;
		bool m_MouseOver;

		// Render viewport?
	};
}