#include <stdio.h>

int main() 
{
    // Массив 12 слов
    int array[12] = {4, -3, 5, -11, 2, 4, -6, 0, 1, -8, 12, 1};

    // Положительная и отрицательная сумма
    int pos_sum = 0;
    int neg_sum = 0;

    // Проход по массиву и нахождение сумм
    for (int i = 0; i < 12; i++) 
    {
        if (array[i] < 0)
            neg_sum += array[i];
        else
            pos_sum += array[i];
    }

    // Вывод положительной и отрицательной суммы
    printf("Positive sum = %d\n", pos_sum);
    printf("Negative sum = %d\n", neg_sum);

    // Вывод наличия 7 бита у отрицательной суммы
    printf("7 bit: ");
    if ((neg_sum & 0x80) == 0)
        printf("FALSE\n");
    else
        printf("OK\n");

    return 0;
}
