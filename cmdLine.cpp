#include "cmdLine.h"

cmdLine::cmdLine()
{
}

cmdLine::~cmdLine()
{
}


// 描述:execmd函数执行命令，并将结果存储到result字符串数组中 
// 参数:cmd表示要执行的命令
// result是执行的结果存储的字符串数组
// 函数执行成功返回TRUE，失败返回FALSE  
std::string cmdLine::runCmd(std::string& strCmd)
{
	/*
	clock_t startTime = clock();
	clock_t execTime;
	CString logData;
	*/
	//安全属性
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;
	std::string strResult;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	strCmd = "cmd /c " + strCmd;//加上"cmd /c"是为了能执行类似dir的命令,执行字符串指定的命令然后终断

	//创建匿名管道，导向DOS输入输出通道
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		return NULL;
	}
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;//数据输出用的文件句柄
	si.hStdOutput = hWrite;//新创建进程的标准输出连在写管道一端
	si.wShowWindow = SW_HIDE;//隐藏窗口
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	//执行cmd命令,并在命名中管道中写入cmd命令返回的串
	if (!CreateProcess(NULL, const_cast <char*>(strCmd.c_str()), NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		return NULL;
	}
	/*
	execTime = clock();
	int t = execTime - startTime;
	logData.Format("执行命令 %s 用时:%d ms", strCmd.c_str(), t);
	mtmlog.LogOut(logData.GetBuffer(0));
	*/
	/*
	if(WaitForSingleObject(pi.hProcess, INFINITE)==WAIT_FAILED)//这里决定是否要等整个命令执行完,如ping等耗时较多的命令.
	{
	return FALSE;
	}
	*/
	CloseHandle(hWrite);//关闭管道句柄

	char buffer[4096] = { 0 };
	DWORD bytesRead;

	while (ReadFile(hRead, buffer, 4096, &bytesRead, NULL))//从匿名管道中读取数据
	{
		strResult += buffer;
		memset(&buffer, 0, 4096);
		Sleep(200);//防止乱码
	}
	/*
	t = clock() - execTime;
	logData.Format("匿名通道读取用时:%d ms", t);
	mtmlog.LogOut(logData.GetBuffer(0));
	*/
	//mtmlog.LogOut(strResult);
	CloseHandle(hRead);
	return strResult;
}