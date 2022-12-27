#include <iostream>
#include <Windows.h>
#include <ctime>

using namespace std;

void main() {
    time_t currTime;
    currTime = time(&currTime);
    tm localCurrTime;
    localtime_s(&localCurrTime, &currTime);
    cout << localCurrTime.tm_mday << '.' << localCurrTime.tm_mon << '.' << localCurrTime.tm_year + 1900 << ' ';    
    cout << localCurrTime.tm_hour << ':' << localCurrTime.tm_min << ':' << localCurrTime.tm_sec << endl;
}