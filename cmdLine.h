/*
**************************************************************************************
**
**	FILENAME			cmdLine.h
**
**	PURPOSE				这是一个C++的cmd命令执行工具类
**
**	CREATION DATE		2016-11-09
**
**	AUTHOR				itas109
**
**  Blog                http://blog.csdn.net/itas109
**
**  Git                 https://github.com/itas109
**
**************************************************************************************
*/
#ifndef CMDLINE_H
#define  CMDLINE_H

#include "afxdialogex.h"
#include <string>

class cmdLine
{
public:
	cmdLine();
	~cmdLine();

	std::string runCmd(std::string& strCmd);

private:
	HANDLE hWrite;
	HANDLE hRead;
};

#endif // !CMDLINE_H
