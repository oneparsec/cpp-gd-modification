#include <Windows.h>
#include <gd.h>
#include <MinHook.h>
#include <cocos2d.h>

using namespace gd;
using namespace cocos2d;

void (__thiscall* MenuLayer_onMoreGames)(MenuLayer*, CCObject*);
void __fastcall MenuLayer_onMoreGames_H(MenuLayer* self, void*, CCObject* sender) {
    gd::FLAlertLayer::create(nullptr, "Info", "Ok", nullptr, "MenuLayer_onMoreGames has been called")->show();
}
DWORD WINAPI MainThread(void* hModule)
{
    MH_Initialize();

    
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));

    MH_CreateHook(
        reinterpret_cast<void*>(base + 0x1919C0),
        reinterpret_cast<void*>(&MenuLayer_onMoreGames_H),
        reinterpret_cast<void**>(&MenuLayer_onMoreGames)
    );

    MH_EnableHook(MH_ALL_HOOKS);
    return 0;
}
 
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0x1000, MainThread, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
