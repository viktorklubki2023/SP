#include <windows.h>
#include <string>
#include <sstream>
#include <iostream>
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

// Function to convert bytes to gigabytes
double BytesToGigabytes(ULONGLONG bytes) {
    return static_cast<double>(bytes) / (1024 * 1024 * 1024);
}

int main() {
    LPCWSTR drive = L"C:\\"; // Drive to check

    ULARGE_INTEGER freeBytesAvailable;
    ULARGE_INTEGER totalNumberOfBytes;
    ULARGE_INTEGER totalNumberOfFreeBytes;

    // Get disk space information
    if (GetDiskFreeSpaceEx(drive, &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
        std::wstringstream ss;

        ss << L"Drive: " << drive << L"\n";
        ss << L"Free space: " << BytesToGigabytes(totalNumberOfFreeBytes.QuadPart) << L" GB\n";

        MessageBoxW(NULL, ss.str().c_str(), L"Disk Space Information", MB_OK | MB_ICONINFORMATION);
    }
    else {
        MessageBoxW(NULL, L"Drive not found", L"Error", MB_OK | MB_ICONERROR);
    }

    return 0;
}
