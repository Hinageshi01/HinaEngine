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

class ExampleLayer : public Hina::Layer
{
public:
	ExampleLayer() = default;
	ExampleLayer(const ExampleLayer &) = delete;
	ExampleLayer &operator=(const ExampleLayer &) = delete;
	ExampleLayer(ExampleLayer &&) = delete;
	ExampleLayer &operator=(ExampleLayer &&) = delete;

	virtual void OnAttach() override {
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
		m_camera.OnUpdate(deltaTime);

		Hina::Renderer::ClearBuffers(glm::vec4(0.1f, 0.1f, 0.11f, 1.0f), 1.0f);

		Hina::Window &window = Hina::Application::Get().GetWindow();
		const glm::mat4 view = m_camera.GetCamera().GetViewMatrix();
		const glm::mat4 projection = m_camera.GetCamera().GetProjectionMatrix(window.GetWidth(), window.GetHeight());

		Hina::Renderer::SetViewMatrix(view);
		Hina::Renderer::SetProjectionMatrix(projection);

		// tmp
		m_texture->Bind(0);
		m_shader->Bind();
		m_shader->SetInt("us_albedo", 0);

		Hina::Renderer::BeginScene();
		Hina::Renderer::Submit(m_shader, m_vertexArray);
		Hina::Renderer::EndScene();
	}

	virtual void OnEvent(Hina::Event &event) override {
		Hina::EventDispatcher dispatcher(event);

		m_camera.OnEvent(event);
	}

	virtual void OnImGuiRender() override {

	}

private:
	std::shared_ptr<Hina::VertexArray> m_vertexArray;
	std::shared_ptr<Hina::Shader> m_shader;
	std::shared_ptr<Hina::Texture2D> m_texture;
	Hina::FirstPersonCamera m_camera;
};

class PBR : public Hina::Application
{
public:
    PBR() {
		PushLater(new ExampleLayer);
    }
};

Hina::Application *Hina::CreateApplication() {
    return new PBR;
}
