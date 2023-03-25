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

class PBRLayer final : public Hina::Layer
{
public:
	explicit PBRLayer(const std::string &str) : Layer(str) {}
	explicit PBRLayer(std::string &&str) : Layer(str) {}
	
	PBRLayer() = delete;
	PBRLayer(const PBRLayer &) = default;
	PBRLayer &operator=(const PBRLayer &) = default;
	PBRLayer(PBRLayer &&) = default;
	PBRLayer &operator=(PBRLayer &&) = default;
	~PBRLayer() = default;

	virtual void OnAttach() override {
		HN_PROFILE_FUNCTION();

		Hina::RenderCore::SetCameraController(m_cameraController);

		// tmp
		{
			std::shared_ptr<Hina::VertexBuffer> vertexBuffer = Hina::VertexBuffer::Create(sizeof(vertices), vertices);
			std::shared_ptr<Hina::IndexBuffer> indexBuffer = Hina::IndexBuffer::Create(sizeof(indices), indices);

			Hina::BufferLayout bufferLayout = {
				{ Hina::ShaderDataType::Float3, "a_position" },
				{ Hina::ShaderDataType::Float3, "a_normal" },
				{ Hina::ShaderDataType::Float2, "a_textureCoord" },
			};
			vertexBuffer->SetLayout(std::move(bufferLayout));

			m_pVertexArray = Hina::VertexArray::Create();
			m_pVertexArray->AddVertexBuffer(vertexBuffer);
			m_pVertexArray->SetIndexBuffer(indexBuffer);

			m_pShader = Hina::Shader::Create(
				"testShader",
				Hina::Path::FromAsset("Shader/v_testShader.glsl"),
				Hina::Path::FromAsset("Shader/f_testShader.glsl"));

			m_pTexture = Hina::Texture2D::Create(Hina::Path::FromAsset("Texture/japanese_stone_wall_diff.png"));
		}
	}

	virtual void OnDetach() override {

	}

	virtual void OnUpdate(const Hina::DeltaTime deltaTime) override {
		HN_PROFILE_FUNCTION();

		m_cameraController.OnUpdate(deltaTime);

		Hina::RenderCore::SetClears(glm::vec4(0.7f, 0.8f, 0.8f, 1.0f), 1.0f);
		Hina::RenderCore::SetDefaultMatrices();

		// tmp
		{
			m_pShader->Bind();
			m_pTexture->Bind(0);
			m_pShader->SetInt("us_albedo", 0);
		}
		
		Hina::RenderCore::BeginScene();
		Hina::RenderCore::Submit(m_pShader, m_pVertexArray);
		Hina::RenderCore::EndScene();
	}

	virtual void OnEvent(Hina::Event &event) override {
		HN_PROFILE_FUNCTION();

		m_cameraController.OnEvent(event);
	}

	virtual void OnImGuiRender() override {

	}

private:
	std::shared_ptr<Hina::VertexArray> m_pVertexArray;
	std::shared_ptr<Hina::Shader> m_pShader;
	std::shared_ptr<Hina::Texture2D> m_pTexture;

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
