#include "hnpch.h"
#include "Hina.h"

static constexpr float vertices[] = {
	-1.0,  1.0, -1.0,  0.0,  1.0,  0.0,
	 1.0,  1.0,  1.0,  0.0,  1.0,  0.0,
	 1.0,  1.0, -1.0,  0.0,  1.0,  0.0,

	 1.0,  1.0,  1.0,  0.0,  0.0,  1.0,
	-1.0, -1.0,  1.0,  0.0,  0.0,  1.0,
	 1.0, -1.0,  1.0,  0.0,  0.0,  1.0,

	-1.0,  1.0,  1.0, -1.0,  0.0,  0.0,
	-1.0, -1.0, -1.0, -1.0,  0.0,  0.0,
	-1.0, -1.0,  1.0, -1.0,  0.0,  0.0,

	 1.0, -1.0, -1.0,  0.0, -1.0,  0.0,
	-1.0, -1.0,  1.0,  0.0, -1.0,  0.0,
	-1.0, -1.0, -1.0,  0.0, -1.0,  0.0,

	 1.0,  1.0, -1.0,  1.0,  0.0,  0.0,
	 1.0, -1.0,  1.0,  1.0,  0.0,  0.0,
	 1.0, -1.0, -1.0,  1.0,  0.0,  0.0,

	-1.0,  1.0, -1.0,  0.0,  0.0, -1.0,
	 1.0, -1.0, -1.0,  0.0,  0.0, -1.0,
	-1.0, -1.0, -1.0,  0.0,  0.0, -1.0,

	-1.0,  1.0, -1.0,  0.0,  1.0,  0.0,
	-1.0,  1.0,  1.0,  0.0,  1.0,  0.0,
	 1.0,  1.0,  1.0,  0.0,  1.0,  0.0,

	 1.0,  1.0,  1.0,  0.0,  0.0,  1.0,
	-1.0,  1.0,  1.0,  0.0,  0.0,  1.0,
	-1.0, -1.0,  1.0,  0.0,  0.0,  1.0,

	-1.0,  1.0,  1.0, -1.0,  0.0,  0.0,
	-1.0,  1.0, -1.0, -1.0,  0.0,  0.0,
	-1.0, -1.0, -1.0, -1.0,  0.0,  0.0,

	 1.0, -1.0, -1.0,  0.0, -1.0,  0.0,
	 1.0, -1.0,  1.0,  0.0, -1.0,  0.0,
	-1.0, -1.0,  1.0,  0.0, -1.0,  0.0,

	 1.0,  1.0, -1.0,  1.0,  0.0,  0.0,
	 1.0,  1.0,  1.0,  1.0,  0.0,  0.0,
	 1.0, -1.0,  1.0,  1.0,  0.0,  0.0,

	-1.0,  1.0, -1.0,  0.0,  0.0, -1.0,
	 1.0,  1.0, -1.0,  0.0,  0.0, -1.0,
	 1.0, -1.0, -1.0,  0.0,  0.0, -1.0,
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
		};
		m_vertexBuffer->SetLayout(std::move(bufferLayout));

		m_vertexArray->AddVertexBuffer(m_vertexBuffer);
		m_vertexArray->SetIndexBuffer(m_indexBuffer);

		// TODO : Use relative path.
		const std::string vsPath = "D:/Works/HinaEngine/Engine/Source/Asset/Shader/v_testShader.glsl";
		const std::string fsPath = "D:/Works/HinaEngine/Engine/Source/Asset/Shader/f_testShader.glsl";
		m_shader = Hina::Shader::Create("testShader", vsPath, fsPath);
	}

	virtual void OnDetach() override {
		
	}

	virtual void OnUpdate() override {
		Hina::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.11f, 1.0f });
		Hina::RenderCommand::Clear();

		Hina::Window &window = Hina::Application::Get().GetWindow();
		const glm::mat4 model = glm::identity<glm::mat4>();
		const glm::mat4 view = camera.GetViewMatrix();
		const glm::mat4 projection = camera.GetProjectionMatrix(window.GetWidth(), window.GetHeight());

		Hina::Renderer::SetModelMatrix(model);
		Hina::Renderer::SetViewMatrix(view);
		Hina::Renderer::SetProjectionMatrix(projection);

		Hina::Renderer::BeginScene();
		Hina::Renderer::Submit(m_shader, m_vertexArray);
		Hina::Renderer::EndScene();
	}

	virtual void OnEvent(Hina::Event &event) {
		
	}

private:
	std::shared_ptr<Hina::VertexArray> m_vertexArray;
	std::shared_ptr<Hina::Shader> m_shader;
	Hina::Camera camera;
};

class PBR : public Hina::Application
{
public:
    PBR() {
		PushLater(new ExampleLayer);
    }

    ~PBR() {

    }
};

Hina::Application *Hina::CreateApplication() {
    return new PBR;
}
