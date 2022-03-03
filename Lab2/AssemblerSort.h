#pragma once

static class AssemblerInsert
{

    //2. ����������� ������� / �����, ������� ��������� �������� ����������.
     //   1. ���������� ���������. + 4
     //   2. + ������ ����������. + 1, 5 - 2   (���������� �����)
    //1
public:
    static void ArraySortBubble(int* arr, int n)
    {
        int currentIterFirst = 1; // ������� �������� �����
        int itersSecondCycle = 0; //������� ��������� ����������� �����
        _asm
        {
                mov eax, arr;       ������ �� ������
            FirstCycleStart :
                mov ebx, n
                cmp currentIterFirst, ebx
                je sortEnd
                mov esi, 0
                mov ebx, n
                sub ebx, currentIterFirst
                mov itersSecondCycle, ebx
                mov ebx, 0;                 ������� ����� 2
            SecondCycleStart :
                cmp ebx, itersSecondCycle
                je SecondCycleEnd;      ��������� ����� �����
                mov ecx, [eax + 4 * ebx]
                cmp ecx, [eax + 4 * ebx + 4];           ��������� ��� ����� �������
                jg swap
                ja swap
                inc ebx
                jmp SecondCycleStart
            swap :
                mov ecx, [eax + 4 * ebx]
                mov edx, [eax + 4 * ebx + 4]
                mov[eax + 4 * ebx], edx
                mov[eax + 4 * ebx + 4], ecx
                inc ebx
                mov esi, 1h
                jmp SecondCycleStart
            SecondCycleEnd:
                add currentIterFirst, 1h
                cmp esi, 0
                je sortEnd
                jmp FirstCycleStart
            sortEnd:
        }
    }

    static void ArraySortShell(int* arr, int n)
    {
        int h = 1; // ������� �������������� �����
        int itersSecondCycle = 0; //������� ��������� while �����
        int tempVar = 0;
        int tempVarTwo = 0;

        _asm
        {
            mov eax, n
            mov edx, 0
            div n
            mov ecx, eax;   n/9

            FirstCycleStart :
            mov ebx, ecx
            cmp h, ebx
            jg goToSecondCycle
            ja goToSecondCycle

                mov eax, 3h
                mul h
                add eax, 1h
                mov h, eax
                jmp FirstCycleStart

                goToSecondCycle:
                ;                       �������� ����������� ����� while
                SecondWhileCycleStart :
                cmp h, 1h
                jl StopWhileCycle
                jb StopWhileCycle;      ��������� ����� �����

                mov ebx, h

                    ThirdForCycleStart:
                cmp ebx, n
                jge StopThirdForCycle
                jae StopThirdForCycle

                    mov ecx, ebx
                    sub ecx, h

                    FourthForCycleStart:

                cmp ecx, 0h
                jl StopFourthCycle
                jb StopFourthCycle

                    mov eax, arr;       ������ �� ������
                    mov tempVar, ecx
                    add ecx, h

                    mov edx, [eax + 4 * ecx]
                    mov ecx, tempVar
                cmp[eax + 4 * ecx], edx
                jle StopFourthCycle
                jbe StopFourthCycle

                    mov tempVar, ecx
                    add ecx, h
                    mov edx, [eax + 4 * ecx];   j + h
                    mov tempVarTwo, edx

                    mov ecx, tempVar
                    mov edx, [eax + 4 * ecx];   j
                    mov tempVar, edx

                    mov edx, tempVarTwo;    j
                    mov[eax + 4 * ecx], edx

                    mov edx, ecx
                    add ecx, h;   j+h
                    mov tempVarTwo, edx

                    mov edx, tempVar
                    mov[eax + 4 * ecx], edx
                    mov ecx, tempVarTwo

                    sub ecx, h
                    jmp FourthForCycleStart

                    StopFourthCycle:

                add ebx, 1h
                jmp ThirdForCycleStart

                    StopThirdForCycle:
                mov eax, h
                    sub eax, 1h

                    mov edx, 0h
                    mov ecx, 3h
                    div ecx
                    mov h, eax
                    jmp SecondWhileCycleStart
                    StopWhileCycle :
        }
        return;
    }
};