#include <stdio.h>
#include <string.h>
#include <iostream>
#include <windows.h>

typedef char* (*ProcessText)(const char*);

int main() {
    // Set console encoding for English text
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
    setlocale(LC_ALL, "English");

    // Load the DLL
    HMODULE hLib = LoadLibrary(TEXT("Lab3DLL.dll"));
    if (hLib == NULL)
    {
        printf("Failed to load the DLL!\n");
        return 1;
    }

    // Get the address of the ProcessText function
    ProcessText processText = (ProcessText)GetProcAddress(hLib, "ProcessText");
    if (!processText) {
        printf("Could not find the ProcessText function in the DLL!\n");
        FreeLibrary(hLib);
        return 1;
    }

    char myString[128];
    printf("Enter a string: ");
    gets_s(myString, (sizeof(myString) - 1));

    // Call the function from the DLL
    char* result = processText(myString);

    if (result) {
        printf("Result: %s", result);
    }

    // Free the DLL
    FreeLibrary(hLib);
    return 0;
}
