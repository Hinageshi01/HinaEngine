#include "hnpch.h"
#include "Hina.h"

#include <GLFW/glfw3.h>

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

class ExampleLayer final : public Hina::Layer
{
public:
	explicit ExampleLayer(const std::string &str) : Layer(str) {}
	explicit ExampleLayer(std::string &&str) : Layer(str) {}
	
	ExampleLayer() = delete;
	ExampleLayer(const ExampleLayer &) = default;
	ExampleLayer &operator=(const ExampleLayer &) = default;
	ExampleLayer(ExampleLayer &&) = default;
	ExampleLayer &operator=(ExampleLayer &&) = default;
	~ExampleLayer() = default;

	virtual void OnAttach() override {
		HN_PROFILE_FUNCTION();

		m_vertexArray = Hina::VertexArray::Create();
		std::shared_ptr<Hina::VertexBuffer> m_vertexBuffer = Hina::VertexBuffer::Create(sizeof(vertices), vertices);
		std::shared_ptr<Hina::IndexBuffer> m_indexBuffer = Hina::IndexBuffer::Create(sizeof(indices) / sizeof(uint32_t), indices);

		Hina::BufferLayout bufferLayout = {
			{ Hina::ShaderDataType::Float3, "a_position" },
			{ Hina::ShaderDataType::Float3, "a_normal" },
			{ Hina::ShaderDataType::Float2, "a_textureCoord" },
		};
		m_vertexBuffer->SetLayout(std::move(bufferLayout));

		m_vertexArray->AddVertexBuffer(m_vertexBuffer);
		m_vertexArray->SetIndexBuffer(m_indexBuffer);

		m_shader = Hina::Shader::Create(
			"testShader",
			Hina::Path::FromAsset("Shader/v_testShader.glsl"),
			Hina::Path::FromAsset("Shader/f_testShader.glsl"));
		
		m_texture = Hina::Texture2D::Create(Hina::Path::FromAsset("Texture/japanese_stone_wall_diff.png"));
	}

	virtual void OnDetach() override {

	}

	virtual void OnUpdate(const Hina::DeltaTime deltaTime) override {
		HN_PROFILE_FUNCTION();

		timer.Reset();

		m_camera.OnUpdate(deltaTime);

		Hina::RenderCore::ClearBuffers(glm::vec4(0.1f, 0.1f, 0.11f, 1.0f), 1.0f);

		Hina::Window &window = Hina::Application::Get().GetWindow();
		const glm::mat4 view = m_camera.GetCamera().GetViewMatrix();
		const glm::mat4 projection = m_camera.GetCamera().GetProjectionMatrix(window.GetWidth(), window.GetHeight());

		Hina::RenderCore::SetViewMatrix(view);
		Hina::RenderCore::SetProjectionMatrix(projection);

		// tmp
		m_texture->Bind(0);
		m_shader->Bind();
		m_shader->SetInt("us_albedo", 0);

		Hina::RenderCore::BeginScene();
		Hina::RenderCore::Submit(m_shader, m_vertexArray);
		Hina::RenderCore::EndScene();
	}

	virtual void OnEvent(Hina::Event &event) override {
		HN_PROFILE_FUNCTION();

		Hina::EventDispatcher dispatcher(event);

		m_camera.OnEvent(event);
	}

	virtual void OnImGuiRender() override {
		HN_PROFILE_FUNCTION();

		bool show = true;

		Hina::ImGuiLog::Get()->AddSpdLog(Hina::Log::GetSpdOutput());
		Hina::ImGuiLog::Get()->Draw("Log:", &show);

		ImGui::Begin("Profile");
		ImGui::Text("One frame: %.3f ms", timer.ElapsedMillis());
		ImGui::End();
	}

private:
	std::shared_ptr<Hina::VertexArray> m_vertexArray;
	std::shared_ptr<Hina::Shader> m_shader;
	std::shared_ptr<Hina::Texture2D> m_texture;
	Hina::FirstPersonCamera m_camera;
	Hina::Timer timer;
};

class PBR : public Hina::Application
{
public:
    PBR() {
		HN_PROFILE_FUNCTION();

		PushLayer(new ExampleLayer("Example"));
    }
};

Hina::Application *Hina::CreateApplication() {
    return new PBR;
}
