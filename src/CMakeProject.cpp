#include <iostream>
#include <imgui.h>
#include <implot.h>
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "Editor.h"

int main() {
    // Inicjalizacja GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Konfiguracja GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Tworzenie okna GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "ImGui GLFW Example", NULL, NULL);
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

    // Inicjalizacja ImGui dla GLFW i OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Główna pętla
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Rozpocznij ramkę ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /*
        * RENDEROWANIE TUTAJ
        * NIC NIE RUSZASZ OPROCZ OD TEGO MIEJSCA
        * ------------------------------------------------------------------------------------------------------------------------------------
        */

        Editor::Render();

        // Kod do kolorowania składni
        std::string pythonCode = "def hello_world():\n\tprint('Hello, World!')";
        Editor::DrawMultilineColoredText(pythonCode); // Tak uzywasz namespace, jak imgui, po prostu biblioteki twojej ktora tworzy edytor

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
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
