#include "hnpch.h"
#include "Hina.h"

#include "Core/Math.h"

namespace Utils
{

// I define D_LIGHT_COUNT and declar u_lights[D_LIGHT_COUNT] in shader,
// then set ulights[XXX].XXX at CPU side.
// TODO : Need to improve light/uniform system in the future.

inline std::string GetUniformName(const uint32_t index, const char *member) {
	std::stringstream ss;
	ss << "u_lights[" << index << "]." << member;
	return ss.str();
}

} // namespace Utils

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
			"basePBR",
			Hina::Path::FromAsset("Shader/v_basePBR.glsl"),
			Hina::Path::FromAsset("Shader/f_basePBR.glsl"));

		m_model = Hina::Model("Gun", Hina::MaterialType::BasePBR, Hina::Path::FromAsset("Model/desert_eagle_2/scene.gltf"));
		//m_model = Hina::Model("Gun", Hina::MaterialType::BasePBR, Hina::Path::FromAsset("Model/antique_movie_camera/scene.gltf"));

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

		// Temporary code just for the graduation defense.
		{
			m_pShader.get()->Bind();

			// Directional light x1.
			m_pShader.get()->SetInt(Utils::GetUniformName(0, "type"), 1);
			m_pShader.get()->SetVec3(Utils::GetUniformName(0, "direction"), glm::vec3(0.0f, -1.0f, 0.0f));
			m_pShader.get()->SetVec3(Utils::GetUniformName(0, "color"), glm::vec3(1.0f, 1.0f, 1.0f));
			m_pShader.get()->SetFloat(Utils::GetUniformName(0, "intensity"), 4.0f);

			// Point light x3.
			const glm::vec3 center = m_model.GetAABB().GetCentre();
			const float radius = m_model.GetAABB().GetSize() * 3.0f;
			const float theta = Hina::Math::AngularToRadians(Hina::Application::Get().GetCrtTime());
			constexpr float speed = 50.0f;

			m_pShader.get()->SetInt(Utils::GetUniformName(1, "type"), 0);
			m_pShader.get()->SetVec3(Utils::GetUniformName(1, "position"), Hina::Math::GetSphereCoordinate(center, radius, speed * theta, speed * theta * 3.14));
			m_pShader.get()->SetVec3(Utils::GetUniformName(1, "color"), glm::vec3(0.8f, 0.2f, 0.2f));
			m_pShader.get()->SetFloat(Utils::GetUniformName(1, "intensity"), radius * 100.0f);
			m_pShader.get()->SetFloat(Utils::GetUniformName(1, "range"), 1024.0f);

			m_pShader.get()->SetInt(Utils::GetUniformName(2, "type"), 0);
			m_pShader.get()->SetVec3(Utils::GetUniformName(2, "position"), Hina::Math::GetSphereCoordinate(center, radius, speed * theta * 3.14, speed * theta));
			m_pShader.get()->SetVec3(Utils::GetUniformName(2, "color"), glm::vec3(0.2f, 0.8f, 0.2f));
			m_pShader.get()->SetFloat(Utils::GetUniformName(2, "intensity"), radius * 100.0f);
			m_pShader.get()->SetFloat(Utils::GetUniformName(2, "range"), 1024.0f);

			m_pShader.get()->SetInt(Utils::GetUniformName(3, "type"), 0);
			m_pShader.get()->SetVec3(Utils::GetUniformName(3, "position"), Hina::Math::GetSphereCoordinate(center, radius, speed * theta * 4.2, speed * theta * 2.4));
			m_pShader.get()->SetVec3(Utils::GetUniformName(3, "color"), glm::vec3(0.2f, 0.2f, 0.8f));
			m_pShader.get()->SetFloat(Utils::GetUniformName(3, "intensity"), radius * 100.0f);
			m_pShader.get()->SetFloat(Utils::GetUniformName(3, "range"), 1024.0f);

			m_pShader.get()->Unbind();
		}

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

		PushLayer(new PBRLayer("BasePBR"));
    }
};

Hina::Application *Hina::CreateApplication() {
    return new PBR;
}
