#include "Core/Core.hpp"


void cheat_main()
{
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
	if (call_reason == DLL_PROCESS_ATTACH) {

		static bool thread_inited = false;
		const auto NtHeader = (PIMAGE_NT_HEADERS)(((PUINT8)&__ImageBase) + __ImageBase.e_lfanew);
		const auto EacBase = (PUINT8)mod;
		const auto EOS_Entry = &EacBase[NtHeader->OptionalHeader.AddressOfEntryPoint];

		if (!thread_inited) {
			LI_FN(DisableThreadLibraryCalls)((HINSTANCE)mod);
			LI_FN(CreateThread).cached()(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(&cheat_main), 0, 0, 0);
			thread_inited = true;
		}

		auto EacMain = (decltype(&DllMain))(EOS_Entry);
		return EacMain(mod, call_reason, reserved);

	}

	return TRUE;
}
#endif
