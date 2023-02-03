#include "hnpch.h"

#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

static const std::string vShader = R"(
	#version 330 core
	layout(location = 0) in vec3 a_position;
	layout(location = 1) in vec4 a_color;
	out vec3 v_position;
	out vec4 v_color;
	
	void main()
	{
		v_color = a_color;
		v_position = a_position;
		gl_Position = vec4(v_position, 1.0);
	}
)";

static const std::string fShader = R"(
	#version 330 core
	layout(location = 0) out vec4 color;
	in vec3 v_position;
	in vec4 v_color;
	
	void main()
	{
		color = v_color;
	}
)";

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

	{ // tmp
		m_vertexArray = std::make_shared<OpenGLVertexArray>();
		std::shared_ptr<OpenGLVertexBuffer> m_vertexBuffer = std::make_shared<OpenGLVertexBuffer>(sizeof(vertices), vertices);
		std::shared_ptr<OpenGLIndexBuffer> m_indexBuffer = std::make_shared<OpenGLIndexBuffer>(sizeof(indices) / sizeof(uint32_t), indices);

		BufferLayout bufferLayout = {
			{ ShaderDataType::Float3, "a_position" },
			{ ShaderDataType::Float4, "a_color" }
		};
		m_vertexBuffer->SetLayout(std::move(bufferLayout));

		m_vertexArray->AddVertexBuffer(m_vertexBuffer);
		m_vertexArray->SetIndexBuffer(m_indexBuffer);

		m_shader = std::make_unique<OpenGLShader>(vShader, fShader);
	}

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
		glViewport(0, 0, m_window->GetWidth(), m_window->GetHeight());

		m_window->BeginOfFrame();

		m_window->OnUpdate();
		for(Layer *layer : m_layerStack) {
			layer->OnUpdate();
		}

		{ // tmp
			m_shader->Bind();
			glDrawElements(GL_TRIANGLES, m_vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
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
