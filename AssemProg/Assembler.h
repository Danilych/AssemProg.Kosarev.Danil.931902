#pragma once

static class AssemblerInsert
{

    /*
    1. Реализовать класс используя ассемблерные вставки.
        1. Базовые математические операции.
        1. Сложение.                                        +
        2. Вычитание.                                       +
        3. Умножение.                                       +
        4. Деление.                                         +
    2. Операции сравнения.                                  +
    3. Логические операции.                                 +
    not, and, or , xor
    4. Индексация по массиву                                +
    5. Операции сдвига                                      +
    6. Реализовать метод который будет выполнять лямбда - функции с заданным кол - во итераций. void (func, n); +
    */
    //1
public:
    static int Add(int a, int b)
    {
        int c = 0;
        _asm
        {
            mov eax, a
            add eax, b
            mov c, eax
        }
        return c;
    }

    static int Substract(int a, int b)
    {
        int c = 0;
        _asm
        {
            mov eax, a
            sub eax, b
            mov c, eax
        }
        return c;
    }

    static _int64 Multiply(int a, int b)
    {
        int r1 = 0;
        int r2 = 0;

        _int64 result = 0;

        _asm
        {
            mov eax, b
            imul a
            mov r1, edx
            mov r2, eax
        }

        if ((a >= 0 && b >= 0) || (a < 0 && b < 0) || a==0 || b==0)
        {
           
            result |= static_cast<_int64>(r1) << 32;

            result |= r2;

        }
        else
        {
            long long rr2 = 0;
            for (int i = 0; i < 32; i++) if (r2 & (1 << i)) rr2 |= 1LL << i;
            
           
            result |= rr2;

            result |= static_cast<_int64>(r1) << 32;
            
        }

        return result;
    }

    static int Divide(_int64 a, int b)
    {
        int a1 = 0; //small
        int a2 = 0; //big

        for (int i = 0; i < 64; i++)
        {
            if (i < 32)
            {
                if (a & (1ULL << i)) a1 |= 1UL << i;

            }
            else
            {
                if (a & (1ULL << i)) a2 |= 1UL << (i - 32);
            }
        }

        _asm
        {
            mov eax, a1
            mov edx, a2
            idiv b
            mov a1, edx; остаток
            mov a2, eax; частное
        }

        return a2;
    }
    //2
    static bool Eq(int a, int b)
    {
        bool c = false;

        _asm
        {
            mov eax, a
            cmp eax, b
            jne S
            mov c, 1
            S :
        }
        return c;
    }

    static bool Uneq(int a, int b)
    {
        bool c = false;

        _asm
        {
            mov eax, a
            cmp eax, b
            je R
            mov c, 1
            R :
        }
        return c;
    }

    static bool Greater(int a, int b)
    {
        bool c = false;

        _asm
        {
            mov bl, 1
            mov eax, a
            cmp eax, b
            jg E
            ja E
            mov bl, 0
            E : mov c, bl
        }
        return c;
    }

    static bool GreaterEq(int a, int b)
    {
        bool c = false;

        _asm
        {
            mov bl, 1
            mov eax, a
            cmp eax, b
            jge E
            jae E
            mov bl, 0
            E : mov c, bl
        }
        return c;
    }

    static bool Less(int a, int b)
    {
        bool c = false;

        _asm
        {
            mov bl, 1
            mov eax, a
            cmp eax, b
            jl E
            jb E
            mov bl, 0
            E : mov c, bl
        }
        return c;
    }

    static bool LessEq(int a, int b)
    {
        bool c = false;

        _asm
        {
            mov bl, 1
            mov eax, a
            cmp eax, b
            jle E
            jbe E
            mov bl, 0
            E : mov c, bl
        }
        return c;
    }
    //3
    static bool Not(bool a)
    {
        bool b = a;

        _asm
        {
            not b
        }

        if (b & 1) return true;
        else return false;
    }

    static bool And(bool a, bool b)
    {
        bool c = a;

        _asm
        {
            mov al, b
            and c, al
        }

        if (c & 1) return true;
        else return false;
    }

    static bool Or(bool a, bool b)
    {
        bool c = a;

        _asm
        {
            mov al, b
            or c, al
        }

        if (c & 1) return true;
        else return false;
    }

    static bool Xor(bool a, bool b)
    {
        bool c = a;

        _asm
        {
            mov al, b
            xor c, al
        }

        if (c & 1) return true;
        else return false;
    }
    //4
    static int ArrayIndex(int* arr, int in)
    {
        int a = 0;
        _asm
        {
            mov ebx, in
            mov eax, arr
            mov ebx, [eax + 4 * ebx]
            mov a, ebx
        }
        return a;
    }
    //5
    static int LShiftLeft(int a, unsigned char b)
    {
        int c = 0;
        _asm
        {
            mov eax, a
            mov cl, b
            shl eax, cl
            mov c, eax
        }
        return c;
    }

    static int LShiftRight(int a, unsigned char b)
    {
        int c = 0;
        _asm
        {
            mov eax, a
            mov cl, b
            shr eax, cl
            mov c, eax
        }
        return c;
    }

    static int CShiftLeft(int a, unsigned char b)
    {
        int c = 0;
        _asm
        {
            mov eax, a
            mov cl, b
            rol eax, cl
            mov c, eax
        }
        return c;
    }

    static int CShiftRight(int a, unsigned char b)
    {
        int c = 0;
        _asm
        {
            mov eax, a
            mov cl, b
            ror eax, cl
            mov c, eax
        }
        return c;
    }
    //6
    static void Repeat(void (*func)(int, int), int i)
    {
        int c = 0;
        _asm
        {
            START :

            push i
            push c
            call func
            add esp, 8

            add c, 1
            mov eax, i
            cmp c, eax

            je END
            jne START

            END :
        }
    }


    static int Iter(int(*func)(int, int), int a)
    {
        int c = 0;
        int d = 10;
        _asm
        {
        L:
            push a
                push a
                call func
                ; pop eax
                add esp, 8

                add c, 1
                mov eax, d
                cmp c, eax

                je ESCAPE
                jne L
                ESCAPE :
        }
        return a;
    }

};