#include "tools.hpp"

#include <filesystem>
#include <shlobj_core.h>

using std::filesystem::absolute;

void Tools::setCursorType(const CursorType type)
{
	switch(type)
	{
		case CursorType::ARROW:
		{
			SetCursor(LoadCursor(nullptr, IDC_ARROW));

			break;
		}
		case CursorType::HAND:
		{
			SetCursor(LoadCursor(nullptr, IDC_HAND));

			break;
		}
	}

	_cursorType = type;
}

const string Tools::getRootDirectoryPath()
{
	char buffer[MAX_PATH];

	size_t len = sizeof(buffer);

	GetModuleFileName(nullptr, buffer, static_cast<DWORD>(len));

	string rootPath = absolute(string(buffer)).string();

	reverse(rootPath.begin(), rootPath.end());

	for(int index = 0; index < rootPath.size(); index++)
	{
		if(rootPath.at(index) == '\\')
		{
			rootPath = rootPath.substr(index);

			break;
		}
	}

	reverse(rootPath.begin(), rootPath.end());

	return rootPath;
}

const string Tools::chooseWindowsExplorerFile(const string & startingDirectory, const string & fileType)
{
	OPENFILENAME ofn;
	char pathBuffer[256] = {};
	char titleBuffer[100] = {};

	string filter = fileType;

	filter.push_back('\0');
	filter += "*." + fileType + '\0';

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = pathBuffer;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(pathBuffer);
	ofn.lpstrFilter = filter.c_str();
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = titleBuffer;
	ofn.lpstrFileTitle[0] = '\0';
	ofn.nMaxFileTitle = sizeof(titleBuffer);
	ofn.lpstrInitialDir = startingDirectory.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if(!GetOpenFileName(&ofn))
	{
		return "";
	}

	return ofn.lpstrFile;
}

const CursorType Tools::getCursorType()
{
	return _cursorType;
}