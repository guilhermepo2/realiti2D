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

		// Adding a background
		Realiti2D::Entity& Background = AddEntity("Background");
		Background.AddComponent<Realiti2D::Transform>(Realiti2D::Vector2(0.0f, 0.0f), 0.0f, Realiti2D::Vector2(1.75f, 1.5f));
		Background.AddComponent<Realiti2D::Sprite>("assets/tappyplane/PNG/background.png");

		// TODO: Add obstacle(s)... <- this should be another component....

		// Plane
		Realiti2D::Entity& PlaneEntity = AddEntity("Plane");
		float StartingXPosition = (-(SCREEN_WIDTH / 2)) + 175;
		PlaneEntity.AddComponent<Realiti2D::Transform>(Realiti2D::Vector2(StartingXPosition, 0.0f), 0.0f, Realiti2D::Vector2(1.0f, 1.0f));
		PlaneEntity.AddComponent<Realiti2D::Sprite>("assets/tappyplane/PNG/Planes/planeBlue1.png");

		Realiti2D::AnimatedSprite& PlaneAnimation = PlaneEntity.AddComponent<Realiti2D::AnimatedSprite>();
		PlaneAnimation.SetAnimationFPS(24.0f);
		PlaneAnimation.AddAnimationTexture("assets/tappyplane/PNG/Planes/planeBlue1.png");
		PlaneAnimation.AddAnimationTexture("assets/tappyplane/PNG/Planes/planeBlue2.png");
		PlaneAnimation.AddAnimationTexture("assets/tappyplane/PNG/Planes/planeBlue3.png");
		
		PlaneEntity.AddComponent<PlaneInput>();
		PlaneEntity.AddComponent<Realiti2D::BoxCollider>(Realiti2D::Vector2(-32.0f, -32.0f), Realiti2D::Vector2(32.0f, 32.0f));

		// Colliosion Box (testing collision
		Realiti2D::Entity& Box = AddEntity("Box");
		Box.AddComponent<Realiti2D::Transform>(Realiti2D::Vector2(StartingXPosition, 200.0f), 0.0f, Realiti2D::Vector2(1.0f, 1.0f));
		Box.AddComponent<Realiti2D::Sprite>("assets/tappyplane/PNG/UI/MedalGold.png");
		Box.AddComponent<Realiti2D::BoxCollider>(Realiti2D::Vector2(-32.0f, -32.0f), Realiti2D::Vector2(32.0f, 32.0f));

		// adding foreground
		Realiti2D::Entity& Foreground = AddEntity("Foreground");
		float ForegroundYPosition = (-SCREEN_HEIGHT / 2.0f) + 15.0f;
		Foreground.AddComponent<Realiti2D::Transform>(Realiti2D::Vector2(0.0f, ForegroundYPosition), 0.0f, Realiti2D::Vector2(1.75f, 1.0f));
		Foreground.AddComponent<Realiti2D::Sprite>("assets/tappyplane/PNG/groundGrass.png");
	}

private:

};

Realiti2D::Application* Realiti2D::CreateApplication() {
	// MAGICAL NUMBERS
	return new Sandbox(1280.0f, 720.0f, "Tappy Plane - Realiti2D");
}