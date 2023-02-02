#include "hnpch.h"

#include "ImGuiLog.h"

namespace Hina
{

ImGuiLog::ImGuiLog() {
    m_isAutoScroll = true;
    Clear();
}

ImGuiLog::~ImGuiLog() {

}

ImGuiLog *ImGuiLog::Get() {
    static ImGuiLog instance;
    return &instance;
}

void ImGuiLog::Clear() {
    m_buffer.clear();
    m_lineOffsets.clear();
    m_lineOffsets.push_back(0);
}

void ImGuiLog::AddLog(const char *fmt, ...) {
    int old_size = m_buffer.size();
    va_list args;
    va_start(args, fmt);
    m_buffer.appendfv(fmt, args);
    va_end(args);
    for(int new_size = m_buffer.size(); old_size < new_size; old_size++) {
        if(m_buffer[old_size] == '\n') {
            m_lineOffsets.push_back(old_size + 1);
        }
    }
}

void ImGuiLog::AddSpdLog(const std::ostringstream &oss, bool clearBuffer) {
    AddLog(oss.str().c_str());
    if(clearBuffer) {
        // TODO : It's quite uncomfortable that codes coupled together like this.
        Log::ClearBuffer();
    }
}

void ImGuiLog::Draw(const char *title, bool *p_open) {
    if(!ImGui::Begin(title, p_open)) {
        ImGui::End();
        return;
    }

    // Options menu
    if(ImGui::BeginPopup("Options")) {
        ImGui::Checkbox("Auto-scroll", &m_isAutoScroll);
        ImGui::EndPopup();
    }

    // Main window
    if(ImGui::Button("Options")) {
        ImGui::OpenPopup("Options");
    }
    ImGui::SameLine();
    bool clear = ImGui::Button("Clear");
    ImGui::SameLine();
    bool copy = ImGui::Button("Copy");
    ImGui::SameLine();
    m_fillter.Draw("Filter", -100.0f);

    ImGui::Separator();

    if(ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar)) {
        if(clear) {
            Clear();
        }
        if(copy) {
            ImGui::LogToClipboard();
        }

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        const char *buf = m_buffer.begin();
        const char *buf_end = m_buffer.end();
        if(m_fillter.IsActive()) {
            // In this example we don't use the clipper when Filter is enabled.
            // This is because we don't have random access to the result of our filter.
            // A real application processing logs with ten of thousands of entries may want to store the result of
            // search/filter.. especially if the filtering function is not trivial (e.g. reg-exp).
            for(int line_no = 0; line_no < m_lineOffsets.Size; line_no++) {
                const char *line_start = buf + m_lineOffsets[line_no];
                const char *line_end = (line_no + 1 < m_lineOffsets.Size) ? (buf + m_lineOffsets[line_no + 1] - 1) : buf_end;
                if(m_fillter.PassFilter(line_start, line_end)) {
                    ImGui::TextUnformatted(line_start, line_end);
                }
            }
        }
        else {
            // The simplest and easy way to display the entire buffer:
            //   ImGui::TextUnformatted(buf_begin, buf_end);
            // And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward
            // to skip non-visible lines. Here we instead demonstrate using the clipper to only process lines that are
            // within the visible area.
            // If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them
            // on your side is recommended. Using ImGuiListClipper requires
            // - A) random access into your data
            // - B) items all being the  same height,
            // both of which we can handle since we have an array pointing to the beginning of each line of text.
            // When using the filter (in the block of code above) we don't have random access into the data to display
            // anymore, which is why we don't use the clipper. Storing or skimming through the search result would make
            // it possible (and would be recommended if you want to search through tens of thousands of entries).
            ImGuiListClipper clipper;
            clipper.Begin(m_lineOffsets.Size);
            while(clipper.Step()) {
                for(int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++) {
                    const char *line_start = buf + m_lineOffsets[line_no];
                    const char *line_end = (line_no + 1 < m_lineOffsets.Size) ? (buf + m_lineOffsets[line_no + 1] - 1) : buf_end;
                    ImGui::TextUnformatted(line_start, line_end);
                }
            }
            clipper.End();
        }
        ImGui::PopStyleVar();

        // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
        // Using a scrollbar or mouse-wheel will take away from the bottom edge.
        if(m_isAutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
            ImGui::SetScrollHereY(1.0f);
        }
    }
    ImGui::EndChild();
    ImGui::End();
}

}