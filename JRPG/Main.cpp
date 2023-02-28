
#include "_PCH.h"

int main()
{
	JRPG* pJRPG = new JRPG;
	int errorCode = pJRPG->Run();
	delete pJRPG;
	return errorCode;
}