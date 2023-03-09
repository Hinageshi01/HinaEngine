#pragma once

#include "Layer/Layer.h"

#include "Editor/EditorDetails.h"
#include "Editor/EditorLog.h"
#include "Editor/EditorOutliner.h"
#include "Editor/EditorProfiler.h"

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

	void ShowDetails();
	void ShowLog();
	void ShowOutLiner();
	void ShowProfiler();

	void SetSelectedEntity();

	EditorDetails m_detaills;
	EditorLog m_log;
	EditorOutliner m_outliner;
	EditorProfiler m_profiler;

	std::shared_ptr<Framebuffer> m_sceneFramebuffer;
	
	glm::vec2 m_sceneSize = glm::vec2(0.0f, 0.0f);

	bool m_blockEvents = false;
};

} // namespace Hina
