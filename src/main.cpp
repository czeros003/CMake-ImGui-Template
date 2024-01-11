#include "Editor.h"
#include "imgui.h"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "imgui_internal.h"
#include <implot.h>

int main() {
    // Inicjalizacja GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Konfiguracja GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Tworzenie okna GLFW
    GLFWwindow* window = glfwCreateWindow(1980, 1200, "Projekt", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Ustawienia kontekstu OpenGL
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Inicjalizacja ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    //kontekst implota
    ImPlot::CreateContext();

    if (!ImPlot::CreateContext()) {
        // Handle ImPlot initialization error
        fprintf(stderr, "ImPlot initialization failed.\n");
    }

    //docking
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    

    // Inicjalizacja ImGui dla GLFW i OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Configure ImGui docking
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);

    //Ustawienie czcionki
    ImGui::GetIO().FontGlobalScale = 2.f;
    std::vector<float> values = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
    // Główna pętla
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Rozpocznij ramkę ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /*
        * RENDEROWANIE TUTAJ
        * NIC NIE RUSZAC OPROCZ OD TEGO MIEJSCA
        * ------------------------------------------------------------------------------------------------------------------------------------
        */

        //Editor::Settings();


        Editor::Render();

        ImGui::Begin("Hello, ImGui!");
        ImGui::Text("This is a simple ImGui window.");

        // Wywołanie funkcji generującej wykres
        Editor::RenderPlot(values, "My Plot");

        ImGui::End();

        // Kod do kolorowania składni
        //std::string pythonCode = "def hello_world():\n\tprint('Hello, World!')";
        //Editor::DrawMultilineColoredText(pythonCode);

        /*
        * ------------------------------------------------------------------------------------------------------------------------------------
        * DO TEGO MIEJSCA!!!
        */

        // Zakończ rysowanie ramki ImGui
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Renderuj ImGui
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Wymiana buforów
        glfwSwapBuffers(window);
    }

    // Czyszczenie zasobów
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
