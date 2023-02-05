#include "hnpch.h"
#include "Hina.h"

static const float vertices[] = {
	  0.5f,  0.5f, 0.0f, 0.9f, 0.2f, 0.2f, 1.0f,
	  0.5f, -0.5f, 0.0f, 0.2f, 0.9f, 0.2f, 1.0f,
	 -0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.9f, 1.0f,
	 -0.5f,  0.5f, 0.0f, 0.9f, 0.9f, 0.2f, 1.0f,
};

static const uint32_t indices[] = {
	0, 1, 3,
	1, 2, 3,
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
			{ Hina::ShaderDataType::Float4, "a_color" }
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
		Hina::RenderCommand::SetClearColor({ 0.7f, 0.8f, 0.9f, 1.0f });
		Hina::RenderCommand::Clear();

		Hina::Renderer::BeginScene();
		Hina::Renderer::Submit(m_shader, m_vertexArray);
		Hina::Renderer::EndScene();
	}

	virtual void OnEvent(Hina::Event &event) {
		
	}

private:
	std::shared_ptr<Hina::VertexArray> m_vertexArray;
	std::shared_ptr<Hina::Shader> m_shader;
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
