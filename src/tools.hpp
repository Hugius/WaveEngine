#pragma once

#include "cursor_type.hpp"

#include <string>

using std::string;

class Tools final
{
public:
	Tools() = delete;

	static void setCursorType(const CursorType type);

	static const string getRootDirectoryPath();
	static const string chooseWindowsExplorerFile(const string & startingDirectory, const string & fileType);

	static const CursorType getCursorType();

private:
	static inline CursorType _cursorType = CursorType::ARROW;
};