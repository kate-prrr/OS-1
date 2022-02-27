#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    HANDLE Map;
    LPVOID Map_1;
    Map =  OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE, false, TEXT("Local\\MyFileM"));
    //режим доступа, флажок наследования, имя объекта
    if( Map != NULL){
        cout << " [File Maping Access!]" << endl;
        Map_1 = MapViewOfFile(Map, FILE_MAP_ALL_ACCESS, 0, 0, 0); //функция проецирвоания области
        //дескриптор проецируемого файла, режим доступа, старшее и младшее DWORD смещения, отображение целиком 
        if(Map_1 == 0 ) cout << " [File not projected!]" << endl;
        else{
            cout << " [The file is projected!]" << endl;
            cout << (char*)(Map_1) << endl;
            UnmapViewOfFile(Map_1); // отмена проецирования области 
        }
    }
    else{
        cout << " [File Maping Error!]" << endl;
        cout << GetLastError() << endl;
        return 0;
    }
    
    return 0;
}
