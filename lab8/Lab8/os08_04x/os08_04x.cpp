#include <iostream>
#include <ctime>
#include <Windows.h>
#include <tlhelp32.h>
#include <stdio.h>

using namespace std;
volatile bool active = true;

DWORD getppid()
{
    HANDLE hSnapshot;
    PROCESSENTRY32 pe32;
    DWORD ppid = 0, pid = GetCurrentProcessId();

    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    __try {
        if (hSnapshot == INVALID_HANDLE_VALUE) __leave;

        ZeroMemory(&pe32, sizeof(pe32));
        pe32.dwSize = sizeof(pe32);
        if (!Process32First(hSnapshot, &pe32)) __leave;

        do {
            if (pe32.th32ProcessID == pid) {
                ppid = pe32.th32ParentProcessID;
                break;
            }
        } while (Process32Next(hSnapshot, &pe32));

    }
    __finally {
        if (hSnapshot != INVALID_HANDLE_VALUE) CloseHandle(hSnapshot);
    }
    return ppid;
}

DWORD WINAPI stopCycle(HANDLE htimer) {
    WaitForSingleObject(htimer, INFINITE);
    active = false;
    return 0;
}

bool isSimple(int n) {
    int i, sq;
    if (n % 2 == 0) { return false; }
    sq = (int)sqrt(n);
    for (i = 3; i <= sq; i++) {
        if ((n % i) == 0) { return false; }
    }
    return true;
}

int main(int argc, char* argv[])
{
    int firsttime = clock();

    HANDLE htimer = NULL;
    int parm = 1;
    int val = 1;

    for (int i = 0; i < argc; i++) {
        cout << i << " = " << argv[i] << endl;
    }

    if (argc > 1) parm = atoi(argv[1]);
    cout << "Child Process " << parm << " start" << endl;

    if (parm == 1) {
        htimer = OpenWaitableTimer(TIMER_ALL_ACCESS, FALSE, L"atimer1");
    }
    else {
        htimer = OpenWaitableTimer(TIMER_ALL_ACCESS, FALSE, L"atimer2");
    }

    HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)stopCycle, htimer, NULL, NULL);

    while (active) {
        if (isSimple(val)) {
            cout << "Simple - " << val << endl;
        }
        val++;
    }

    WaitForSingleObject(hChild, INFINITE);

    cout << "ppid: " << getppid() << endl;
    cout << "time:" << clock() - firsttime << endl;
    system("pause");
    return 0;
}