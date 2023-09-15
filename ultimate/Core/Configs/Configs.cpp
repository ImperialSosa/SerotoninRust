#include "Configs.hpp"
#include "../SDK/AssemblyCSharp/AssemblyCSharp.hpp"
#include "../SDK/System/System.hpp"
inline bool gggg = false;
void Configs::SaveConfig()
{
	if (!gggg)
	{
		auto stream = SystemIO::File::Open("C:\\test.txt", SystemIO::FileMode::Open);

		auto test = SystemIO::File::OpenText("C:\\test.txt")->ReadLine();
		LOG("[DEBUG] test - %p", test);
		gggg = true;
	}
}