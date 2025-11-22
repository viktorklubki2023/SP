#include "lab3.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    // Set console encoding to display English characters correctly
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
    setlocale(LC_ALL, "English");

    char myString[128];

    printf("Enter a string: ");
    gets_s(myString, sizeof(myString));

    char* result = ProcessText(myString);

    if (result) {
        printf("Result: %s", result);
    }

    return 0;
}
