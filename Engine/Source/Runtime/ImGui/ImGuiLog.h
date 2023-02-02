#pragma once

#include "imgui.h"

namespace Hina
{

class ImGuiLog
{
public:
    enum class LogCategory
    {
        None = 0,
        TRACE, INFO, WARN, ERRO, FATAL,
    };

    ImGuiLog(const ImGuiLog &) = delete;
    ImGuiLog &operator=(const ImGuiLog &) = delete;
    ImGuiLog(ImGuiLog &&) = delete;
    ImGuiLog &operator=(ImGuiLog &&) = delete;

    static ImGuiLog *Get();
    
    void Clear();
    void AddLog(const char *fmt, ...);
    void AddSpdLog(const std::ostringstream &oss, bool cearBuffer = true);
    void Draw(const char *title, bool *p_open = nullptr);

private:
    ImGuiLog();
    ~ImGuiLog();

    ImGuiTextBuffer m_buffer;
    ImGuiTextFilter m_fillter;
    // Index to lines offset. We maintain this with AddLog() calls.
    ImVector<int> m_lineOffsets;
};

} // namespace Hina
