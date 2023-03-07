#pragma once

namespace Hina
{

class EditorContext
{
public:
	virtual ~EditorContext() = default;

	virtual void Init() = 0;
	virtual void Shutdown() = 0;

	virtual void Begin() = 0;
	virtual void End() = 0;

	virtual uint32_t GetActiveWidgetID() = 0;

	static std::unique_ptr<EditorContext> Creat();
};

} // namespace Hina
