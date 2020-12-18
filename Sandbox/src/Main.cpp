#include <Realiti2D.h>

class PlaneInput : public Realiti2D::Component {

public:
	PlaneInput() {}
	~PlaneInput() {}

	virtual void Initialize() {
		DEBUG_INFO("Initialize Tappy Plane");
	}

	virtual void BeginPlay()  {
		DEBUG_INFO("Begin Play Tappy Plane");
	}

	void ProcessInput(const Realiti2D::InputState& CurrentInputState) {
		if (CurrentInputState.Mouse.WasMouseKeyPressedThisFrame(Realiti2D::R2D_Mousecode::MOUSECODE_LEFT)) {
			m_VerticalVelocity = m_UpForce;
		}
	}

	void Update(float DeltaTime) {
		m_VerticalVelocity -= m_Gravity * DeltaTime;
		Owner->GetComponentOfType<Realiti2D::Transform>()->Position += Realiti2D::Vector2(0.0f, m_VerticalVelocity * DeltaTime);
		
		if ( m_VerticalVelocity <= 0.0f ) {
			float CurrentRotation = Owner->GetComponentOfType<Realiti2D::Transform>()->Rotation;
			CurrentRotation = Realiti2D::Math::Min(CurrentRotation + 1.0f, 45.0f);
			Owner->GetComponentOfType<Realiti2D::Transform>()->Rotation = CurrentRotation;
		}
		else {
			Owner->GetComponentOfType<Realiti2D::Transform>()->Rotation = -30.0f;
		}
	}

	void Destroy() {
		DEBUG_INFO("Destroy Tappy Plane");
	}

private:
	float m_UpForce = 325.0f;
	float m_VerticalVelocity = 0.0f;
	float m_Gravity = 500.0f;
};

class Sandbox : public Realiti2D::Application {
public:
	Sandbox(const float& Width, const float& Height, const std::string& Title) : Application(Width, Height, Title) {}
	~Sandbox() {}

	void Start() override {

		DEBUG_INFO("starting app");

		Realiti2D::Entity& PlaneEntity = AddEntity("Plane");
		PlaneEntity.AddComponent<Realiti2D::Transform>(Realiti2D::Vector2(0.0f, 0.0f), 0.0f, Realiti2D::Vector2(1.0f, 1.0f));
		PlaneEntity.AddComponent<Realiti2D::Sprite>("assets/tappyplane/PNG/Planes/planeBlue1.png");
		PlaneEntity.AddComponent<PlaneInput>();
	}

private:

};

Realiti2D::Application* Realiti2D::CreateApplication() {
	return new Sandbox(1280.0f, 720.0f, "Realiti2D");
}