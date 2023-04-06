#include "hnpch.h"
#include "Hina.h"

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

		//m_model = Hina::Model("Gun", Hina::MaterialType::BasePBR, "C:/Users/22470/Desktop/Models/desert_eagle_2/scene.gltf");
		//m_model = Hina::Model("Bottle", Hina::MaterialType::BasePBR, "C:/Users/22470/Desktop/Models/gas_bottles_set/scene.gltf");
		//m_model = Hina::Model("Chest", Hina::MaterialType::BasePBR, "C:/Users/22470/Desktop/Models/old_wooden_chest/scene.gltf");
		//m_model = Hina::Model("Tortoise", Hina::MaterialType::BasePBR, "C:/Users/22470/Desktop/Models/tortoise/scene.gltf");

		// Some little trick to get a comfortable camera controling.
		if(m_model.IsLoaded()) {
			m_cameraController.FrameAll(m_model.GetAABB());
			m_cameraController.SetSpeed(m_model.GetAABB().GetSize() * 1.8f);
		}
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
