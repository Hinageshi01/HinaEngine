#pragma once

#include "Layer/Layer.h"

#include "Editor/EditorHierarchy.h"
#include "Editor/EditorInstrumentor.h"
#include "Editor/EditorLog.h"

#include "RenderCore/Framebuffer.h"

namespace Hina
{

class EditorLayer final : public Layer
{
public:
	EditorLayer(const std::shared_ptr<Framebuffer> &buffer) :
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

	void ShowHierarchy();
	void ShowLog();
	void ShowInstrumentor();

	EditorHierarchy m_hierarchy;
	EditorInstrumentor m_instrumentor;
	EditorLog m_log;

	std::shared_ptr<Framebuffer> m_sceneFramebuffer;
	std::shared_ptr<Scene> m_scene;
	
	glm::vec2 m_sceneSize = glm::vec2(0.0f, 0.0f);

	bool m_blockEvents = false;
};

} // namespace Hina
