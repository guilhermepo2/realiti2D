#include <Realiti2D.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class PlaneInput : public Realiti2D::Component {

public:
	PlaneInput() {}
	~PlaneInput() {}

	virtual void Initialize() {
		DEBUG_INFO("Initialize Tappy Plane");
	}

	virtual void BeginPlay()  {
		DEBUG_INFO("Begin Play Tappy Plane");
		m_Collider = Owner->GetComponentOfType<Realiti2D::BoxCollider>();

		if (m_Collider == nullptr) {
			DEBUG_ERROR("Tappy Plane does not have a box collider!");
		}
		else {
			m_Collider->CollisionCallback = BIND_COLLISION(&PlaneInput::ExecuteThis);
		}

		Owner->GetComponentOfType<Realiti2D::AnimatedSprite>()->Play("plane");

	}

	void ExecuteThis(Realiti2D::BoxCollider* Other) {
		DEBUG_INFO("Tappy plane collided with {0}", Other->Owner->Name);
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
	Realiti2D::BoxCollider* m_Collider;
};

class Sandbox : public Realiti2D::Application {
public:
	Sandbox(const float& Width, const float& Height, const std::string& Title) : Application(Width, Height, Title) {}
	~Sandbox() {}

	void Start() override {
		DEBUG_INFO("starting app");

		Realiti2D::LevelLoader::LoadLevel(this, "assets/SampleLevel.r2d");

		Realiti2D::Entity* PlaneEntity = GetEntityByName("Plane");
		PlaneEntity->AddComponent<PlaneInput>();
	}

private:

};

Realiti2D::Application* Realiti2D::CreateApplication() {
	// MAGICAL NUMBERS
	return new Sandbox(1280.0f, 720.0f, "Tappy Plane - Realiti2D");
}