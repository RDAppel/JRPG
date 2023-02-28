#pragma once

#include <string>
#include <Windows.h>

class ExternalExe
{

public:

	static bool Run(const std::wstring exeName, const std::wstring exeDir,
		const std::wstring args = L"")
	{
		SHELLEXECUTEINFO shExecInfo = { 0 };
		shExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		shExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		shExecInfo.hwnd = NULL;
		shExecInfo.lpVerb = L"open";
		shExecInfo.lpFile = exeName.c_str();
		shExecInfo.lpDirectory = exeDir.c_str();
		shExecInfo.lpParameters = args.c_str();
		shExecInfo.nShow = SW_SHOW;
		shExecInfo.hInstApp = NULL;
		ShellExecuteEx(&shExecInfo);

		if (!shExecInfo.hProcess) return false;

		if (WaitForSingleObject(shExecInfo.hProcess, INFINITE) == 0)
		{
			DWORD exitCode = 0;
			GetExitCodeProcess(shExecInfo.hProcess, &exitCode);
			return (exitCode == 0);
		}

		return false;
	}
};