#include <iostream>
#include <windows.h>
#include <iomanip>
#include <ctime>
using namespace std;

#define THREADS_NUMBER 12
HANDLE hThreads[THREADS_NUMBER];

int n = 100000000;
int stepSize = 9307400;
int maxSteps = n / stepSize + 1;
double pi = 0;
volatile long int stepNum = THREADS_NUMBER;



DWORD WINAPI ThreadFunc(LPVOID lpParameter)
{
	double curPi = 0;
	int numberOfCurThread = (int)lpParameter;
	while (true)
	{
		int start = numberOfCurThread * stepSize;
		int end = (numberOfCurThread + 1) * stepSize < n ? (numberOfCurThread + 1) * stepSize : n;
		for (int i = start; i < end; i++)
		{
			long double x = (i + 0.5) / n;
			curPi += 4 / (1 + x * x);
		}
		numberOfCurThread = InterlockedExchangeAdd(&stepNum, 1);
		if (stepNum > maxSteps)
			break;
		SuspendThread(hThreads[(int)lpParameter]);
	}
	pi += curPi;
	return 0;
}



int main()
{
//	cout << endl;
	cout << " [Count of threads]: " << THREADS_NUMBER << endl << endl;

	for (int i = 0; i < THREADS_NUMBER; i++)
		hThreads[i] = CreateThread(0,// атрибуты защиты потока
          0,//размер начального стека
        ThreadFunc, //адрес функции потока
        (void*)i,//аргументы для вызова функции потока
        CREATE_SUSPENDED,//параметр создания потока
        0);//идентификатор потока

	double start = GetTickCount();

	while (stepNum < maxSteps)
		for (int i = 0; i < THREADS_NUMBER; i++)
			ResumeThread(hThreads[i]);


	
	for (int i = 0; i < THREADS_NUMBER; i++)
		ResumeThread(hThreads[i]);
	
	WaitForMultipleObjects(THREADS_NUMBER, hThreads, TRUE, INFINITE);

	double end = GetTickCount();
    cout.precision(10);  //знаки после запятой


    cout << " [Pi]: " << pi / n << endl;
    cout << " [Time]: " << (double)(end-start)/1000 << endl;

	for (int i = 0; i < THREADS_NUMBER; i++)
		CloseHandle(hThreads[i]);
	return 0;
}
