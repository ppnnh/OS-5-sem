﻿#include <iostream>
#include<Windows.h>

#include <process.h>
using namespace std;
int main()
{
    for (int i = 0; i < 1000; i++) {
        cout << i << " PID:" << _getpid() << endl;;
        Sleep(1000);
    }
}
// cmd
// tasklist /FI "IMAGENAME eq OS03_01.exe"

//power-shell
//get-process OS03_01
