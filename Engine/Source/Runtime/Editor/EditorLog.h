#pragma once

#include <imgui.h>

namespace Hina
{

enum class LogLevel : uint8_t
{
    None  = 0x00,
    Trace = 1 << 0,
    Info  = 1 << 1,
    Warn  = 1 << 2,
    Error = 1 << 3,
    Fatal = 1 << 4,
    All   = 0xff,
};

class EditorLog final
{
public:
    EditorLog() = default;
    EditorLog(const EditorLog &) = delete;
    EditorLog &operator=(const EditorLog &) = delete;
    EditorLog(EditorLog &&) = default;
    EditorLog &operator=(EditorLog &&) = default;
    ~EditorLog() = default;

    void OnImGuiRender();

    void Clear();
    void AddLog(const char *fmt, ...);
    void AddSpdLog(const std::ostringstream &oss, bool cearBuffer = true);

private:
    void CreateButton(LogLevel level);

    const ImVec4 GetLevelColor(LogLevel level) const;
    const char *GetLevelButtonNume(LogLevel level) const;
    const std::string GetFilterStr() const;

    void SetOutputColor(std::string_view str) const;

    ImGuiTextBuffer m_buffer;
    ImGuiTextFilter m_fillter;
    ImVector<int> m_lineOffsets;

    uint8_t m_levelFilter = static_cast<uint8_t>(LogLevel::All);
};

} // namespace Hina
