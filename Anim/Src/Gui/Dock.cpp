#include "Gui/Dock.h"
#include "Core/Application.h"
#include "Renderer/Renderer.h"
#include "Core/AssetManager.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


std::vector<std::string> userTextBuffer;

using namespace Anim;
//static Renderer* s_renderer = &Renderer::init(1920, 1080, " ", glm::vec3(0,0,0), glm::vec3(0,0,0));

Dock::Dock(){}

Dock::~Dock()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Dock::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;

    ImGui_ImplGlfw_InitForOpenGL(Renderer::Instance().GetWindow().GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 430");
    //LOG::Info("Initialized ImGui OpenGL Context.");

    /* "Purple-y theme" */
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = ImVec4(0.99f, 0.99f, 0.99f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.12f, 0.12f, 0.12f, 0.96f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.10f, 0.10f, 0.10f, 0.80f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.20f, 0.20f, 0.20f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.45f, 0.45f, 0.45f, 0.50f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.28f, 0.28f, 0.28f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.39f, 0.39f, 0.39f, 0.51f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.39f, 0.39f, 0.39f, 0.51f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.88f, 0.88f, 0.88f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.54f, 0.54f, 0.54f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.74f, 0.74f, 0.74f, 0.40f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.73f, 0.73f, 0.73f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.73f, 0.73f, 0.73f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.37f, 0.37f, 0.37f, 0.93f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.31f, 0.27f, 0.55f, 0.92f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.31f, 0.27f, 0.55f, 0.92f);
    colors[ImGuiCol_Separator]              = ImVec4(0.65f, 0.65f, 0.65f, 0.50f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.65f, 0.65f, 0.65f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.65f, 0.65f, 0.65f, 0.94f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.12f, 0.12f, 0.12f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.12f, 0.12f, 0.12f, 0.39f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.12f, 0.12f, 0.12f, 0.43f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.17f, 0.17f, 0.17f, 0.86f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.30f, 0.21f, 0.60f, 0.80f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.30f, 0.22f, 0.60f, 0.80f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(0.60f, 0.60f, 0.60f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.67f, 0.67f, 0.67f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    /* --- style elements --- */
    ImGui::GetStyle().WindowRounding = 0.0f;
    ImGui::GetStyle().WindowBorderSize = 0.0f;
    ImGui::GetStyle().ScrollbarSize = 14.0f;
    ImGui::GetStyle().ItemSpacing = ImVec2(8.0f, 7.0f);
    ImGui::GetStyle().FramePadding = ImVec2(8.0f, 3.0f);
    ImGui::GetStyle().FrameRounding = 6.0f; 
    ImGui::GetStyle().ChildRounding = 6.0f;
    ImGui::GetStyle().PopupRounding = 7.0f;
    ImGui::GetStyle().PopupBorderSize = 0.0f;

}



void Dock::Update(Frame& frame, float dt)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ShowSidePanel(frame, dt);
    ShowInfoWindow();

    //ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Dock::ShowSidePanel(Frame& frame, float dt)
{
    bool f_open;
    ImGuiWindowFlags panel_flags = 0;
    panel_flags |= ImGuiWindowFlags_NoTitleBar;
    panel_flags |= ImGuiWindowFlags_NoMove;

    ImGui::Begin("SidePanel", &f_open, panel_flags);    

    ImGui::Text((const char*)glGetString(GL_VERSION));
    ImGui::Text("Frame Time: %.2fs", dt);
    ImGui::Text(" ");
    
    // if(ImGui::CollapsingHeader("Scene"))
    // {
    //     ShowFrameSubPanel(frame);
    // }

    // if(ImGui::CollapsingHeader("Plots"))
    // {
    //     ShowPlotSubPanel();
    // }

    // if(ImGui::CollapsingHeader("Shaders"))
    // {

    // }

    ImGui::End();
}

void Dock::ShowFrameSubPanel(Frame& Frame)
{

}

void Dock::ShowShaderSubPanel()
{
    ImGuiWindowFlags winFlags = 0;
    winFlags |= ImGuiWindowFlags_HorizontalScrollbar;// (false ? ImGuiWindowFlags_NoScrollWithMouse : 0);
    ImGui::BeginChild("Loaded Shaders", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.98f, 200), true, winFlags);
    
    // std::map<unsigned int, SPtr<Shader>>& shaderMap = *AssetManager::Get().GetShaderMap();
    // for(auto itr = shaderMap.begin(); itr != shaderMap.end(); ++itr)   
    // {
    //     ImGui::TextColored(ImVec4(0.28f, 0.78f, 0.83f, 1.0f), "Shader:%s", itr->second->);

    // }
    ImGui::EndChild();
}

void Dock::ShowPlotSubPanel()
{

}

void Dock::DrawUserText(const std::string& msg)
{
    userTextBuffer.push_back(msg);
}

void Dock::ShowInfoWindow()
{
    if(userTextBuffer.size() > 0)
    {
        bool f_open;
        ImGuiWindowFlags win_flags = 0;
        //win_flags |= ImGuiWindowFlags_NoTitleBar;
        // win_flags |= ImGuiWindowFlags_NoMove;
        // win_flags |= ImGuiWindowFlags_NoResize;
        ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiCond_Always);
        ImGui::Begin("UserInfo", &f_open, win_flags);
        for(unsigned int i = 0; i < userTextBuffer.size(); i++)
        {
            ImGui::Text(userTextBuffer[i].c_str());
        }
        userTextBuffer.clear();

        ImGui::End();
        Log::Info("logging stuff");
        userTextBuffer.clear();

    }
}
