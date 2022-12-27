#include <Windows.h>
#include <iostream>
#include <cassert>
#include <sstream>

//BOOL CreateProcess
//(
//    LPCTSTR lpApplicationName,                 // имя исполняемого модуля
//    LPTSTR lpCommandLine,                      // Командная строка
//    LPSECURITY_ATTRIBUTES lpProcessAttributes, // Указатель на структуру SECURITY_ATTRIBUTES
//    LPSECURITY_ATTRIBUTES lpThreadAttributes,  // Указатель на структуру SECURITY_ATTRIBUTES
//    BOOL bInheritHandles,                      // Флаг наследования текущего процесса
//    DWORD dwCreationFlags,                     // Флаги способов создания процесса
//    LPVOID lpEnvironment,                      // Указатель на блок среды
//    LPCTSTR lpCurrentDirectory,                // Текущий диск или каталог
//    LPSTARTUPINFO lpStartupInfo,               // Указатель нас структуру STARTUPINFO
//    LPPROCESS_INFORMATION lpProcessInformation // Указатель нас структуру PROCESS_INFORMATION 
//);

void CreateProccersWithPriority(LPCWSTR an, STARTUPINFO si, int priority)
{
    std::cout << "-- HWR\n";
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO)); si.cb = sizeof(STARTUPINFO);
    if (priority == 1)
    {        
        if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | BELOW_NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi))
            std::cout << "-- Process OS05_021 created\n";
        else  std::cout << "-- Process OS05_021 not created\n";
    }
    if (priority == 2)
    {
        if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi))
            std::cout << "-- Process OS05_021 created\n";
        else  std::cout << "-- Process OS05_021 not created\n";
    }
    if (priority == 3)
    {
        if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | HIGH_PRIORITY_CLASS, NULL, NULL, &si, &pi))
            std::cout << "-- Process OS05_021 created\n";
        else  std::cout << "-- Process OS05_021 not created\n";
    }
    if (priority == 4)
    {
        if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | REALTIME_PRIORITY_CLASS, NULL, NULL, &si, &pi))
            std::cout << "-- Process OS05_021 created\n";
        else  std::cout << "-- Process OS05_021 not created\n";
    }
}


int main(int argc, char* argv[])
{
    setlocale(LC_ALL,"russian");
    for (int i = 0; i < argc; i++)
    {
        std::cout << "arg" << i << ": " << argv[i] << "\n";
    }

    HANDLE hp = GetCurrentProcess();
    try
    {
        {
            DWORD pa = NULL, sa = NULL, icpu = -1;
            if (!GetProcessAffinityMask(hp, (PDWORD_PTR)&pa, (PDWORD_PTR)&sa)) throw "GetProcessAffinityMask";
            std::cout << " Process Affinity Mask: " << std::showbase << std::hex << pa << "\n";
            std::cout << " System Affinity Mask: " << std::showbase << std::hex << sa << "\n";
            std::cout << std::dec << std::noshowbase << "\n\n";


            if (argv[1] != NULL)
            {
                unsigned long long mask;
                if (!strcmp(argv[1], "max"))
                {
                    if (!SetProcessAffinityMask(hp, sa)) throw "SetProcessAffinityMask";
                }
                else {
                    int mask = atoi(argv[1]);
                    if (!SetProcessAffinityMask(hp, mask)) throw "SetProcessAffinityMask";
                }
                if (!GetProcessAffinityMask(hp, (PDWORD_PTR)&pa, (PDWORD_PTR)&sa)) throw "GetProcessAffinityMask";
                std::cout << " Process Affinity Mask: " << std::showbase << std::hex << pa << "\n";
                std::cout << " System Affinity Mask: " << std::showbase << std::hex << sa << "\n";
                std::cout << std::dec << std::noshowbase;

                if (argv[2] != NULL)
                {
                    STARTUPINFO si;
                    ZeroMemory(&si, sizeof(STARTUPINFO));
                    si.cb = sizeof(STARTUPINFO);

                    unsigned long long priority;
                    sscanf_s(argv[2], "%d", &priority);
                    CreateProccersWithPriority(L"E:\\5sem\\OS\\labs\\lab5\\os05_02\\Debug\\os05_02x.exe", si, priority);


                    if (argv[3] != NULL)
                    {
                        sscanf_s(argv[3], "%d", &priority);
                        ZeroMemory(&si, sizeof(STARTUPINFO));
                        si.cb = sizeof(STARTUPINFO);
                        CreateProccersWithPriority(L"E:\\5sem\\OS\\labs\\lab5\\os05_02\\Debug\\os05_02x.exe", si, priority);
                    }

                }
            }

        }
    }
    catch (char* msg) { std::cout << "Error " << msg << "\n"; }
    system("pause");
}