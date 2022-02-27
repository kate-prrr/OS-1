#include <iostream>
#include <windows.h>

using namespace std;

HANDLE CreateFileSt(){
    LPCWSTR  name;
    string select_file;
    cout << endl;
    cout << " [Enter the name and path of the FILE as c:\\Example\\Example.txt]:" << endl;
    cin >> select_file;
    name =  (LPCWSTR) (select_file.c_str());
    HANDLE hfile = CreateFile((LPCSTR) name,  GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hfile != INVALID_HANDLE_VALUE){
        cout << endl;
        cout << " [The file was created successfully]" << endl;
        return CreateFileMapping(hfile, NULL, PAGE_READWRITE, 0, 512, TEXT("Local\\MyFileM")); //объект типа проецируемый файл
         //дескриптор файла, опционально, задает защиту, старшее и младшее слова максимального размера, имя объекта
    }
    else{
        cout << " [Error creating the file]" << endl;
        cout << GetLastError() << endl;
        return NULL;
    }
    
    CloseHandle(hfile);
}

int main()
{
    HANDLE Map;
    LPVOID Map_1;
    Map = CreateFileSt();
    if( Map != NULL){
        cout << " [File Maping Access!]" << endl;
        Map_1 = MapViewOfFile(Map, FILE_MAP_ALL_ACCESS, 0, 0, 0); //отображение объекта на ВАП
        if(Map_1 == 0 ) cout << " [File not projected!]" << endl;
        else{
            cout << " [The file is projected!]" << endl;
            CopyMemory(Map_1, TEXT("Hi, this program is working!"), 28);
            system("pause");
            UnmapViewOfFile(Map_1); //открепление файла от адресного пространства процесса
            cout << " [Data recorded!]" << endl;
               
             
        }
    }
    else{
        cout << " [File Maping Error!]" << endl;
        cout << GetLastError() << endl;
        return 0;
    }
    
    return 0;
}