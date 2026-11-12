#pragma once

#include <string>

class FileSystem
{
public:
	typedef enum { ArkivUserApplicationData, ArkivUserApplicationDataLow, ArkivCommonApplicationData, ArkivUserPrograms, ArkivCommonPrograms, ArkivProgramFiles, Desktop, RoamingAppData, AppData } FolderType;
	static std::wstring getSpecialFolder(FolderType folder, bool create, const char* subDirectory = 0, bool appendArkiv = true);
	static bool IsFileExists(const TCHAR* name);
	static bool IsFolderExists(const TCHAR* name);
};
