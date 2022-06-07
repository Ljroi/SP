#include <stdio.h>
#include <stdlib.h>

int main() 
{
    srand(time(NULL));

    // Размер массива
    const int size_mass = 15;

    int mass[size_mass];

    for (int i = 0; i < size_mass; i++)
    {
        // Заполнение массива числами от 0 до 99
        mass[i] = rand() % 100;
        // Вывод числа
        printf("%d ", mass[i]);
    }
    printf("\n");

    // Индекс и значение максимального числа
    int index;
    int max_number;

    // Указатель на массив
    int* ptr_mass = mass;

    // АССЕМБЛЕРНАЯ ВСТАВКА 
    asm (
            // Сохранение первого адреса массива
            "mov %[mass], %%rax;"
            // Сохранение длины массива
            "movl %[size_mass], %%ebx;"

            // Индекс максимального ставим 0
            "xorl %%ecx, %%ecx;"
            // Значение максимального ставим первым значнием из массива
            "movl (%%rax), %%edx;"
            // Обнуление счетчика пройденых значений
            "xorl %%edi, %%edi;"
            
        "main_loop:"
            // Получаем значение из массива
            "movl (%%rax), %%esi;"
            // Если оно не больше "большего", то просто переходим к след.
            "cmpl %%esi, %%edx;"
            "jg next;"
            
            // Устанавливаем новый индекс и значение 
            "movl %%esi, %%edx;"
            "movl %%edi, %%ecx;"

            // Переход к след значению
        "next:"
            // Увеличение счетчика эл.
            "inc %%edi;"
            // Перемещение к след. эл. в адресе
            "addq $4, %%rax;"
            
            // Если edi != size_mass, то повторяем действия
            "cmpl %%ebx, %%edi;"
            "jne main_loop;"

            
            // Заполняем из регистров в переменные
            "movl %%edx, %[max_number];"
            "movl %%ecx, %[index];"

            :
            :[size_mass]"m"(size_mass), [mass]"m"(ptr_mass),
                [index]"m"(index), [max_number]"m"(max_number)
            :
        );

    // Вывод индекса и значения
    printf("Index max number = %d\n", index);
    printf("Max number = %d\n", max_number);

    return 0;

}
