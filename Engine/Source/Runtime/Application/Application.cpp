#include "hnpch.h"

#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hina
{

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

Application *Application::s_instance = nullptr;

Application::Application() {
	assert(!s_instance && "Application instance already exist.");
	s_instance = this;

	Hina::Log::Init();
	HN_CORE_INFO("Initialized Log");

	m_window = Window::Create();
	m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

	m_imguiLayer = new ImGuiLayer();
	PushOverlay(m_imguiLayer);

	m_isRunning = true;

	{ // tmp
		static float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
		};

		static unsigned int indices[] = {
			0, 1, 3,
		};

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

		static const std::string vShader = R"(
			#version 330 core
			layout(location = 0) in vec3 a_position;
			out vec3 v_position;
			
			void main()
			{
				v_position = a_position;
				gl_Position = vec4(a_position, 1.0);
			}
		)";

		static const std::string fShader = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			in vec3 v_position;
			
			void main()
			{
				color = vec4(v_position * 0.5 + 0.5, 1.0);
			}
		)";

		m_shader = std::make_unique<GLShader>(vShader, fShader);
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
		m_shader->Bind();

		m_window->BeginOfFrame();

		m_window->OnUpdate();
		for(Layer *layer : m_layerStack) {
			layer->OnUpdate();
		}

		{ // tmp
			glBindVertexArray(m_VBO);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
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
