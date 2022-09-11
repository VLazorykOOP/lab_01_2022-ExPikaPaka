#include <Windows.h>
#include <iostream>
#include <fstream>
#include <ios>
#include <vector>


void CText(const char t[], int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    std::cout << t;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

int userSize;
const int ARRAY_MAX_SIZE = 560;

enum { AStatic, ANew, ACalloc, AVec };
int AMode;

int ConsoleInputSizeArray(const int sizeMax)
{
    int size = 0; 
    char buff[256];

    char buf[16];
    _itoa_s(sizeMax, buf, 10);

    do {
        CText("  Введіть розмір масиву ", 3);
        CText("[1 - ", 12);
        CText(buf, 12);
        CText("]", 12);
        CText(" : ", 3);
        std::cin >> size;

        if (std::cin.fail()) {
            CText(" Невірно введений розмір!   \n", 112);
           
            std::cin.clear();
            std::cin >> buff;
        }
    } while (size <= 0 || size >= sizeMax);
    return size;
}

int ConsoleInputArray(int sizeMax, double A[]) {
    char buff[256];
    char buf[16];
    
    int size = ConsoleInputSizeArray(sizeMax);
    for (int i = 0; i < size; i++) {
        _itoa_s(i, buf, 10);
        CText("  Введіть елемент ", 3);
        CText("[", 12);
        CText(buf, 12);
        CText("] ", 12);
        CText(": ", 3);

        std::cin >> A[i];
        if (std::cin.fail()) {
            CText(" Неправильне значення! Введіть раціональні число!   \n", 112);

            std::cin.clear();
            std::cin >> buff;
            i--;
        }

    }
    return size;
}


int RndInputArray(int sizeMax, double A[])
{
    int size = ConsoleInputSizeArray(sizeMax);
    int r1 = 0, r2 = 0, r3 = 0;
    srand(time(NULL));

    std::cout << "  ";
    for (int i = 0; i < size; i++) {
        r1 = rand();
        r2 = rand();
        r3 = rand();
        A[i] = 100.0 * r1;
        A[i] = A[i] / (1.0 + r2);
        if (r3 % 3 == 0) A[i] = -A[i];
        std::cout << A[i] << "   ";
    }
    return size;
}

int ConsoleInputDynamicArrayNew(int sizeMax, double* pA) {
    char buff[256];
    char buf[16];

    int size = ConsoleInputSizeArray(sizeMax);
    pA = new double[size];
    if (pA == nullptr) { return 0; }
    for (int i = 0; i < size; i++) {
        _itoa_s(i, buf, 10);
        CText("  Введіть елемент ", 3);
        CText("[", 12);
        CText(buf, 12);
        CText("] ", 12);
        CText(": ", 3);

        std::cin >> pA[i];
        if (std::cin.fail()) {
            CText(" Неправильне значення! Введіть раціональні число!   \n", 112);

            std::cin.clear();
            std::cin >> buff;
            i--;
        }

    }
    return size;
}

int ConsoleInputDynamicArray_calloc(int sizeMax, double* pA) {
    char buff[256];
    char buf[16];

    int size = ConsoleInputSizeArray(sizeMax);
    pA = (double*)calloc(size, sizeof(double));      // pA = (double*)malloc(size * sizeof(double)); 
    if (pA == nullptr) { return 0; }
    for (int i = 0; i < size; i++) {
        _itoa_s(i, buf, 10);
        CText("  Введіть елемент ", 3);
        CText("[", 12);
        CText(buf, 12);
        CText("] ", 12);
        CText(": ", 3);

        std::cin >> pA[i];
        if (std::cin.fail()) {
            CText(" Неправильне значення! Введіть раціональні число!   \n", 112);

            std::cin.clear();
            std::cin >> buff;
            i--;
        }

    }
    return size;
}

int ConsoleInputVector(int sizeMax, std::vector<double> &A) {
    char buff[256];
    char buf[16];

    int size = ConsoleInputSizeArray(sizeMax);
    double d;

    for (int i = 0; i < size; i++) {
        _itoa_s(i, buf, 10);
        CText("  Введіть елемент ", 3);
        CText("[", 12);
        CText(buf, 12);
        CText("] ", 12);
        CText(": ", 3);

        std::cin >> d;
        if (std::cin.fail()) {
            CText(" Неправильне значення! Введіть раціональні число!   \n", 112);

            std::cin.clear();
            std::cin >> buff;
            i--;
        }
        else {
            A.push_back(d);
        }

    }
    return size;
}



void WriteArrayTextFile(int n, double *arr, const char *fileName ) {
    std::ofstream fout(fileName);
    if (fout.fail()) return;
    fout << n << std::endl;
    for (int i = 0; i < n; i++)
        fout << arr[i] << "   ";

    CText("\n\n  ", 0);
    CText("Дані збережено у файл  ", 112);
    CText(fileName, 128);
    CText("\n  ", 0);
   
    char full[_MAX_PATH];
    if (_fullpath(full, fileName, _MAX_PATH) != NULL)
        CText(full, 128);

    CText("\n", 0);

    fout.close(); 
}



void ShowMainMenu();
void MenuManager();



void Task1_v11(int arrSize, double *arr) {

    if (arrSize == 1)
        arr[0] *= 2;
    else
        for (int i = 0; i < arrSize / 2; i++)
            arr[i] *= 2;

    for (int i = (arrSize / 2); i <= arrSize; i++)
        arr[i] *= 3;

    std::cout << "  ";
    for (int i = 0; i < arrSize; i++)
        std::cout << arr[i] << "   ";
   
}



void Task2_v11(int arrSize, double* arr) {
    int pos1 = 0;
    int pos2 = 0;
    int size = 0;
    double elMin = 0;
    char buf[16];
    bool fl = 0;

    while (arr[pos1] >= 0) {     // Finding first negative element
        pos1++;
        if (pos1 > arrSize - 1) {
            std::cout << " ";
            CText("У масиві не має від'ємних елементів! Введіть масив знову.\n", 112);
            fl = 1;
            break;
        }
    }
    if (fl) return;


    pos1++;
    size = arrSize - pos1;
    elMin = (double)pos1;

    if (pos1 < arrSize - 1) {       // Summing by pare, and moving everything
        while (pos1 < arrSize) {
            arr[pos1] += arr[pos1 + 1];
            pos2 = pos1 + 1;
            while (pos2 < arrSize) {
                arr[pos2] = arr[pos2 + 1];
                if (pos2 == arrSize - 1) arr[pos2] = 0;
                pos2++;

            }
            arrSize--;
            pos1++;
        }
    }
    if (pos1 != arrSize - 1)    // Exception wrong size
        if (size % 2 != 0) arrSize++;



    pos1 = elMin;
    pos2 = pos1;
    elMin = arr[pos1]; // Minimal element

    

    while (pos1 < arrSize) {        // Finding last minimal element from pos1
        if (arr[pos1] < elMin) {
            elMin = arr[pos1];
            pos2 = pos1;
        }
        pos1++;
    }

    std::cout << "  ";
    for (int i = 0; i < arrSize; i++)
        std::cout << arr[i] << "   ";
    std::cout << "\n";

    if (pos2 != arrSize) {
        _itoa_s(pos2 + 1, buf, 10);
        std::cout << "  ";
        CText("Номер останього мінімального елемента за умовою : ", 112);
        CText(" ", 128);
        CText(buf, 128);
        CText(" ", 128);
        std::cout << "\n";
    }
    else {
        std::cout << "  ";
        CText("Не існує мінімального елементу за умовою задачі!\n", 112);
    }
   
   
}




float area(int x1, int y1, int x2, int y2, int x3, int y3) {
    return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}

bool isInside(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y) {
 
    float A = area(x1, y1, x2, y2, x3, y3);
    float A1 = area(x, y, x2, y2, x3, y3);
    float A2 = area(x1, y1, x, y, x3, y3);
    float A3 = area(x1, y1, x2, y2, x, y);

    return (A == A1 + A2 + A3);
}


void Task3_v11(int arrSize, double* arr, double* arr2) {

    int cnt = 0;
    char buff[16];

    std::cout << "  ";
    CText("Заданий трикутник: ", 112);
    for (int i = 0; i < 3; i++) {
        CText("(", 128); _itoa_s(arr2[i], buff, 10); CText(buff, 128);
        CText(", ", 128); _itoa_s(arr2[i + 1], buff, 10); CText(buff, 128);
        CText(")", 128); CText("   ", 112);
    }
    std::cout << '\n';

    for (int i = 0; i < userSize; i += 2) {   // Calculating here
       
        std::cout << "  ";
        CText("Точка ", 112);
        CText("(", 128); _itoa_s(arr[i], buff, 10); CText(buff, 128);
        CText(", ", 128); _itoa_s(arr[i + 1], buff, 10); CText(buff, 128);
        CText(")", 128); CText("   ", 112);
      
        if (isInside(arr2[0], arr2[1], arr2[2], arr2[3], arr2[4], arr2[5], arr[i], arr[i + 1]))
            CText(" належить трикутнику", 115);
        else
            CText(" не належить трикутнику", 116);
        std::cout << '\n';
    }
}



void ShowInputMenu() {

    std::cout << "\n  ";
    CText(" Виберіть спосіб введення данних   \n", 225);
    std::cout << '\n';
    CText("  1. Рандомно\n", 11);
    CText("  2. З консолі (статичний масив)\n", 11);
   /* CText("  3. З консолі (calloc)\n", 11);
    CText("  4. З консолі (new)\n", 11);
    CText("  5. З консолі (vector)\n", 11);*/
    CText("  3. Вийти \n\n\n", 11);

    CText("  Виберіть спосіб з меню : ", 3);

}



int InputManager(double* arr, double* arr2, double* arrNew, double* arrCalloc, std::vector<double> arrVec) {
    int key;
    char buff[256];
    char fileAddress[1024];
    memset(fileAddress, 0, sizeof(fileAddress));

    std::cin >> key;

    if (std::cin.fail()) {
        std::cout << "  ";
        CText("Невірно введений запит! Введіть число від 1 до 3\n", 112);
        std::cin.clear();
        std::cin >> buff;
        InputManager(arr, arr2, arrNew, arrCalloc, arrVec);
    }
    else switch (key) {

    case 1:
        userSize = RndInputArray(ARRAY_MAX_SIZE, arr);
        break;

    case 2:
        AMode = AStatic;
        userSize = ConsoleInputArray(ARRAY_MAX_SIZE, arr);
        break;

    /*case 3:
        AMode = ACalloc;
        userSize = ConsoleInputDynamicArray_calloc(ARRAY_MAX_SIZE, arrCalloc);
        break;

    case 4:
        AMode = ANew;
        userSize = ConsoleInputDynamicArrayNew(ARRAY_MAX_SIZE, arrNew);
        break;

    case 5:
        AMode = AVec;
        userSize = ConsoleInputVector(ARRAY_MAX_SIZE, arrVec);
        break;*/
  
       
    case 3:
        break;

    default:
        std::cout << "  ";
        CText("Вибраний не правильний спосіб!\n", 112);
        CText("\n\n\n  Виберіть спосіб з меню : ", 3);
        InputManager(arr, arr2, arrNew, arrCalloc, arrVec);
        break;
    }

    return 0;
}


void ShowMainMenu() {

    std::cout << "  ";
    CText("         Меню          \n", 225);
    std::cout << '\n';
    CText("  1. N_1_V11 Помножити першу половину масиву на 2, другу на 3   \n", 11);
    CText("  2. N_2_V11 Знайти номер мінімального ел. серед попарно доданих ел., що правіше, за перший від'ємний ел.\n", 11);
    CText("  3. N_3_V11 Задати трикутник. Задати довільні точки. Визначити, скільки точок належать трикутнику\n", 11);
    CText("  4. Показати меню (Очистити вікно)\n", 11);
    CText("  5. Вийти \n\n\n", 11);

    CText("  Виберіть дію з меню : ", 3);
}

void MenuManager(double *arr, double *arr2, double *arrNew, double *arrCalloc, std::vector<double> arrVec) {
    int key;
    char buff[256];

    std::cin >> key;

    if (std::cin.fail()) {
        std::cout << "  ";
        CText("Невірно введений запит! Введіть число від 1 до 5\n", 112);
        std::cin.clear();
        std::cin >> buff;
        MenuManager(arr, arr2, arrNew, arrCalloc, arrVec);
    }
    else switch (key) {

    case 1:
        ShowInputMenu();
        InputManager(arr, arr2, arrNew, arrCalloc, arrVec);
        if (AMode == AStatic) WriteArrayTextFile(userSize, arr, "Task_1_Original_Array.txt");
        //if (AMode == ANew) WriteArrayTextFile(userSize, arrNew, "Task_1_Original_Array.txt");
        //if (AMode == ACalloc) WriteArrayTextFile(userSize, arrCalloc, "Task_1_Original_Array.txt");

        CText("\n\n  Результат задачі : \n", 3);
        if (AMode == AStatic) Task1_v11(userSize, arr);
        //if (AMode == ANew) Task1_v11(userSize, arr);
        //if (AMode == ACalloc) Task1_v11(userSize, arr);
        
        if (AMode == AStatic) WriteArrayTextFile(userSize, arr, "Task_1_Modificated_Array.txt");
        //if (AMode == ANew) WriteArrayTextFile(userSize, arrNew, "Task_1_Modificated_Array.txt");
        //if (AMode == ACalloc) WriteArrayTextFile(userSize, arrCalloc, "Task_1_Modificated_Array.txt");
        CText("\n\n\n  Виберіть дію з меню : ", 3);
        MenuManager(arr, arr2, arrNew, arrCalloc, arrVec);

    case 2:
        ShowInputMenu();
        InputManager(arr, arr2, arrNew, arrCalloc, arrVec);
        if (AMode == AStatic) WriteArrayTextFile(userSize, arr, "Task_2_Original_Array.txt");
        //if (AMode == ANew) WriteArrayTextFile(userSize, arrNew, "Task_2_Original_Array.txt");
        //if (AMode == ACalloc) WriteArrayTextFile(userSize, arrCalloc, "Task_2_Original_Array.txt");

        CText("\n\n  Результат задачі : \n", 3);
        if (AMode == AStatic) Task2_v11(userSize, arr);
        //if (AMode == ANew) Task2_v11(userSize, arrNew);
        //if (AMode == ACalloc) Task2_v11(userSize, arrCalloc);

        if (AMode == AStatic) WriteArrayTextFile(userSize, arr, "Task_2_Modificated_Array.txt");
        //if (AMode == ANew) WriteArrayTextFile(userSize, arrNew, "Task_2_Modificated_Array.txt");
        //if (AMode == ACalloc) WriteArrayTextFile(userSize, arrCalloc, "Task_2_Modificated_Array.txt");

        CText("\n\n\n  Виберіть дію з меню : ", 3);
        MenuManager(arr, arr2, arrNew, arrCalloc, arrVec);

    case 3:
        CText("  Введіть 6 координат трикутника (x1, y1)..\n", 3);
        ConsoleInputArray(7, arr2);
        WriteArrayTextFile(userSize, arr2, "Task_3_Points_Array.txt");

        CText("  Введіть координати точок (x1, y1)..\n", 3);
        userSize = ConsoleInputArray(ARRAY_MAX_SIZE, arr);
       
        CText("\n\n  Результат задачі : \n", 3);
        Task3_v11(userSize, arr, arr2);
        WriteArrayTextFile(userSize, arr2, "Task_3_Triangle_Array.txt");
        CText("\n\n\n  Виберіть дію з меню : ", 3);
        MenuManager(arr, arr2, arrNew, arrCalloc, arrVec);

    case 4:
        system("cls");
        ShowMainMenu();
        MenuManager(arr, arr2, arrNew, arrCalloc, arrVec);

    case 5:
        exit(0);

    default:
        std::cout << "  ";
        CText("Вибране не правильне завдання!\n", 112);
        CText("\n\n\n  Виберіть дію з меню : ", 3);
        MenuManager(arr, arr2, arrNew, arrCalloc, arrVec);
        break;
    }
    
}



int main() {

    system("chcp 1251");
    system("cls");

    double A[ARRAY_MAX_SIZE], B[ARRAY_MAX_SIZE],C[ARRAY_MAX_SIZE];

    double* ANew = NULL;
    double* ACalloc = NULL;
    std::vector<double> AVector;

    ShowMainMenu();
    MenuManager(A, B, ANew, ACalloc, AVector);
    
    return 0;
}