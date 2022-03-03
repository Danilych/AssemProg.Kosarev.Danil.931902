#include <iostream>
#include <time.h>
#include "AssemblerSort.h"

int main()
{
    void (*fncptr)(int*, int);
    fncptr = &AssemblerInsert::ArraySortBubble;

    srand(time(NULL));
    int MyArr[10];
    std::cout << "Bubble sort!\n\n";
    for (int i = 0; i < 10; i++)
    {
        MyArr[i] = rand() % 1000;
        std::cout << MyArr[i] << std::endl;
    }

    _asm
    {
        lea esi, [MyArr]
        push 10
        push esi
        call fncptr
        add esp, 8
    }
    std::cout << "\n\n";

    for (int i = 0; i < 10; i++)
        std::cout << MyArr[i] << std::endl;

    std::cout << "\n\n";
    std::cout << "Shell sort!\n\n";
    for (int i = 0; i < 10; i++)
    {
        MyArr[i] = rand() % 1000;
        std::cout << MyArr[i] << std::endl;
    }

    fncptr = &AssemblerInsert::ArraySortShell;
    _asm
    {
        lea esi, [MyArr]
        push 10
        push esi
        call fncptr
        add esp, 8
    }
    std::cout << "\n\n";
    for (int i = 0; i < 10; i++)
        std::cout << MyArr[i] << std::endl;
    system("Pause");
}

// { 10,60,20,30,40,00,50,70,80,90 };
// { 10,60,20,30,40,00,50,70,80,90 };
// { 10,20,60,30,40,00,50,70,80,90 };
// { 10,20,30,60,40,00,50,70,80,90 };
// { 10,20,30,40,60,00,50,70,80,90 };
// { 10,20,30,40,00,60,50,70,80,90 };
// { 10,20,30,40,00,50,60,70,80,90 };
// { 10,20,30,40,00,50,60,70,80,90 };