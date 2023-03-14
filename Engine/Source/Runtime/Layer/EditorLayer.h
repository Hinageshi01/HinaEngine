#pragma once

#include "Layer/Layer.h"

#include "Editor/EditorDetails.h"
#include "Editor/EditorLog.h"
#include "Editor/EditorOutliner.h"
#include "Editor/EditorProfiler.h"

namespace Hina
{

class EditorLayer final : public Layer
{
public:
	EditorLayer() : Layer("Editor") {}
	
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

	glm::vec2 m_primaryFramebufferSize = glm::vec2(0.0f, 0.0f);

	bool m_blockEvents = false;
};

} // namespace Hina
