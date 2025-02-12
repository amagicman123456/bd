// Created on 2/11/2025.
#include <windows.h>
#include <WinInet.h>
#include <iostream>
#include <sstream>
//link with -lwininet
std::string send_request(const char* server, const char* page){
    std::string result;
    HINTERNET internet, connect, request;
    if(!(internet = InternetOpen("WinInet Test", INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, 0)) ||
       !(connect = InternetConnect(internet, server, INTERNET_DEFAULT_HTTPS_PORT, 0, 0, INTERNET_SERVICE_HTTP, 0, 1)) ||
       !(request = HttpOpenRequest(connect, "GET", page, 0, 0, 0, INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_SECURE, 1))) {
        InternetCloseHandle(request);
        InternetCloseHandle(connect);
        InternetCloseHandle(internet);
        return "";
    }
    bool s = HttpSendRequest(request, 0, 0, 0, 0);
    char data[10000];
    while(s) {
        DWORD bytes;
        bool read = InternetReadFile(request, data, sizeof(data) - 1, &bytes);
        if (!read || !bytes) break;
        data[bytes] = 0;
        result += data;
    }
    return result;
}
int main(){
    std::string s = send_request("amagicman123456.github.io", "/bd/")
    for (char& i : s) i -= 97;
    std::stringstream ss;
    for (int i = 0, j = 0; i < s.length(); ++i) {
        ss << s[i];
        ss >> j;
        if (j < 255) {

        }
    }
    return 0;
}