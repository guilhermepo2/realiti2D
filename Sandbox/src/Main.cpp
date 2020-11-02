#include <Realiti2D.h>

class Sandbox : public Realiti2D::Application {
public:
	Sandbox(const float& Width, const float& Height, const std::string& Title) : Application(Width, Height, Title) {}
	~Sandbox() {}

	void Start() override {
		DEBUG_INFO("starting app");
	}

private:

};

Realiti2D::Application* Realiti2D::CreateApplication() {
	return new Sandbox(1024.0f, 768.0f, "Realiti2D");
}