#include "hnpch.h"
#include "Hina.h"

#include <GLFW/glfw3.h>

#include "RenderCore/Framebuffer.h"

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

		const Hina::Window &window = Hina::Application::Get().GetWindow();
		Hina::FramebufferInitializer framebufferInit;
		framebufferInit.m_height = window.GetHeight();
		framebufferInit.m_width = window.GetWidth();
		framebufferInit.m_samples = 1;
		framebufferInit.m_attachmentFormats = { Hina::FramebufferFormat::RGBA8, Hina::FramebufferFormat::DEPTH24STENCIL8 };
		m_framebuffer = Hina::Framebuffer::Create(framebufferInit);
	}

	virtual void OnDetach() override {

	}

	virtual void OnUpdate(const Hina::DeltaTime deltaTime) override {
		HN_PROFILE_FUNCTION();

		m_camera.OnUpdate(deltaTime);

		Hina::Window &window = Hina::Application::Get().GetWindow();
		const glm::mat4 view = m_camera.GetCamera().GetViewMatrix();
		const glm::mat4 projection = m_camera.GetCamera().GetProjectionMatrix(window.GetWidth(), window.GetHeight());

		Hina::RenderCore::SetViewMatrix(view);
		Hina::RenderCore::SetProjectionMatrix(projection);

		// tmp
		m_shader->Bind();
		m_texture->Bind(0);
		m_shader->SetInt("us_albedo", 0);

		m_framebuffer->Bind();
		Hina::RenderCore::ClearBuffers(glm::vec4(0.7f, 0.8f, 0.8f, 1.0f), 1.0f);
		Hina::RenderCore::Submit(m_shader, m_vertexArray);
		m_framebuffer->Unbind();
	}

	virtual void OnEvent(Hina::Event &event) override {
		HN_PROFILE_FUNCTION();

		Hina::EventDispatcher dispatcher(event);

		m_camera.OnEvent(event);
	}

	virtual void OnImGuiRender() override {
		HN_PROFILE_FUNCTION();

		bool show = true;

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		const ImGuiViewport *viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace", &show, windowFlags);
		ImGui::PopStyleVar(3);

		// Submit the DockSpace
		ImGuiIO &io = ImGui::GetIO();
		if(io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			ImGuiID dockspaceID = ImGui::GetID("DockSpace");
			ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_AutoHideTabBar);
		}

		if(ImGui::BeginMenuBar()) {
			if(ImGui::BeginMenu("Options")) {
				if(ImGui::MenuItem("Close")) {

				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::Begin("Scene");
		ImGui::Image((void *)m_framebuffer->GetColorAttachmentRenderID(0), ImGui::GetWindowSize(), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();

		Hina::ImGuiLog::Get()->AddSpdLog(Hina::Log::GetSpdOutput());
		Hina::ImGuiLog::Get()->Draw("Log:", &show);

		ImGui::Begin("Profile", &show);
		ImGui::Text("FPS: %.1f", timer.GetFPS());
		ImGui::Text("One frame: %.3f ms", timer.ElapsedMillis());
		timer.Reset();
		ImGui::End();

		ImGui::End();
	}

private:
	std::shared_ptr<Hina::VertexArray> m_vertexArray;
	std::shared_ptr<Hina::Shader> m_shader;
	std::shared_ptr<Hina::Texture2D> m_texture;
	Hina::FirstPersonCamera m_camera;
	Hina::Timer timer;

	std::shared_ptr<Hina::Framebuffer> m_framebuffer;
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
