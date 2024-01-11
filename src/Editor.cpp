#include "Editor.h"


namespace Editor
{
	
    //Funkcje ustawień
    void Settings()
    {   
        //Ustawienie czcionki
        ImGui::GetIO().FontGlobalScale = 2.f;

        //ustawienie dockingu
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGuiStyle& style = ImGui::GetStyle();
        // Krawedzie
        style.FrameRounding = 12.0f;
        style.GrabRounding = 12.0f;
        // Kolor tekstu
        style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    }

    void Environment()
    {   
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", nullptr, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                ImGui::MenuItem("Padding", NULL, &opt_padding);
                ImGui::Separator();

                if (ImGui::MenuItem("Flag: NoDockingOverCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingOverCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingOverCentralNode; }
                if (ImGui::MenuItem("Flag: NoDockingSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingSplit; }
                if (ImGui::MenuItem("Flag: NoUndocking", "", (dockspace_flags & ImGuiDockNodeFlags_NoUndocking) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoUndocking; }
                if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
                if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
                if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
                ImGui::Separator();

                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Text"))
            {
                if (ImGui::MenuItem("Open"))
                {
                    OpenFile(text);
                }

                if (ImGui::MenuItem("Save"))
                {
                    SaveFile(text, "plik");
                }

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        ImGui::End();
    }

    void RenderPlot(const std::vector<float>& data, const char* plotTitle)
    {
        if (ImPlot::BeginPlot(plotTitle)) {
            ImPlot::PlotLine("Line Plot", data.data(), static_cast<int>(data.size()));
            ImPlot::EndPlot();
        }
    }

    void TextEditor()
    {
        ImVec2 windowSize = ImGui::GetIO().DisplaySize;
        ImGui::SetNextWindowSize(ImVec2(600, 400)); // Set an explicit size for the window
        ImGui::Begin("TextEditor");

        if (ImGui::InputTextMultiline("##source", text, sizeof(text), windowSize, ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_EnterReturnsTrue)) {
            // Your code to handle text input changes goes here
        }

        //DrawMultilineColoredText(text);

        ImGui::End();
    }

    // Function to format JSON
    std::string FormatJSON(const char* json)
    {
        std::string result;
        int indentationLevel = 0;

        for (int i = 0; json[i]; i++) {
            char c = json[i];
            if (c == '{' || c == '[') {
                result += c;
                result += '\n';
                indentationLevel++;
                for (int j = 0; j < indentationLevel; j++) {
                    result += "    ";
                }
            }
            else if (c == '}' || c == ']') {
                result += '\n';
                indentationLevel--;
                for (int j = 0; j < indentationLevel; j++) {
                    result += "    ";
                }
                result += c;
            }
            else if (c == ',') {
                result += c;
                result += '\n';
                for (int j = 0; j < indentationLevel; j++) {
                    result += "    ";
                }
            }
            else {
                result += c;
            }
        }

        return result;
    }

    void FormatToJson()
    {
        char jsonText[1024] = "";
        std::string outputText;  // Use std::string instead of char array

        ImGui::Begin("Text Input and Output");

        ImGui::Text("Input Text:");

        ImGui::InputTextMultiline("##InputText", jsonText, sizeof(jsonText), ImVec2(-1.0f, ImGui::GetTextLineHeight() * 8));

        if (ImGui::Button("FormatJson")) {
            outputText = FormatJSON(jsonText);
        }

        // Add a label for output text
        ImGui::Text("Output Text:");

        // Display the multiline output text
        ImGui::TextWrapped(outputText.c_str());  // Convert to const char* before passing to ImGui

        // End ImGui frame
        ImGui::End();
    }

    //Funkcja od renderowania co klatke
    void Render()
    {
        Environment();

        ImGui::Begin("Aplikacja");
        // Kod do kolorowania składni
        //std::string pythonCode = "def hello_world():print('Hello, World!')";
        DrawMultilineColoredText(text);

        ImGui::End();
        
        PlotDataFunction();

        TextEditor();
        
        FormatToJson();
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

    //Funkcje wspomagajace uzytkownika
    void SaveFile(const char* text, const char* fileName)
    {
        std::ofstream outputFile("C:\\Users\\macko\\Projekty\\Outputy\\test.txt");
        if (outputFile.is_open())
        {
            outputFile << text;
            outputFile.close();
        }
    };

    void OpenFile(char* text)
    {
        std::ifstream inputFile("C:\\Users\\macko\\Projekty\\Outputy\\test.txt");

        if (inputFile.is_open())
        {
            std::stringstream buffer;
            buffer << inputFile.rdbuf();

            std::string fileContent = buffer.str();
            if (fileContent.length() >= strlen(text))
                strcpy(text, fileContent.c_str());

            inputFile.close();
        }
    }

    void HighlightText(const char* text, const char* highlight)
    {
        const char* remainingText = text;

        while (const char* found = strstr(remainingText, highlight))
        {
            ImGui::TextUnformatted(remainingText, found);

            ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "%.*s", (int)strlen(highlight), found);

            remainingText = found + strlen(highlight);
        }
    }

    void Find(char* text, bool* pOpen)
    {


    }

    void Replace(char* text)
    {

    }

    void ReplaceAll(char* text)
    {
    }

};