#include <iostream>
#include <Windows.h>

using namespace std;
#define PG (4096)
int pg = 512;

int main() {
	setlocale(LC_ALL, "rus");
	int* m1 = (int*)VirtualAlloc(NULL, pg * PG, MEM_COMMIT, PAGE_READWRITE);
	for (int i = 0; i < pg * PG / 4; i++) {
		m1[i] = i;
	}
	system("pause");

	// Б=C1=193
	// у=F3=243
	// р=F0=240
	// Страница C1 = 193, смещение F3F=3903

	int* m2 = m1 + 4 * 207 * 1024 + 3822;
	cout << *m2 << endl << hex << m2 << endl;
	system("pause");
}
