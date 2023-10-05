#include "Core/Core.hpp"

void cheat_main()
{
#ifndef DEBUG_MODE
    fix_relocations();
#endif
	Core().Instance()->Init();
}

#ifdef DEBUG_MODE
BOOL DllMain(HINSTANCE instance, DWORD reason, void* reserved)
{
		switch (reason)
		{
			// Attach
		case DLL_PROCESS_ATTACH:
		{
			LI_FN(DisableThreadLibraryCalls)(instance);
			LI_FN(CreateThread).cached()(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(&cheat_main), 0, 0, 0);
			break;
		}
		default:
			break;
		}
		return TRUE;
}
#else
#ifdef _DEBUG
//#define TOKEN 
#else
//#define TOKEN {0x21, 0x11, 0x15, 0xCD, 0x32, 0x64, 0xFA, 0x6C, 0x78, 0x3A, 0x97, 0x9A, 0xCC, 0xFF, 0x32, 0x64, 0x42, 0xBB, 0xDA, 0xB2, 0xDD, 0xAA, 0x24, 0x25, 0xCC, 0xCA, 0xFA, 0xD8, 0x16, 0xC3, 0x57, 0xD2, 0xA2 }
#endif

extern "C" IMAGE_DOS_HEADER __ImageBase;

BOOL __stdcall DllMain(std::uintptr_t mod, std::uint32_t call_reason, std::uintptr_t reserved) {
    static bool thread_inited = false;
    auto EPIC_EXPORT_AVOIDANCE = reinterpret_cast<eac_info*>(_TAG);
    if (call_reason == DLL_PROCESS_ATTACH)
    {
        eac_data.cheat_base = EPIC_EXPORT_AVOIDANCE->cheat_base;
        eac_data.entry = EPIC_EXPORT_AVOIDANCE->entry;

        eac::base = mod;
        eac::entry = (mod + eac_data.entry);

        if (!thread_inited)
        {
            LI_FN(CreateThread)(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(cheat_main), nullptr, 0, nullptr);
            thread_inited = true;
        }

        const auto eac_dll_fn =
            reinterpret_cast<decltype(&DllMain)>(mod + eac_data.entry);

        const auto result = eac_dll_fn(mod, call_reason, reserved);
        return result;
    }

    return TRUE;
}
#endif
