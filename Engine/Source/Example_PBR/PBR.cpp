#include "hnpch.h"
#include "Hina.h"

#include "RenderCore/Texture2D.h"

static constexpr float vertices[] = {
//   pos,              normal,          uv
	-1.0,  1.0, -1.0,  0.0,  1.0,  0.0, 0.0, 1.0,
	 1.0,  1.0,  1.0,  0.0,  1.0,  0.0, 1.0, 1.0,
	 1.0,  1.0, -1.0,  0.0,  1.0,  0.0, 1.0, 1.0,

	 1.0,  1.0,  1.0,  0.0,  0.0,  1.0, 1.0, 1.0,
	-1.0, -1.0,  1.0,  0.0,  0.0,  1.0, 0.0, 0.0,
	 1.0, -1.0,  1.0,  0.0,  0.0,  1.0, 1.0, 0.0,

	-1.0,  1.0,  1.0, -1.0,  0.0,  0.0, 0.0, 1.0,
	-1.0, -1.0, -1.0, -1.0,  0.0,  0.0, 0.0, 0.0,
	-1.0, -1.0,  1.0, -1.0,  0.0,  0.0, 0.0, 0.0,

	 1.0, -1.0, -1.0,  0.0, -1.0,  0.0, 1.0, 0.0,
	-1.0, -1.0,  1.0,  0.0, -1.0,  0.0, 0.0, 0.0,
	-1.0, -1.0, -1.0,  0.0, -1.0,  0.0, 0.0, 0.0,

	 1.0,  1.0, -1.0,  1.0,  0.0,  0.0, 1.0, 1.0,
	 1.0, -1.0,  1.0,  1.0,  0.0,  0.0, 1.0, 0.0,
	 1.0, -1.0, -1.0,  1.0,  0.0,  0.0, 1.0, 0.0,

	-1.0,  1.0, -1.0,  0.0,  0.0, -1.0, 0.0, 1.0,
	 1.0, -1.0, -1.0,  0.0,  0.0, -1.0, 1.0, 0.0,
	-1.0, -1.0, -1.0,  0.0,  0.0, -1.0, 0.0, 0.0,

	-1.0,  1.0, -1.0,  0.0,  1.0,  0.0, 0.0, 1.0,
	-1.0,  1.0,  1.0,  0.0,  1.0,  0.0, 0.0, 1.0,
	 1.0,  1.0,  1.0,  0.0,  1.0,  0.0, 1.0, 1.0,

	 1.0,  1.0,  1.0,  0.0,  0.0,  1.0, 1.0, 1.0,
	-1.0,  1.0,  1.0,  0.0,  0.0,  1.0, 0.0, 1.0,
	-1.0, -1.0,  1.0,  0.0,  0.0,  1.0, 0.0, 0.0,

	-1.0,  1.0,  1.0, -1.0,  0.0,  0.0, 0.0, 1.0,
	-1.0,  1.0, -1.0, -1.0,  0.0,  0.0, 0.0, 1.0,
	-1.0, -1.0, -1.0, -1.0,  0.0,  0.0, 0.0, 0.0,

	 1.0, -1.0, -1.0,  0.0, -1.0,  0.0, 1.0, 0.0,
	 1.0, -1.0,  1.0,  0.0, -1.0,  0.0, 1.0, 0.0,
	-1.0, -1.0,  1.0,  0.0, -1.0,  0.0, 0.0, 1.0,

	 1.0,  1.0, -1.0,  1.0,  0.0,  0.0, 1.0, 1.0,
	 1.0,  1.0,  1.0,  1.0,  0.0,  0.0, 1.0, 1.0,
	 1.0, -1.0,  1.0,  1.0,  0.0,  0.0, 1.0, 0.0,

	-1.0,  1.0, -1.0,  0.0,  0.0, -1.0, 0.0, 1.0,
	 1.0,  1.0, -1.0,  0.0,  0.0, -1.0, 1.0, 1.0,
	 1.0, -1.0, -1.0,  0.0,  0.0, -1.0, 1.0, 0.0,
};

static constexpr uint32_t indices[] = {
	 0,  1,  2,
	 3,  4,  5,
	 6,  7,  8,
	 9,  10, 11,
	 12, 13, 14,
	 15, 16, 17,
	 18, 19, 20,
	 21, 22, 23,
	 24, 25, 26,
	 27, 28, 29,
	 30, 31, 32,
	 33, 34, 35,
};

class PBRLayer final : public Hina::Layer
{
public:
	explicit PBRLayer(const std::string &str) : Layer(str) {}
	explicit PBRLayer(std::string &&str) : Layer(std::move(str)) {}
	
	PBRLayer() = delete;
	PBRLayer(const PBRLayer &) = default;
	PBRLayer &operator=(const PBRLayer &) = default;
	PBRLayer(PBRLayer &&) = default;
	PBRLayer &operator=(PBRLayer &&) = default;
	~PBRLayer() = default;

	virtual void OnAttach() override {
		HN_PROFILE_FUNCTION();

		Hina::RenderCore::SetCameraController(m_cameraController);

		m_pShader = Hina::Shader::Create(
			"testShader",
			Hina::Path::FromAsset("Shader/v_testShader.glsl"),
			Hina::Path::FromAsset("Shader/f_testShader.glsl"));

		m_model = Hina::Model(Hina::MaterialType::BasePBR, Hina::Path::FromAsset("Model/officebot/scene.gltf"));
		//m_model = Hina::Model(Hina::MaterialType::BasePBR, "C:/Users/22470/Desktop/game_ready_scifi_helmet_2/scene.gltf");

		m_cameraController.FrameAll(m_model.GetAABB());
	}

	virtual void OnDetach() override {

	}

	virtual void OnUpdate(const Hina::DeltaTime deltaTime) override {
		HN_PROFILE_FUNCTION();

		m_cameraController.OnUpdate(deltaTime);

		Hina::RenderCore::SetDefaultMatrices();
		Hina::RenderCore::SetClears(glm::vec4(0.7f, 0.8f, 0.8f, 1.0f), 1.0f);

		Hina::RenderCore::BeginScene();
		m_model.Draw(m_pShader);
		Hina::RenderCore::EndScene();
	}

	virtual void OnEvent(Hina::Event &event) override {
		HN_PROFILE_FUNCTION();

		m_cameraController.OnEvent(event);
	}

	virtual void OnImGuiRender() override {

	}

private:
	Hina::Model m_model;
	std::shared_ptr<Hina::Shader> m_pShader;
	Hina::FirstPersonCamera m_cameraController;
};

class PBR final : public Hina::Application
{
public:
    PBR() {
		HN_PROFILE_FUNCTION();

		Hina::Initializer init;
		init.m_api = Hina::GraphicsAPI::OpenGL;
		init.m_window.m_title = "Physically Based Rendering";
		init.m_window.m_width = 1600;
		init.m_window.m_height = 900;

		Application::Init(init);

		PushLayer(new PBRLayer("Example"));
    }
};

Hina::Application *Hina::CreateApplication() {
    return new PBR;
}
