#pragma once

namespace Hina
{

class ImGuiContext
{
public:
	virtual ~ImGuiContext() = default;

	virtual void Init() = 0;
	virtual void Shutdown() = 0;

	virtual void Begin() = 0;
	virtual void End() = 0;

	virtual void SetDarkTheme() = 0;

	virtual uint32_t GetActiveWidgetID() = 0;

	static std::unique_ptr<ImGuiContext> Creat();
};

} // namespace Hina
