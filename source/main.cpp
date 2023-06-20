#include <cstdlib>
#include <csignal>
#include <atomic>

#include <fmt/core.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <implot.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

const char *getGlfwError() {
    const char *result = nullptr;
    glfwGetError(&result);
    return result;
}

int main(int argc, char **argv) {

    // Boring library initialization code

    if(!glfwInit()) {
        fmt::print(stderr, "Failed to initialize GLFW: {}\n", getGlfwError());
        return EXIT_FAILURE;
    }

    GLFWwindow *window = glfwCreateWindow(1920, 1080, "awian", nullptr, nullptr);
    if(window == nullptr) {
        fmt::print(stderr, "Failed to create window: {}\n", getGlfwError());
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGL()) {
        fmt::print(stderr, "Failed to load OpenGL\n");
        return EXIT_FAILURE;
    }

    ImGui::CreateContext();
    auto &io = ImGui::GetIO();
    // Increase font scale a bit because default ImGui font looks tiny on a 4k display
    // TODO: make this configurableW
    io.FontGlobalScale *= 1.5f;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImPlot::CreateContext();
    ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    /* Handle signals grafecully.
       Note: atomic_flag (unlike atomic_bool) is guaranteed to be lock free
       (atomic_bool implemented using locks could cause a deadlock here)
    */
    static std::atomic_flag interrupted = false;
    signal(SIGINT, [](int){interrupted.test_and_set();});

    while(!glfwWindowShouldClose(window) && !interrupted.test()) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int x,y;
        glfwGetWindowSize(window, &x, &y);
        ImGui::SetNextWindowPos({0,0});
        ImGui::SetNextWindowSize({(float)x,(float)y});

        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);

        if(ImGui::Begin("Text window")) {
            ImGui::Text("Test text");
        }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}