#include <iostream>
#include <imgui.h>
#include <implot.h>
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

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

    // Główna pętla programu
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Rozpoczęcie rysowania w ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Twój kod GUI znajdzie się tutaj
        ImGui::Begin("Hello, ImGui!");
        ImGui::Text("This is a simple ImGui window.");
        ImGui::End();

        // Renderowanie ImGui
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Wyświetlanie rysunku na ekranie
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
