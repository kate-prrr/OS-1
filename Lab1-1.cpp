#include <iostream>
#include <windows.h>

using namespace std;

void Menu() {
    cout << endl;
    cout << " [Managing disks, directories, and files]" << endl;
    cout << endl;
    cout << " 1.Disk List" << endl;
    cout << " 2.Information about the disk and the size of free space" << endl;
    cout << " 3.Creating and deleting specified directories" << endl;
    cout << " 4.Creation file in the specified directory" << endl;
    cout << " 5.Copying and moving files between directories" << endl;
    cout << " 6.File attribute analysis and modification" << endl;
    cout << endl;
    cout << " [Enter the number of the function you need]: " << endl;
}

void DiskList(){
    int element;
    int n;
    cout << " [Available disks] :" << endl;
    cout << endl;
    element = GetLogicalDrives(); //битовое значение для определения наличия дисков
    for (int x = 0; x < 26; x++)
    {
        n = ((element >> x) & 1);
        if (n) 
        {
            cout << " [" << (char)(65 + x) << ":\\]" << endl;                                                        //   ****
        }
    }    
}

void CreateAndRemoveDirectory() {
    int choise;
    string select_disk;
    LPCWSTR  name;
    cout << " 1.Create Directory" << endl;
    cout << " 2.Remove Directory" << endl;
    cout << " [Enter the number of the function you need]: " << endl;  
    cin >> choise;
    switch(choise){
        case 1:
            cout << " [Enter the name and path of the directory as c:\\Example\\New folder]:" << endl;
            cin >> select_disk;
            name =  (LPCWSTR) (select_disk.c_str());                                                                //   ****
            if (CreateDirectory((LPCSTR) name,NULL))
                cout << " [The directory was successfully created!]" << endl;
            else
                cout << " [Error when creating a directory!]" << endl;
            break;
        case 2:
            cout << " [Enter the name and path of the directory as c:\\Example\\New folder]:" << endl;
            cin >> select_disk;
            name =  (LPCWSTR) (select_disk.c_str());
            if (RemoveDirectory((LPCSTR) name))
                cout << " [The directory was successfully removed!]" << endl;
            else
                cout << " [Error when removing a directory!]" << endl;
            break;
        default:
            break;
    }
}

void CreateFile() {
    LPCWSTR  name;
    string select_file;
     cout << endl;
    cout << " [Enter the name and path of the FILE as c:\\Example\\Example.txt]:" << endl;
    cin >> select_file;
    name =  (LPCWSTR) (select_file.c_str());
    HANDLE hfile = CreateFile((LPCSTR) name,  GENERIC_WRITE | GENERIC_READ,NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hfile != INVALID_HANDLE_VALUE)
        cout << " [The text file was successfully created!]" << endl;
    else
        cout << " [Error when creating a text file!]" << endl;
    CloseHandle(hfile);
}

void CopyFileAndMoveFile(){
    int choise;
    LPCWSTR  name;
    LPCWSTR  name1;
    string select_file;
    string select_file1;
    WINBOOL hfile;
    BOOL gfile;


    cout << " 1.Copy" << endl;
    cout << " 2.Move" << endl;
    cout << " 3.Move File Ex" << endl;
    cout << " [Enter the number of the function you need]:" << endl;
    cin >> choise;
    switch(choise){
        case 1:
            cout << " [Enter the name and path of the file to copy as c:\\Example\\Example.txt]:" << endl;
            cin >> select_file;
            cout << " [Select the copy path as d:\\Example\\Example.txt]" << endl;
            cin >> select_file1;
            name =  (LPCWSTR) (select_file.c_str());
            name1 =  (LPCWSTR) (select_file1.c_str());
            hfile = CopyFile((LPCSTR) name,(LPCSTR) name1, 1);
            if(hfile  == 0) cout << " [An error occurred while copying the file]" << endl;
            else cout << " [The file has been copied successfully]" << endl;
            break;
        case 2:
            cout << " [Enter the name and path of the file to move as c:\\Example\\Example.txt]:" << endl;
            cin >> select_file;
            cout << " [Select the move path as d:\\Example\\Example.txt]" << endl;
            cin >> select_file1;
            name =  (LPCWSTR) (select_file.c_str());
            name1 =  (LPCWSTR) (select_file1.c_str());
            gfile = MoveFile((LPCTSTR) name,(LPCTSTR) name1);
            if(gfile == 0 ) cout << " [An error occurred while moved the file]" << endl;
            else cout << " [The file has been moved successfully]" << endl;
            break;
        case 3:
            cout << " [Enter the name and path of the file to move as c:\\Example\\Example.txt]:" << endl;//Добавляются дополнительные флаги+ перезапись файла с одинаковым именем
            cin >> select_file;
            cout << " [Select the move path as d:\\Example\\Example.txt]" << endl;
            cin >> select_file1;
            name =  (LPCWSTR) (select_file.c_str());
            name1 =  (LPCWSTR) (select_file1.c_str());
            gfile = MoveFileEx((LPCTSTR) name,(LPCTSTR) name1, MOVEFILE_COPY_ALLOWED | MOVEFILE_FAIL_IF_NOT_TRACKABLE | MOVEFILE_REPLACE_EXISTING);
            if(gfile == 0 ) cout << " [An error occurred while moved the file]" << endl;
            else cout << " [The file has been moved successfully]" << endl;
            break;
        default:
            break;
    }
    
}

void InfoDisk(){

    string select_disk;
    wstring w_string;
    LPCWSTR  name;
    UINT x;
    
    BOOL GetDiskFreeSpaceFlag;  //проверка правильности вызванной функции
    BOOL GetVolumeInformationFlag;
    char lpVolumeNameBuffer[100];        // название диска    
    DWORD nVolumeNameSize = 100;            // длина буфера названия диска   
    unsigned long lpVolumeSerialNumber;     // сериальный номер диска        
    LPDWORD lpMaximumComponentLength = NULL; // максимальная длина файла      
    LPDWORD lpFileSystemFlags = NULL;        // опции файловой системы        
    char lpFileSystemNameBuffer[100];    // имя файловой системы           
    DWORD nFileSystemNameSize = 100;         // длина буфера имени файл. сист. 

    u_int64 FreeBytesAvailable;    // доступно для использования(байт)
    u_int64 TotalNumberOfBytes;    // максимальный объём( в байтах )  
    u_int64 TotalNumberOfFreeBytes; // свободно на диске( в байтах )    
    
    cout << " [Enter the disk name as c:\\]:" << endl;
    cin >> select_disk;
    name =  (LPCWSTR) (select_disk.c_str());
    x = GetDriveType((LPCSTR) (name));
    cout << endl;
    cout <<" [Disk type]:"<< endl;
    if( x == 0 ) cout << " UNKNOWN" << endl; //неизвестный тип
	if( x == 1 ) cout << " DRIVE NO ROOT DIR" << endl;//неправильный путь
	if( x == 2 ) cout << " REMOVABLE" << endl;//съемный диск
	if( x == 3 ) cout << " FIXED" << endl;//фиксированный диск
	if( x == 4 ) cout << " REMOTE" << endl;//удаленный диск
	if( x == 5 ) cout << " CDROM" << endl;//CDROM диск
	if( x == 6 ) cout << " RAMDISK" << endl;//RAM диск
    
    GetVolumeInformationFlag = GetVolumeInformationA((LPCSTR) (name),lpVolumeNameBuffer,nVolumeNameSize,&lpVolumeSerialNumber,lpMaximumComponentLength,
    lpFileSystemFlags,lpFileSystemNameBuffer,nFileSystemNameSize); // Буферы для имени диска, серийного номера файловой системы
    
    if(GetVolumeInformationFlag != 0) 
    {
        cout << " [Volume Name is]: " << lpVolumeNameBuffer << endl;
        cout << " [Volume Serial Number is]: " << lpVolumeSerialNumber << endl;
        cout << " [File System is]: " << lpFileSystemNameBuffer << endl;
    }
    else cout << " Not Present (GetVolumeInformation)" << endl;
    
    GetDiskFreeSpaceFlag = GetDiskFreeSpaceEx(  //позволяет получать информацию о доступном свободном пространстве для текущего пользователя
    (LPCSTR) (name), // имя директории
    (PULARGE_INTEGER)&FreeBytesAvailable,     // доступно для использования
    (PULARGE_INTEGER)&TotalNumberOfBytes,     // максимальный объем
    (PULARGE_INTEGER)&TotalNumberOfFreeBytes  // свободно на диске
    );
    
    if(GetDiskFreeSpaceFlag != 0) 
    {
         cout << " [Total Number Of Bytes Available  = " << FreeBytesAvailable
         << "( " << ((long double)((FreeBytesAvailable)))/1024/1024/1024
         << " Gb )]" << endl;
        cout << " [Total Number Of Free Bytes = " << TotalNumberOfFreeBytes 
         << "( " <<  ((long double)((TotalNumberOfFreeBytes)))/1024/1024/1024
         << " Gb )]" << endl;
        cout << " [Total Number Of Bytes = " << TotalNumberOfBytes 
         << "( " << ((long double)((TotalNumberOfBytes)))/1024/1024/1024
         << " Gb )]" << endl;
    }
    else cout << " Not Present (GetDiskFreeSpace)" << endl;
}


void SetNewFileTime(HANDLE hFile){
    SYSTEMTIME time_1;
    FILETIME time;
    int Year;
    int Month;
    int Day;
    int Hour;
    int Minutes;
    int Seconds;
    
    
    cout << " [Input Year]:" << endl;
    cin >> Year; 
    cout << " [Input Month]:" << endl;
    cin >> Month;
    cout <<  " [Input Day]:" << endl;
    cin >> Day;
    cout << " [Input Hour]:" << endl;
    cin >> Hour;
    cout << " [Input Minutes]:" << endl;
    cin >> Minutes;
    cout << " [Input Seconds]:" << endl;
    cin >> Seconds;
    time_1.wYear = Year;
    time_1.wMonth = Month;
    time_1.wDay = Day;
    time_1.wHour = Hour;
    time_1.wMinute = Minutes;
    time_1.wSecond = Seconds;
    if(SystemTimeToFileTime(&time_1, &time)){
        SetFileTime(hFile, &time, &time, &time);
    }
    else cout << " [Error in changing data]" << endl;
}

void InfoAtributs(){
    string select_file;
    wstring w_string;
    LPCWSTR  name;
    DWORD atributs;
    int choise;
    int input;
    int n;
    HANDLE hFile;
    BY_HANDLE_FILE_INFORMATION fhi;
    BOOL fResult;
    SYSTEMTIME stUTC,stLocal; 
    FILETIME lpCreationTime;
    FILETIME lpLastAccessTime;
    FILETIME lpLastWriteTime;
    cout <<  endl;
    cout << " 1.Info Atributes File" << endl;
    cout << " 2.Change file Atributes" << endl;
    cout << " 3.File Information" << endl;
    cout <<  endl;
     cout << " [Enter the number of the function you need]: " << endl; 
    
    cin >> choise;
    switch(choise){
        case 1:
            cout << " [Enter the file name as c:\\Example\\Example.txt]:" << endl;
            cin >> select_file;
            name =  (LPCWSTR) (select_file.c_str());
            atributs = GetFileAttributes((LPCSTR) name);
            cout <<  endl;
            cout << " [File type]:" << endl;
            if(atributs & FILE_ATTRIBUTE_ARCHIVE ) cout << " ARCHIVE" << endl; // Архивный
            if(atributs & FILE_ATTRIBUTE_COMPRESSED) cout << " COMPRESSED" << endl; // Сжатый
            if(atributs & FILE_ATTRIBUTE_DIRECTORY) cout <<" NAME DIRECTORY" << endl; // Имя папки
            if(atributs & FILE_ATTRIBUTE_HIDDEN) cout <<" HIDEN FILES" << endl; // Скрытый файл или директория
            if(atributs & FILE_ATTRIBUTE_NORMAL) cout <<" FILE WITH NO ATRIBUTES" << endl; // Файл не имеет атрибутов
            if(atributs & FILE_ATTRIBUTE_READONLY) cout <<" FILE READ" << endl; // Файл только для чтения
            if(atributs & FILE_ATTRIBUTE_SYSTEM) cout <<" SYSYTEM FILE" << endl; // Системный файл
            break;
        case 2:
            cout << " [Enter the file name as c:\\Example\\Example.txt]:" << endl;
            cin >> select_file;
            name =  (LPCWSTR) (select_file.c_str());
            
            cout<< endl;
            cout << " 1.ARCHIVE" << endl;
            cout << " 2.COMPRESSED" << endl;
            cout << " 3.NAME DIRECTORY" << endl;
            cout << " 4.HIDEN FILES" << endl;
            cout << " 5.FILE WITH NO ATRIBUTES" << endl;
            cout << " 6.FILE READ" << endl;
            cout << " 7.SYSYTEM FILE" << endl;
            cout<< endl;
            cout << " [Enter the attribute type for the file]: " << endl; 
            cin >> input;
            switch(input){
                    case 1:
                        SetFileAttributes( (LPCSTR) name, FILE_ATTRIBUTE_ARCHIVE);
                        atributs = GetFileAttributes((LPCSTR) name);
                        if( atributs & FILE_ATTRIBUTE_ARCHIVE) cout << "[The change was successful]" << endl;
                        else cout << " [Error in changing the attribute]" << endl;
                        break;
                    case 2:
                        SetFileAttributes( (LPCSTR) name, FILE_ATTRIBUTE_COMPRESSED);
                        atributs = GetFileAttributes((LPCSTR) name);
                        if( atributs & FILE_ATTRIBUTE_COMPRESSED) cout << "[The change was successful]" << endl;
                        else cout << " [Error in changing the attribute]" << endl;
                        break;
                    case 3:
                        SetFileAttributes( (LPCSTR) name, FILE_ATTRIBUTE_DIRECTORY);
                        atributs = GetFileAttributes((LPCSTR) name);
                        if( atributs & FILE_ATTRIBUTE_DIRECTORY) cout << "[The change was successful]" << endl;
                        else cout << " [Error in changing the attribute]" << endl;
                        break;
                    case 4:
                        SetFileAttributes( (LPCSTR) name, FILE_ATTRIBUTE_HIDDEN);
                        atributs = GetFileAttributes((LPCSTR) name);
                        if( atributs & FILE_ATTRIBUTE_HIDDEN) cout << "[The change was successful]" << endl;
                        else cout << " [Error in changing the attribute]" << endl;
                        break;
                    case 5:
                        SetFileAttributes( (LPCSTR) name, FILE_ATTRIBUTE_NORMAL);
                        atributs = GetFileAttributes((LPCSTR) name);
                        if( atributs & FILE_ATTRIBUTE_NORMAL) cout << "[The change was successful]" << endl;
                        else cout << " [Error in changing the attribute]" << endl;
                        break;
                    case 6:
                        SetFileAttributes( (LPCSTR) name, FILE_ATTRIBUTE_READONLY);
                        atributs = GetFileAttributes((LPCSTR) name);
                        if( atributs & FILE_ATTRIBUTE_READONLY) cout << "[The change was successful]" << endl;
                        else cout << " [Error in changing the attribute]" << endl;
                        break;
                    case 7:
                        SetFileAttributes( (LPCSTR) name, FILE_ATTRIBUTE_SYSTEM);
                        atributs = GetFileAttributes((LPCSTR) name);
                        if( atributs & FILE_ATTRIBUTE_SYSTEM) cout << "[The change was successful]" << endl;
                        else cout << " [Error in changing the attribute]" << endl;
                        break;
                    default:
                        break;
                }
            break;
        case 3:
            cout << " [Enter the file name as c:\\Example\\Example.txt]:" << endl;
            cin >> select_file;
            name =  (LPCWSTR) (select_file.c_str());
            hFile = CreateFile( (LPCSTR) name, GENERIC_READ | GENERIC_WRITE | DELETE, 0, NULL, CREATE_ALWAYS, 0, NULL);
            if (hFile != INVALID_HANDLE_VALUE){
                fResult = GetFileInformationByHandle( hFile, &fhi);
                if (fResult){
                    cout << " [The information was received]" << endl; // Получена информация о файле
                    cout << " [Atributes]: " << fhi.dwFileAttributes << endl;
                    if(GetFileTime(hFile, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime)){
                       FileTimeToSystemTime(&lpCreationTime, &stUTC);
        SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
        printf(" [Time create]: %02d.%02d.%d  %02d:%02d", stLocal.wMonth, stLocal.wDay, stLocal.wYear,
            stLocal.wHour, stLocal.wMinute);

        FileTimeToSystemTime(&lpLastAccessTime, &stUTC);
        SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
        printf("\n [Time access]: %02d.%02d.%d  %02d:%02d", stLocal.wMonth, stLocal.wDay, stLocal.wYear,
            stLocal.wHour, stLocal.wMinute);

        FileTimeToSystemTime(&lpLastWriteTime, &stUTC);
        SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
        printf("\n [Time write]: %02d.%02d.%d  %02d:%02d", stLocal.wMonth, stLocal.wDay, stLocal.wYear,
            stLocal.wHour, stLocal.wMinute);
                    }
                    cout<< endl;
                    cout << " [Serial Number]: " << fhi.dwVolumeSerialNumber <<endl;
                    cout << " [File Size(High)]: " << fhi.nFileSizeHigh <<endl;   //старшие 
                    cout << " [File Size(Low)]: " << fhi.nFileSizeLow <<endl;     //и младшие разряды числа
                    cout << " [Number of Links]: " << fhi.nNumberOfLinks <<endl;
                    cout << " [Index(High)]: " << fhi.nFileIndexHigh <<endl;
                    cout << " [Index(Low)]: " << fhi.nFileIndexLow <<endl;
                    
                        cout <<  endl;
                        cout << " [Would you like to change the file time?]:" << endl;
                        cout << " 1.Yes" << endl;
                        cout << " 2.No" << endl;
                        cin >> n;
                        if(n == 1){
                            SetNewFileTime(hFile);
                        }
                        if(n==2){
                            CloseHandle(hFile);
                            }
                    
                }
                else cout << " [An error has occurred]" << endl;
                
                CloseHandle(hFile);
            }
            break;
        default:
            break;    
    }
    
}

int main()
{

    int n;
    
    do {
        system("cls");
        Menu();
        cin >>  n;
        switch (n) {
        case 1:
            DiskList(); 
            break;
        case 2:
            DiskList(); 
            InfoDisk();    
            break;
        case 3:
            CreateAndRemoveDirectory();
            break;
        case 4:
            CreateFile();
            break;
        case 5:
            CopyFileAndMoveFile();
            break;
        case 6:
            InfoAtributs();
            break;
    
        default:
            break;
        }
        system("pause");
    } while (n != 0);
    return 0;
}