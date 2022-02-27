#include <iostream>
#include <windows.h>

using namespace std;

void Menu() {
    cout << endl;
    cout << " [Virtual address space exploration]" << endl;
    cout << " 1.Information Systems" << endl;
    cout << " 2.Information Memory" << endl;
    cout << " 3.Information Memory at a certain address" << endl;
    cout << " 4.Reservation Memory" << endl;
    cout << " 5.Input Data Memory" << endl;
    cout << " 6.Protect Memory" << endl;
 
}

void SystemInformation(){
    SYSTEM_INFO Info;  //отображает сведения о конфигурации операционной системы
    GetSystemInfo(&Info);
      if(Info.wProcessorArchitecture == 12){
        cout << " [ARM64]" << endl;
    }
    else if(Info.wProcessorArchitecture == 9){
        cout << " [x64 (AMD or Intel)]" << endl;
    }
    else if(Info.wProcessorArchitecture == 6){
        cout << " [Intel Itanium Processor Family (IPF)]" << endl;
    } 
     else if(Info.wProcessorArchitecture == 5){
        cout << " [ARM]" << endl;
    }
    else if(Info.wProcessorArchitecture == 0){
        cout << " [Intel x86]" << endl;
    }
    cout <<" [OEM ID]: " << Info.dwOemId << endl; 
    cout <<" [Number of processors]: " << Info.dwNumberOfProcessors << endl;
    cout <<" [Page size]: " << Info.dwPageSize << endl;
    cout <<" [Processor type]: " <<  Info.dwProcessorType << endl;
    cout <<" [Minimum application address]: " << Info.lpMinimumApplicationAddress << endl;
    cout <<" [Maximum application address]: " << Info.lpMaximumApplicationAddress << endl;
    cout <<" [Active processor mask]: " << Info.dwActiveProcessorMask << endl;
    cout <<" [Granularity for the starting address where virtual memory can be allocated]: " << Info.dwAllocationGranularity << endl;
    cout << " [Architecture dependent processor level]: " << Info.wProcessorLevel << endl;
    cout << " [Architecture dependent processor revision]: " << Info.wProcessorRevision <<endl;
}

void MemoryInformation(){
 	MEMORYSTATUSEX memoryStatus;  //содержит информацию о памяти компьютера
	memoryStatus.dwLength = sizeof(memoryStatus); //размер структуры в байтах
	GlobalMemoryStatusEx(&memoryStatus); //информация о текущей памяти компьютера
	cout << " [Physical memory is used]: " << memoryStatus.dwMemoryLoad << "%" << endl;
	cout << " [Physical memory total]: " << memoryStatus.ullTotalPhys / 1024 / 1024 << " MB" << endl;
	cout << " [Physical memory available]: " << memoryStatus.ullAvailPhys / 1024 / 1024 << " MB" << endl;
	cout << " [Total swap file]: " << memoryStatus.ullTotalPageFile / 1024 / 1024 << " MB" << endl;
	cout << " [The swap file is available]: " << memoryStatus.ullAvailPageFile / 1024 / 1024 << " MB" << endl;
	cout << " [Total virtual memory]: " << memoryStatus.ullTotalVirtual / 1024 / 1024 << " MB" << endl;
	cout << " [Virtual memory is available]: " << memoryStatus.ullAvailVirtual / 1024 / 1024 << " MB" << endl;
    
}

void InformationMemorySpec(){
    LPVOID adress;
    MEMORY_BASIC_INFORMATION lpBuffer;  //адрес структуры
    SIZE_T l;
    SYSTEM_INFO Info;  //отображает сведения о конфигурации операционной системы
    GetSystemInfo(&Info);
    l = sizeof(lpBuffer);
    cout <<" [Minimum application address]: " << Info.lpMinimumApplicationAddress << endl;
    cout <<" [Maximum application address]: " << Info.lpMaximumApplicationAddress << endl;
    
    cout << " [Input adress memory as 0xBFFFFFFF]: " << endl;
    cin >> adress;
    
    l = VirtualQuery(adress, &lpBuffer, l);  //адрес области, адрес информационного буфера, размер буфера
    if (l != 0){
        cout << " [Base Adress]: " << lpBuffer.BaseAddress << endl; // Сообщает то же значение, что и параметр lpAddress, но округленное до ближайшего меньшего адреса, кратного размеру страницы
        cout << " [AllocationBase]: " << lpBuffer.AllocationBase << endl; // Идентифицирует базовый адрес региона, включающего в себя адрес, указанный в параметре lpAddress
        cout << " [AllocationProtect]: " << lpBuffer.AllocationProtect << endl; // Идентифицирует атрибут защиты, присвоенный региону при его резервировании
        cout << " [RegionSize]: " << lpBuffer.RegionSize << endl; // Сообщает суммарный размер (в байтах) группы страниц, которые начинаются с базового адреса BaseAddress и имеют те же атрибуты защиты, состояние и тип, что и страница, расположенная по адресу, указанному в параметре lpAddress
        cout << " [Protect]: " << lpBuffer.Protect << endl; //Идентифицирует атрибут защиты (PAGE_*) всех смежных страниц, которые имеют те же атрибуты защиты, состояние и тип, что и страница, располо-женная по адресу, указанному в параметре lpAddress
        cout <<" [Status of pages]:"<<endl;
        if( lpBuffer.State == MEM_COMMIT){
            cout << " Ficksation Page " << endl;  //выделенные для использования
        }
        else if( lpBuffer.State == MEM_FREE ){
            cout << " Free Page " << endl; //свободный тип
        }
        else if( lpBuffer.State == MEM_RESERVE ){
            cout << " Rezerv Page" << endl;  //зарезервированный
        }
        
        cout << " [Memory type]: ";
        
        switch(lpBuffer.Type) {
            case MEM_PRIVATE:
                cout << " MEM_PRIVATE" << endl; //диапазон адресов сопоставлен со страничным файлом
                break;
            case MEM_IMAGE:
                cout << " MEM_IMAGE" << endl;  //диапазон виртуальных адресов сопоставлен с образом EXE- или DLL-файла
                break;
            case MEM_MAPPED:
                cout << " MEM_MAPPED" << endl; //диапазон виртуальных адресов сопоставлен с файлом данных, проецируемым в память
                break;
            default:
                cout << " NO TYPE" << endl;
                break;
        }
    }
    else{
        cout << " [An error occurred while analyzing the memory]" << endl;
    }

}

void reserveMemory() {
    PVOID address;
    SIZE_T dwSize;
    PVOID p;
    MEMORY_BASIC_INFORMATION lpBuffer;
    BOOL Free;
     SYSTEM_INFO Info;  //отображает сведения о конфигурации операционной системы
    GetSystemInfo(&Info);
    cout << " [Input Size]: " << endl;
    cin >> dwSize;

    cout <<" [Minimum application address]: " << Info.lpMinimumApplicationAddress << endl;
    cout <<" [Maximum application address]: " << Info.lpMaximumApplicationAddress << endl;
    cout << " [Input adress memory as 0x00000000]:" << endl;
    cin >> address;
    
    p = VirtualAlloc(address, dwSize, MEM_RESERVE, PAGE_EXECUTE_READWRITE); //адрес для резервирования или выделения памяти, размер выделяемого региона, тип распределения памяти, тип защиты доступа 
    //MEM_RESERVE-резервирует блок адресов без выделения памяти
    //PAGE_EXECUTE_READWRITE-допускается выполнение, чтение, запись
    if( p != 0 ) {
        cout << " [Memory highlighted, adress]: " << p << endl; // Память выделена
    }
    else{
        cout << " [Memory no highlighted]" << endl;
        return;
    }
    cout <<" [Status of pages]:"<<endl;
    dwSize = sizeof(lpBuffer);
    dwSize = VirtualQuery(p, &lpBuffer, dwSize);
    
    if( lpBuffer.State == MEM_COMMIT){
        cout << " Ficksation Page " << endl;
    }
    else if( lpBuffer.State == MEM_FREE ){
        cout << " Free Page  " << endl;
    }
    else if( lpBuffer.State == MEM_RESERVE ){
        cout << " Rezerv Page" << endl;
    }
    
    Free = VirtualFree(p, 0, MEM_RELEASE); //освобождение региона адресного пространства
    if (Free != 0 ){
        cout << " Memory Cleaned!" << endl;
    }
    else{
        cout << " No Cleaned Memory!" << endl;
    }
}

void WriteDataCell() {
    PVOID address;
    SIZE_T dwSize=30;
    PVOID p;
    BOOL Free;
    SYSTEM_INFO Info;  //отображает сведения о конфигурации операционной системы
    GetSystemInfo(&Info);
    cout <<" [Minimum application address]: " << Info.lpMinimumApplicationAddress << endl;
    cout <<" [Maximum application address]: " << Info.lpMaximumApplicationAddress << endl;
    cout << " [Input adress memory as 0x11111111]: "<< endl;
    cin >> address;
    p = VirtualAlloc(address, dwSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if( p == 0 ) {
        cout << " [Memory no highlighted!] " << endl;
        return;
    }

    cout << " [Adress]: " << (int)(*((char *)p)) << endl;
    *((char *)p) = 'help';
    cout << " [Adress]: " << (int)(*((char *)p)) << endl;

    
    Free = VirtualFree(p, 0, MEM_RELEASE);
    if (Free != 0 ){
        cout << "Memory Cleaned!" << endl;
    }
    else{
        cout << "No Cleaned Memory!" << endl;
    }


  
}

void Protect(){
    PVOID address;
    SIZE_T dwSize=10;
    PVOID p;
    BOOL Free;
    int choice;
    DWORD flag;
    DWORD old;
    SYSTEM_INFO Info;  //отображает сведения о конфигурации операционной системы
    GetSystemInfo(&Info);
    cout << " [Input adress memory as 0x00000011]:  "<< endl;
    cin >> address;
    p = VirtualAlloc(address, dwSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if( p == 0 ) {
        cout << " [Memory no highlighted!] " << endl;
        return;
    }
    cout << " [Adress]: " << p << endl;
    
    cout << " [Value]: " << (int)(*((char *)p)) << endl;
    
    cout << " [Input Choice Flag]: " << endl;
    cout << " 1.PAGE_READONLY " << endl;
    cout << " 2.PAGE_READWRITE " << endl;
    cout << " 3.PAGE_EXECUTE " << endl;
    cout << " 4.PAGE_EXECUTE_READ " << endl;
    cout << " 5.PAGE_EXECUTE_READWRITE " << endl;
    cout << " 6.PAGE_GUARD " << endl;
    cout << " 7.PAGE_NOCACHE " << endl;
    cin >> choice;
    
    switch(choice){
        case 1:
            flag = PAGE_READONLY;
            break;
             case 2:
            flag = PAGE_READWRITE;
            break;
             case 3:
            flag = PAGE_EXECUTE;
            break;
             case 4:
            flag = PAGE_EXECUTE_READ;
            break;
             case 5:
            flag = PAGE_EXECUTE_READWRITE;
            break;
             case 6:
            flag = PAGE_GUARD;
            break;
             case 7:
            flag = PAGE_NOCACHE;
            break;
      
    }
    
    if( VirtualProtect(p, dwSize, flag, &old) ) {//адрес анчальной страницы области страниц, размер области, тип защиты, Указатель на переменную, которая получает предыдущее значение защиты доступа первой страницы в указанной области страниц.
        cout << " [Access Changed!]" << endl;
    }
    else{
        cout << " [Access not Changed!]" << endl;
    }
    
    if( flag == PAGE_READONLY ){
        cout << " [No data, No Root!]" << endl;
    }
    else{
        *((char *)p) = 100;
        cout << " [Value]: " << (int)(*((char *)p)) << endl;
    }
    
    Free = VirtualFree(p, 0, MEM_RELEASE);
    if (Free != 0 ){
        cout << " [Memory Cleaned!]" << endl;
    }
    else{
        cout << " [No Cleaned Memory!]" << endl;
    }
}

int main()
{
   
    int input;
 //   int adr = 0; 
   // void* word;
  //  DWORD size;
   // string address;
    
    do {
    
        Menu();
        cin >> input;
        switch (input) {
        case 1:
            SystemInformation(); 
            break;
        case 2:
            MemoryInformation();   
            break;
        case 3:
            InformationMemorySpec();
            break;
        case 4:
            reserveMemory();
            break;
        case 5:
            WriteDataCell();
            break;
        case 6:
            Protect();
            break;

        default:
            break;
        }
        system("pause");
    } while (input != 0);
    return 0;
}
