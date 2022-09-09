#include "string"
#include "vvlog.h"

int main()
{
	std::string str{"hello world"};
	vv::vvTrace("trace");//not display
	vv::vvDebug("debug");//not display
	vv::vvInfo(str);
	vv::vvWarn("{} {} {} {}","this","is","a",str);
	vv::vvError("{} != {}",1,2);

	//set log output level
	vv::vvSetGlobalLevel(vv::vvLevel::trace);
	vv::vvTrace("display now");
	VDEBUG("display now too");
	VINFO("hello info");
	VWARN(str);
	return 0;
}
