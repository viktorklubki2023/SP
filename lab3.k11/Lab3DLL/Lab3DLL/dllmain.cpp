#include "pch.h"
#include <string>
#include <sstream>
#include <vector>


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
extern "C" __declspec(dllexport) char* ProcessText(const char* input) {
    std::string str(input);
    std::istringstream iss(str);
    std::vector<std::string> words;
    std::string word;

    while (iss >> word) {
        words.push_back(word);
    }

    std::string result;
    for (size_t i = 0; i < words.size(); i++) {
        if ((i + 1) % 2 == 0) {
            if (!result.empty()) {
                result += " ";
            }
            result += words[i];
        }
    }

    char* output = new char[result.length() + 1];
    strcpy_s(output, result.length() + 1, result.c_str());
    return output;
}