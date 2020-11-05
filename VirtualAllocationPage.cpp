// ConsoleApplication5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include<Windows.h>
#include<memoryapi.h>
using namespace std;

int main()
{
    
    /*char* str = (char*)"koni";
    //DWORD dwOldProtect;
    VirtualProtect(str, 5, PAGE_READWRITE, NULL);
    str[0] = 'j';
    cout << str;*/
    
    /*char* str = (char*)"koni";
    uint64_t j = (uint64_t)str;
    DWORD rubbish;
    VirtualProtect((void*)j, 5, PAGE_READWRITE, &rubbish);
    str[0] = 'j';
    cout << str;*/
    SYSTEM_INFO sSysInfo;
    GetSystemInfo(&sSysInfo);
    DWORD dwPageSize = sSysInfo.dwPageSize;
    char* str = (char*)"koni";
    int64_t j = (int64_t)str;
    j = 0xfffffffff000 & j;
    DWORD rubbish;
    LPVOID Reservedpage=VirtualAlloc(NULL, dwPageSize, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
    LPTSTR Changeto=(LPTSTR) Reservedpage;
    DWORD i=0;
    Changeto[i] = 'a';
    VirtualProtect((void*)j, 16, PAGE_READWRITE, &rubbish);
    str[0] = 'j';
    cout << str;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
