#pragma once

#include "imgui.h"

namespace Hina
{

class ImGuiLog
{
public:
    ImGuiLog(const ImGuiLog &) = delete;
    ImGuiLog &operator=(const ImGuiLog &) = delete;
    ImGuiLog(ImGuiLog &&) = delete;
    ImGuiLog &operator=(ImGuiLog &&) = delete;

    ImGuiTextBuffer m_buffer;
    ImGuiTextFilter m_fillter;
    // Index to lines offset. We maintain this with AddLog() calls.
    ImVector<int> m_lineOffsets;
    // Keep scrolling if already at the bottom.
    bool m_isAutoScroll = true;

    static ImGuiLog *Get();

    void Clear();
    void AddLog(const char *fmt, ...);
    void AddSpdLog(const std::ostringstream &oss, bool cearBuffer = true);
    void Draw(const char *title, bool *p_open = nullptr);

private:
    ImGuiLog();
    ~ImGuiLog();
};

} // namespace Hina