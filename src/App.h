#pragma once

#define SDL_MAIN_HANDLED
#include "SDL3/SDL.h"

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

#include <string>

class App
{
public:
    App(const char *window_title, int window_width, int window_height, Uint32 window_flags = SDL_WINDOW_RESIZABLE, Uint32 renderer_flags = SDL_RENDERER_ACCELERATED, Uint32 sdl_init_flags = SDL_INIT_VIDEO);
    ~App();

    ImGuiIO &ImguiInit();
    ImGuiIO &ImguiNewFrame();
    void ImguiRender();

    int SetWindowMinimumSize(int min_width, int min_height);
    void SetWindowWidthHeight(int w, int h);

    int GetWindowWidth() { return window_width; }
    int GetWindowHeight() { return window_height; }
    void GetScaleFactors(float &x, float &y, float &factor);

    SDL_Window *GetSDLWindow() { return window; }
    SDL_Renderer *GetSDLRenderer() { return renderer; }

    bool GetIsMouseHidden() { return isMouseHidden; }
    void HideMouseCursor();
    void ShowMouseCursor();

    void DrawString(const std::string& str, const ImVec2 &position, float size, const ImVec4 &color, int discriminator);
    bool IsMouseInsideRect(float mouseX, float mouseY, const SDL_FRect &rect);
    
private:
    SDL_Window *window{};
    SDL_Renderer *renderer{};
    const char *window_title;
    int initial_window_width, initial_window_height;
    int window_width, window_height;
    float scale_factor_x{}, scale_factor_y{}, scale_factor{};
    bool isMouseHidden;
};

App::App(const char *window_title, int window_width, int window_height, Uint32 window_flags, Uint32 renderer_flags, Uint32 sdl_init_flags)
    : window_title(window_title), initial_window_width(window_width), initial_window_height(window_height), window_width(window_width), window_height(window_height), isMouseHidden(false)
{
    if (SDL_Init(sdl_init_flags) != 0)
    {
        SDL_Log("Failed to initialize SDL: %s\n", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow(window_title, initial_window_width, initial_window_height, window_flags);
    if (!window)
    {
        SDL_Log("Failed to create SDL window: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(window, NULL, renderer_flags);
    if (!renderer)
    {
        SDL_Log("Failed to create SDL renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
    SDL_RendererInfo info;
    SDL_GetRendererInfo(renderer, &info);
    SDL_Log("Current SDL_Renderer: %s", info.name);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    SDL_DisplayID display = SDL_GetPrimaryDisplay();
    const SDL_DisplayMode *displayMode = SDL_GetCurrentDisplayMode(display);
    if (displayMode)
    {
        SDL_Log("%s %dx%d", SDL_GetDisplayName(display), displayMode->w, displayMode->h);
        SDL_Rect rect = {0, 0, displayMode->w, displayMode->h};
        SDL_SetRenderViewport(renderer, &rect);
    }
    else
        SDL_SetRenderViewport(renderer, NULL);

    scale_factor_x = static_cast<float>(window_width) / initial_window_width;
    scale_factor_y = static_cast<float>(window_height) / initial_window_height;
    scale_factor = std::min(scale_factor_x, scale_factor_y);
}

App::~App()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

ImGuiIO &App::ImguiInit()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.IniFilename = NULL;
    io.LogFilename = NULL;
    ImGui::StyleColorsClassic();

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    return io;
}

ImGuiIO &App::ImguiNewFrame()
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGuiIO &io = ImGui::GetIO();

    SDL_SetRenderScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    return io;
}

void App::ImguiRender()
{
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());
}

int App::SetWindowMinimumSize(int min_width, int min_height)
{
    return SDL_SetWindowMinimumSize(window, min_width, min_height);
}

void App::SetWindowWidthHeight(int w, int h)
{
    window_width = w;
    window_height = h;
    scale_factor_x = static_cast<float>(window_width) / initial_window_width;
    scale_factor_y = static_cast<float>(window_height) / initial_window_height;
    scale_factor = std::min(scale_factor_x, scale_factor_y);
}

void App::GetScaleFactors(float &x, float &y, float &factor)
{
    x = scale_factor_x;
    y = scale_factor_y;
    factor = scale_factor;
}

void App::HideMouseCursor()
{
    if (!isMouseHidden)
    {
        if (!SDL_HideCursor())
        {
            SDL_Log("%s", SDL_GetError());
            return;
        }
        isMouseHidden = true;
    }
}

void App::ShowMouseCursor()
{
    if (isMouseHidden)
    {
        if (SDL_ShowCursor())
        {
            SDL_Log("%s", SDL_GetError());
            return;
        }
        isMouseHidden = false;
    }
}

void App::DrawString(const std::string& str, const ImVec2 &position, float size, const ImVec4 &color, int discriminator)
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking;

    ImGui::SetNextWindowPos(position);
    ImGui::Begin(std::string("String " + std::to_string(discriminator)).c_str(), nullptr, window_flags);
    ImGui::PushStyleColor(ImGuiCol_Text, color);
    float old_size = ImGui::GetFont()->Scale;
    ImGui::GetFont()->Scale *= size / 100;
    ImGui::PushFont(ImGui::GetFont());
    ImGui::Text(str.c_str());
    ImGui::GetFont()->Scale = old_size;
    ImGui::PopFont();
    ImGui::PopStyleColor();
    ImGui::End();
}

bool App::IsMouseInsideRect(float mouseX, float mouseY, const SDL_FRect &rect)
{
    return (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
            mouseY >= rect.y && mouseY <= rect.y + rect.h);
}