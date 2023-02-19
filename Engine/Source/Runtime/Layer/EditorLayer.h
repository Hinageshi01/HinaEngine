#pragma once

#include "Layer/Layer.h"

#include "ImGui/ImGuiLog.h"
#include "ImGui/ImGuiInstrumentor.h"

#include "RenderCore/Framebuffer.h"

namespace Hina
{

class EditorLayer final : public Layer
{
public:
	EditorLayer(std::shared_ptr<Framebuffer> buffer) :
		Layer("Editor"), m_sceneFramebuffer(buffer) {}
	
	EditorLayer() = delete;
	EditorLayer(const EditorLayer &) = default;
	EditorLayer &operator=(const EditorLayer &) = default;
	EditorLayer(EditorLayer &&) = default;
	EditorLayer &operator=(EditorLayer &&) = default;
	virtual ~EditorLayer() = default;

	virtual void OnAttach();
	virtual void OnDetach();

	virtual void Begin();
	virtual void OnUpdate(const DeltaTime deltaTime);
	virtual void End();

	virtual void OnImGuiRender();

	virtual void OnEvent(Event &event);

private:
	void ShowDockSpace();
	void ShowScene();
	void ShowLog();
	void ShowInstrumentor();

	ImGuiLog m_log;
	ImGuiInstrumentor m_instrumentor;

	std::shared_ptr<Framebuffer> m_sceneFramebuffer;
	
	glm::vec2 m_sceneSize;
	bool m_show = true;
};

} // namespace Hina
