#include <iostream>
#include "Assembler.h"

void PrintTest(int a, int b)
{
    int c = 0;
    _asm
    {
        mov eax, a
        add eax, b
        mov c, eax
    }
    std::cout << a << " + " << b << " = " << c << std::endl;
}

void PrintTest2()
{

    std::cout << "fhdvjkdfhv" << std::endl;
}

int main()
{
    std::cout << "100+70 = " << AssemblerInsert::Add(100, 70) << std::endl;
    std::cout << "100-70 = " << AssemblerInsert::Substract(100,70) << std::endl;
    std::cout << std::fixed << "100*70 = " << AssemblerInsert::Multiply(100, 70) << std::endl;
    std::cout << std::fixed << "100/70 = " << AssemblerInsert::Divide(100, 70) << std::endl << std::endl;
    std::cout << "100==70 = " << AssemblerInsert::Eq(100, 70) << std::endl;
    std::cout << "100!=70 = " << AssemblerInsert::Uneq(100, 70) << std::endl;
    std::cout << "100>70 = " << AssemblerInsert::Greater(100, 70) << std::endl;
    std::cout << "100>=70 = " << AssemblerInsert::GreaterEq(100, 70) << std::endl;
    std::cout << "100<70 = " << AssemblerInsert::Less(100, 70) << std::endl;
    std::cout << "100<=70 = " << AssemblerInsert::LessEq(100, 70) << std::endl << std::endl;
    std::cout << "Not:True =  " << AssemblerInsert::Not(true) << std::endl;
    std::cout << "True and True =  " << AssemblerInsert::And(true, true) << std::endl;
    std::cout << "True or false =  " << AssemblerInsert::Or(true, false) << std::endl;
    std::cout << "True xor True =  " << AssemblerInsert::Xor(true, true) << std::endl << std::endl;

    int MyArr[10] = { 10,60,20,30,40,00,50,70,80,90 };
    std::cout << "MyArr[5] =  " << AssemblerInsert::ArrayIndex(MyArr, 5) << std::endl << std::endl;

    std::cout << "Logic shift left (4, 4)  " << AssemblerInsert::LShiftLeft(4, 4) << std::endl;
    std::cout << "Logic shift Right (64, 4)  " << AssemblerInsert::LShiftRight(64, 4) << std::endl;
    std::cout << "Cycle shift left (2048, 4)  " << AssemblerInsert::CShiftLeft(2048, 4) << std::endl;
    std::cout << "Cycle shift Right (4, 4)  " << AssemblerInsert::CShiftRight(4, 4) << std::endl << std::endl;

    std::cout << "Print test 10 times (10+current loop iter)  " << std::endl;
    AssemblerInsert::Repeat(&PrintTest, 10);

    AssemblerInsert::Iter([](int a, int b) -> int {int e = a + b; return e; }, 10);
}
