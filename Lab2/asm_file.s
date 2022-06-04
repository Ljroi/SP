# Подсчет суммы отрицательных и положительный слов
# Проверка 7 бита с отрицательной суммы

# Блок с данными
.data

# Массив 12 слов
array:
    .long 4, -3, 5, -11, 2, 4, -6, 0, 1, -8, 12, 1
array_end:

# Формат вывода положительной суммы
positive_sum: 
    .string "Positive sum = %d\n"

negative_sum:
    .string "Negative sum = %d\n"

# Формат вывода наличия 7 бита 
print_ok:
    .string "7 bit: OK\n"

# Формат вывод отсут. 7 бита
print_no:
    .string "7 bit: FALSE\n"


# Блок с кодом
.text
.global main

# Начало программы
main:
    # Обнуление регистров сумм
    xorl %eax, %eax
    xorl %ebx, %ebx

    # Кидаем начало массива в esi
    movl $array, %esi

# Суммирование значений массива
funct:
    # Вытаскиваем значение из массива
    movl (%esi), %edx
    # Сравниваем с 0
    cmpl $0, %edx

    # Если меньше, то прыгаем в less
    jl less

    # Прибавляем к положительной сумме
    addl %edx, %eax
    # Переходим к след. элементу
    jmp next

less:
    # Прибавляем к отриц. сумме
    addl %edx, %ebx

# Переход к след. элементу
next:
    # Брибавляем к текущему адресу массив 4 (слово = 4 байта)
    addl $4, %esi
    # Если адрес не дошел до конца, то повторяем все действия
    cmp $array_end, %esi
    jne funct

    # Вывод положительной суммы
    pushl %eax
    pushl $positive_sum
    call printf
    addl $8, %esp

    # Вывод отрицательной суммы
    pushl %ebx
    pushl $negative_sum
    call printf
    addl $8, %esp

    # Проверка наличия 7 бита (0х80 = 1000 0000, как раз седьмой бит)
    movl %ebx, %ecx
    # Применение маски 
    andb $0x80, %cl
    # Сравление полученного значения с 0 (если нет 7 бита, то число будет = 0)
    cmpl $0, %ecx
    # Если не равено 0, то есть бит
    jne ok

    # Вывод, если нет бита
    pushl $print_no
    call printf
    jmp end
ok:
    # Вывод, если есть бит
    pushl $print_ok
    call printf

end:
    # Завершение работы программы
    movl $1, %eax
    xorl %ebx, %ebx
    int $0x80
