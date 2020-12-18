#include <Realiti2D.h>

class Sandbox : public Realiti2D::Application {
public:
	Sandbox(const float& Width, const float& Height, const std::string& Title) : Application(Width, Height, Title) {}
	~Sandbox() {}

	void Start() override {

		DEBUG_INFO("starting app");
		Realiti2D::Entity& MyEntity = AddEntity("MyEntity");
		MyEntity.AddComponent<Realiti2D::Transform>(Realiti2D::Vector2(0.0f, 0.0f), 0.0f, Realiti2D::Vector2(1.0f, 1.0f));
		MyEntity.AddComponent<Realiti2D::Sprite>("assets/boat_large_SE.png");

		Realiti2D::Entity& MyEntity2 = AddEntity("MyEntity2");
		MyEntity2.AddComponent<Realiti2D::Transform>(Realiti2D::Vector2(350, 100.0f), 0.0f, Realiti2D::Vector2(-1.0f, 1.0f));
		MyEntity2.AddComponent<Realiti2D::Sprite>("assets/cannonLarge_SE.png");

		Realiti2D::Entity& MyEntity3 = AddEntity("MyEntity3");
		MyEntity3.AddComponent<Realiti2D::Transform>(Realiti2D::Vector2(-125.0f, 100.0f), 0.0f, Realiti2D::Vector2(1.0f, 1.0f));
		MyEntity3.AddComponent<Realiti2D::Sprite>("assets/formation_rock_NE.png");

		Realiti2D::Entity& MyEntity4 = AddEntity("MyEntity4");
		MyEntity4.AddComponent<Realiti2D::Transform>(Realiti2D::Vector2(-150.0f, -150.0f), 0.0f, Realiti2D::Vector2(1.0f, 1.0f));
		MyEntity4.AddComponent<Realiti2D::Sprite>("assets/formation_rock_NE.png");
	}

private:

};

Realiti2D::Application* Realiti2D::CreateApplication() {
	return new Sandbox(1280.0f, 720.0f, "Realiti2D");
}