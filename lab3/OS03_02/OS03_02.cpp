#include <iostream>
#include<Windows.h>
#include <process.h>
using namespace std;
int main()
{
    
    //имя исполняемого модуля
    //указатель на постоянную строку
    LPCWSTR chp1 = L"E:\\5sem\\OS\\Лабораторные_работы\\lab3\\OS03_02_1\\Debug\\OS03_02_1.exe"; 
    LPCWSTR chp2 = L"E:\\5sem\\OS\\Лабораторные_работы\\lab3\\OS03_02_2\\Debug\\OS03_02_2.exe";
    // определения свойств главного окна,
    // если новое окно создаётся для нового процесса
    // информация предустановки
    STARTUPINFO w1;
    STARTUPINFO w2;
    //информация о недавно созданном 
    //процессе и его первичном потоке
    PROCESS_INFORMATION pi1;
    PROCESS_INFORMATION pi2;
    //заполняет блок памяти нулями.
    //1-указатель на блок памяти, 2-размер блока памяти
    ZeroMemory(&w1, sizeof(STARTUPINFO)); w1.cb = sizeof(STARTUPINFO);
    ZeroMemory(&w2, sizeof(STARTUPINFO)); w2.cb = sizeof(STARTUPINFO);

    if (CreateProcess(chp1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &w1, &pi1))
        cout << "-- Process OS03_02_1 created" << endl;
    else {
        cout << "-- Process OS03_02_1 not created" << endl;
    }

    if (CreateProcess(chp2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &w2, &pi2))
        cout << "-- Process OS03_02_2 created" << endl;
    else {
        cout << "-- Process OS03_02_2 not created" << endl;
    }

    for (int i = 0; i < 100; i++) {
        cout << i << "  OS03_02 " << " PID:" << _getpid() << endl;;
        Sleep(1000);
    }  
      
    
    
    
    
    
    WaitForSingleObject(//ждать пока дочерний процесс не выйдет из работы
        pi1.hProcess, // идентификатор объекта
        INFINITE      // время ожидания в милисекундах
    );
    WaitForSingleObject(pi2.hProcess, INFINITE); //ожидание завершения д процесса
    CloseHandle(pi1.hProcess); // закрытие дискриптора д процесса и потока 
    CloseHandle(pi2.hProcess);
}