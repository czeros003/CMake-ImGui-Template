#include "Editor.h"
#include <imgui.h>
#include <implot.h>

namespace Editor
{
    void RenderPlot(const std::vector<float>& data, const char* plotTitle)
    {
        if (ImPlot::BeginPlot(plotTitle)) {
            ImPlot::PlotLine("Line Plot", data.data(), static_cast<int>(data.size()));
            ImPlot::EndPlot();
        }
    }

    void DrawMultilineColoredText(const std::string& text) {
        ImVec4 keywordColor = ImVec4(0.9f, 0.2f, 0.2f, 1.0f);
        ImVec4 stringColor = ImVec4(0.5f, 0.8f, 0.5f, 1.0f);
        ImVec4 textColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

        size_t pos = 0;
        size_t start = 0;

        while (pos < text.size()) {
            if (text.compare(pos, 3, "def") == 0 || text.compare(pos, 4, "print") == 0) {
                ImGui::TextColored(keywordColor, "%s", text.substr(start, pos - start).c_str());
                ImGui::TextColored(keywordColor, "%s", text.substr(pos, 3).c_str());
                start = pos + 3;
                pos += 3;
            }
            else if (text[pos] == '\'' || text[pos] == '"') {
                size_t end = text.find(text[pos], pos + 1);
                if (end != std::string::npos) {
                    ImGui::TextColored(textColor, "%s", text.substr(start, pos - start).c_str());
                    ImGui::TextColored(stringColor, "%s", text.substr(pos, end - pos + 1).c_str());
                    start = end + 1;
                    pos = end + 1;
                }
            }
            else {
                pos += 1;
            }
        }

        if (start < text.size()) {
            ImGui::TextColored(textColor, "%s", text.substr(start).c_str());
        }
    }
}