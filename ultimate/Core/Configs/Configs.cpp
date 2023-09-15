#include "Configs.hpp"
#include "../SDK/AssemblyCSharp/AssemblyCSharp.hpp"
#include "../SDK/System/System.hpp"
inline bool gggg = false;
void Configs::SaveConfig()
{
	if (!gggg)
	{
		auto stream = SystemIO::File::Open("C:\\test.txt", SystemIO::Open);



	//	LOG("[DEBUG] test - %ls", stream->c_str());
		gggg = true;
	}
}