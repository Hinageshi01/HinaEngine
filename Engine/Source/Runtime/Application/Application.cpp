#include "hnpch.h"
#include "Application.h"

#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

namespace Hina
{

static float vertices[] = {
	  0.5f,  0.5f, 0.0f, 0.9f, 0.2f, 0.2f, 1.0f,
	  0.5f, -0.5f, 0.0f, 0.2f, 0.9f, 0.2f, 1.0f,
	 -0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.9f, 1.0f,
	 -0.5f,  0.5f, 0.0f, 0.9f, 0.9f, 0.2f, 1.0f,
};

static uint32_t indices[] = {
	0, 1, 3,
	1, 2, 3,
};

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

Application *Application::s_instance = nullptr;

Application::Application() {
	assert(!s_instance && "Application instance already exist.");
	s_instance = this;

	Hina::Log::Init();
	HN_CORE_INFO("Initialized Log");
	HN_CORE_WARN("Warning log test");
	HN_CORE_ERROR("Error log test");
	HN_CORE_FATAL("Fatal log test");

	m_window = Window::Create();
	m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

	m_imguiLayer = new ImGuiLayer();
	PushOverlay(m_imguiLayer);

	m_isRunning = true;

	m_vertexArray = VertexArray::Create();
	std::shared_ptr<VertexBuffer> m_vertexBuffer = VertexBuffer::Create(sizeof(vertices), vertices);
	std::shared_ptr<IndexBuffer> m_indexBuffer = IndexBuffer::Create(sizeof(indices) / sizeof(uint32_t), indices);

	BufferLayout bufferLayout = {
		{ ShaderDataType::Float3, "a_position" },
		{ ShaderDataType::Float4, "a_color" }
	};
	m_vertexBuffer->SetLayout(std::move(bufferLayout));

	m_vertexArray->AddVertexBuffer(m_vertexBuffer);
	m_vertexArray->SetIndexBuffer(m_indexBuffer);

	// TODO : Use relative path.
	const std::string vsPath = "D:/Works/HinaEngine/Engine/Source/Asset/v_testShader.glsl";
	const std::string fsPath = "D:/Works/HinaEngine/Engine/Source/Asset/f_testShader.glsl";
	m_shader = Shader::Create("testShader", vsPath, fsPath);
}

Application::~Application() {

}

void Application::PushLater(Layer *layer) {
	m_layerStack.PushLayer(layer);
	layer->OnAttach();
}

void Application::PushOverlay(Layer *layer) {
	m_layerStack.PushOverlay(layer);
	layer->OnAttach();
}

void Application::Run() {
	while(m_isRunning) {
		m_window->BeginOfFrame();

		RenderCommand::SetClearColor({ 0.7f, 0.8f, 0.9f, 1.0f });
		RenderCommand::Clear();
		Renderer::BeginScene();
		Renderer::Submit(m_shader, m_vertexArray);
		Renderer::EndScene();

		m_window->OnUpdate();
		for(Layer *layer : m_layerStack) {
			layer->OnUpdate();
		}

		// TODO : Can we change these to static functions?
		m_imguiLayer->BeginOfFrame();
		for(Layer *layer : m_layerStack) {
			layer->OnImGuiRender();
		}
		m_imguiLayer->EndOfFrame();

		m_window->EndOfFrame();
	}
}

void Application::OnEvent(Event &event) {
	HN_CORE_TRACE(event);

	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

	for(auto it = m_layerStack.end(); it != m_layerStack.begin(); /**/) {
		// Handel event by layer from high layer to low layer.
		// Example: if a click event be handled by UI layer,
		// it won't influence any layer behined UI.
		(*--it)->OnEvent(event);
		if(event.m_isHandled) {
			break;
		}
	}
}

bool Application::OnWindowClose(WindowCloseEvent &event) {
	m_isRunning = false;
	return true;
}

} // namespace Hina
