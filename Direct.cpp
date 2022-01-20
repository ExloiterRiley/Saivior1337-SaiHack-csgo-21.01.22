#include "Direct.h"

directX * d3d;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static bool screensize = false;


LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            d3d->ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

unsigned long __stdcall directX::CreateDirectWindow(void*)
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T(XOR("SaiHack Menu")), NULL }; 
    ::RegisterClassEx(&wc); 
    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T(XOR("SaiHack Menu")), WS_MINIMIZEBOX, 100, 100, 830, 450, NULL, NULL, wc.hInstance, NULL); 
    if (!d3d->CreateDeviceD3D(hwnd))
    {
        d3d->CleanupDeviceD3D(); 
        ::UnregisterClass(wc.lpszClassName, wc.hInstance); 
        return 1; 
    }
    ::ShowWindow(hwnd, SW_SHOWDEFAULT); 
    ::UpdateWindow(hwnd); 

    IMGUI_CHECKVERSION(); 
    ImGui::CreateContext(); 
    ImGuiIO& io = ImGui::GetIO();  (void)io; 
    ImGui::StyleColorsDark(); 
    ImGui_ImplWin32_Init(hwnd); 
    ImGui_ImplDX9_Init(g_pd3dDevice); 


    bool show_demo_window = true; 
    bool show_another_window = false; 
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f); 
    static const char* glowStyle[]{ "Outline", "Legit", "Legit Outline" };
    static const char* glowFriendStyle[]{ "Outline", "Legit", "Legit Outline" };
    static const char* Sounds[]{ "Stapler", "Bameware", "Fatality", "Pop", "Punch", "Rifk7", "Skeet"};
    static const char* Bones[]{ "Head", "Neck", "Body" };
    static const char* Models[]{ "M9", "Karambit", "Flip", "Flip Ghost", "Gut" };
    bool done = false; 
    while (!done)
    {

        MSG msg; 
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg); 
            ::DispatchMessage(&msg); 
            if (msg.message == WM_QUIT)
                done = true; 
        }
        if (done)
            break; 



        ImGui_ImplDX9_NewFrame(); 
        ImGui_ImplWin32_NewFrame(); 
        ImGui::NewFrame(); 
        if (!screensize)
        {
            ImGui::SetNextWindowSize({ 800, 400 });
            screensize = !screensize;
        }
        ImGui::SetNextWindowPos({ 1, 1 });


        ImGui::Begin(XOR("SaiHack | By Saivior1337"), NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize); 

        if (ImGui::Button(XOR("Visuals"), ImVec2(190, 20.f))) { CFG.menuTabs = 1; }
        ImGui::SameLine();
        if (ImGui::Button(XOR("Aimbot"), ImVec2(190, 20.f))) { CFG.menuTabs = 2; }
        ImGui::SameLine();
        if (ImGui::Button(XOR("Misc"), ImVec2(190, 20.f))) { CFG.menuTabs = 3; }
        ImGui::SameLine();
        if (ImGui::Button(XOR("Convars"), ImVec2(190, 20.f))) { CFG.menuTabs = 4; }





        switch (CFG.menuTabs)
        {
        case 1:
            ImGui::NewLine();
            ImGui::Checkbox(XOR("Radar"), &CFG.radar);
            ImGui::SameLine();
            ImGui::Checkbox(XOR("Glow"), &CFG.glow);
            ImGui::SameLine();
            ImGui::Checkbox(XOR("Chams"), &CFG.clrRender);
            if (CFG.clrRender)
            {
                ImGui::NewLine();
                ImGui::ColorEdit3(XOR("Chams Color"), CFG.clrRenderColor, ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoInputs);
                ImGui::SameLine();
                ImGui::ColorEdit3(XOR("Chams Friend Color"), CFG.clrRenderFriendColor, ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoInputs);
            }
            if (CFG.glow)
            {
                ImGui::NewLine();
                ImGui::ColorEdit4(XOR("Glow Color"), CFG.glowColor, ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoInputs);
                ImGui::SameLine();
                ImGui::Combo(XOR("Glow Style"), &CFG.selectedGlowStyle, glowStyle, IM_ARRAYSIZE(glowStyle));
                ImGui::NewLine();
                ImGui::Checkbox(XOR("Glow Friends"), &CFG.glowFriends);

                if (CFG.glowFriends)
                {
                    ImGui::NewLine();
                    ImGui::ColorEdit4(XOR("Friend Color"), CFG.glowFriendColor, ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoInputs);
                    ImGui::SameLine();
                    ImGui::Combo(XOR("Friend Style"), &CFG.selectedGlowFriendStyle, glowFriendStyle, IM_ARRAYSIZE(glowFriendStyle));
                    ImGui::NewLine();
                }
            }
            break;
        case 2:
            ImGui::NewLine();
            ImGui::Checkbox(XOR("Aim"), &CFG.AimBotB);
            ImGui::SameLine();
            ImGui::Checkbox(XOR("Trigger"), &CFG.triggerBot);
            if (CFG.AimBotB)
            {
                ImGui::NewLine();
                ImGui::SliderFloat(XOR("FOV"), &CFG.aimFov, 0.f, 100.f, XOR("%3.f"));
                ImGui::NewLine();
                ImGui::SliderInt(XOR("Smooth"), &CFG.aimSmooth, 1, 20, XOR("%d"));
                ImGui::NewLine();
                ImGui::Combo(XOR("Bone"), &CFG.selectedBone, Bones, IM_ARRAYSIZE(Bones));
                ImGui::NewLine();
                ImGui::Checkbox(XOR("Visible check"), &CFG.aimVisibleCheck);
            }
            break;
        case 3:
            ImGui::NewLine();
            ImGui::Checkbox(XOR("Hit Sound"), &CFG.hitSound);
            ImGui::SameLine();
            ImGui::Checkbox(XOR("Bunnyhop"), &CFG.bunnyHop);
            ImGui::NewLine();
            ImGui::Checkbox(XOR("Models"), &CFG.models);
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), XOR("FPS Drops!"));
            if (CFG.models)
            {
                ImGui::NewLine();
                ImGui::Combo(XOR("Knife"), &CFG.selectedModels, Models, IM_ARRAYSIZE(Models));

            }
            
            if (CFG.hitSound)
            {
                ImGui::NewLine();
                ImGui::Combo(XOR("Sound"), &CFG.selectedSound, Sounds, IM_ARRAYSIZE(Sounds));
            }
            ImGui::NewLine();
            if (ImGui::Button(XOR("Save Config")))
                iCFG->SaveConfig();

            ImGui::SameLine();

            if (ImGui::Button(XOR("Load Config")))
                iCFG->LoadConfig();
            break;
        case 4:
            ImGui::NewLine();
            ImGui::TextColored(ImVec4(1.f, 1.f, 0.f, 1.f), XOR("Currently under construction :("));
            break;
        }


        ImGui::End(); 

        ImGui::EndFrame(); 
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE); 
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE); 
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE); 
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * clear_color.w * 255.0f), (int)(clear_color.y * clear_color.w * 255.0f), (int)(clear_color.z * clear_color.w * 255.0f), (int)(clear_color.w * 255.0f)); 
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0); 
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render(); 
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData()); 
            g_pd3dDevice->EndScene(); 
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL); 


        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            d3d->ResetDevice(); 
        std::this_thread::sleep_for(1ms);
    }

    ImGui_ImplDX9_Shutdown(); 
    ImGui_ImplWin32_Shutdown(); 
    ImGui::DestroyContext(); 

    d3d->CleanupDeviceD3D(); 
    ::DestroyWindow(hwnd); 
    ::UnregisterClass(wc.lpszClassName, wc.hInstance); 

    return 0; 
}


bool directX::CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false; 

    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp)); 
    g_d3dpp.Windowed = TRUE; 
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; 
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; 
    g_d3dpp.EnableAutoDepthStencil = TRUE; 
    g_d3dpp.BackBufferWidth = 830; 
    g_d3dpp.BackBufferHeight = 450; 
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16; 
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; 
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false; 

    return true; 
}

void directX::CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release();  g_pd3dDevice = NULL;  }
    if (g_pD3D) { g_pD3D->Release();  g_pD3D = NULL;  }
}

void directX::ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects(); 
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp); 
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0); 
    ImGui_ImplDX9_CreateDeviceObjects(); 
}