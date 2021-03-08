#include <Realiti2D.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define VISIONS_EDITOR

class Visions : public Realiti2D::Application {
public:
	Visions(const float& Width, const float& Height, const std::string& Title) : Application(Width, Height, Title) {}
	~Visions() {}

	void Start() override {
		DEBUG_INFO("Starting Visions Editor]");
	}

private:

};

Realiti2D::Application* Realiti2D::CreateApplication() {
	return new Visions(SCREEN_WIDTH, SCREEN_HEIGHT, "Visions Editor");
}