/*filename:fileexception.h
description:文件异常类的声明*/

#pragma once
#include <string>
using namespace std;
class FileException
{
public:
	string filename;
	string type;
	string mode;

	FileException(string inputFilename, string inputType, string inputMode) {
		filename = inputFilename;
		type = inputType;
		mode = inputMode;
	}
	~FileException() { };
};