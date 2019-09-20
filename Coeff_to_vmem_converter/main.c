#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

void bin2hex(char *, unsigned int, char *);

void main()
{
    FILE *fp;
    FILE *fpw[100];
    FILE *fph[100];

    int y;
    char bank_num;          // число банков памяти
    int coef_int;           // общее число коэфициентов после atoi
    int coef_lengt;         // размер одного коэф. в битах
    float coef_lengt_2 = 0; // размер одного коэф. в битах в степени двойки
    int char_number;        // размер данных для записи в файл функцией fwrite
    int i = 0;
    int i_counter = 0; // счетчик считывания каждого коэффициента
    int i_file = 0;    // счетчик для записи файлов
    int i_nulls;       // счетчик нулей для дозаписи в файл
    int i_nulls_write; // счетчик записи нулей в каждый файл
    int nulls_number;  // число нулей
    char null = 0;     // собственно ноль
    int sym;
    char coef_num[6];
    char *num = coef_num;
    unsigned long len;    // размер файла без нулей
    int vmem_number_full; // число коффициентов в файле vmem с учетом дозаписанных нулей

    signed long long int coef_alone_int; // буфер, каждый коэфициент после atoi

    int bank_size;

    char zero_buffer[20]
        = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // буфер для записи нулей в самом конце
    char bufin[20]; // группа переменных из функции преобразования bin hex
    char bufout[100];
    int adr = 0x00000000;
    int sz;
    int output_char; // число выходных символов в vmem файле

    system("chcp 1251");                     // переходим в консоли на русский язык
    system("cls");                           // очищаем окно консоли
    printf("Введите число банков памяти: "); // выводим сообщение
    scanf("%d", &y);                         // вводим значения переменной y
    printf("Число банков y=%d \n", y);       // выводим значение переменной y

    for (bank_num = 0; bank_num < y;) // Функция создания файлов
    {
        char filename[20];
        sprintf(filename, "coef%d.bin", bank_num);
        fpw[bank_num] = fopen(filename, "wb");

        bank_num++;
    }

    printf("\nСоздано %d файлов \n", bank_num);

    printf("\nВыполнить сканирование файла с коэффициентами?\n");

    printf("\nНажми любую кнопку\n");

    getchar();
    getchar();

    fp = fopen("fix_50bit_coef.h", "r"); // открываем файл на чтение
                                         //Чтение (побайтно) данных из файла в бесконечном цикле
    while (1) {
        // Чтение одного байта из файла
        sym = fgetc(fp);

        //Проверка на конец файла или ошибку чтения
        if (sym == EOF) {
            // Проверяем что именно произошло: кончился файл
            // или это ошибка чтения
            if (feof(fp) != 0) {
                printf(
                    "\nЧтение файла закончено\n"); //Если файл закончился, выводим сообщение о завершении чтения
                                                   //и выходим из бесконечного цикла
                break;
            } else {
                printf(
                    "\nОшибка чтения из файла\n"); //Если при чтении произошла ошибка, выводим сообщение об
                                                   // ошибке и выходим из бесконечного цикла
                break;
            }
        }

        if (sym == 61) // блок захвата числа коэффициентов
        {
            sym = fgetc(fp);
            {
                if (sym == 32) {
                    sym = fgetc(fp);
                    {
                        if (sym != 123) {
                            coef_num[i] = sym;
                            i++;
                            coef_num[i] = fgetc(fp);
                            i++;
                            while (coef_num[i - 1] != 59) // поиск символа  ";"
                            {
                                coef_num[i] = fgetc(fp);
                                i++;
                            }
                        }
                    }
                }
            }
        }

        //Если файл не закончился, и не было ошибки чтения
        //выводим код считанного символа на экран
        printf("%d ", sym);
    }

    // Закрываем файл и выводим число
    printf("\n");
    printf("\nЧисло коэффицинтов ASCII\n");
    printf("%d ", coef_num[0]);
    printf("%d ", coef_num[1]);
    printf("%d ", coef_num[2]);
    printf("%d ", coef_num[3]);
    printf("%d ", coef_num[4]);
    printf("%d ", coef_num[5]);

    printf("\n");
    printf("Закрытие файла: ");
    if (fclose(fp) == EOF)
        printf("ошибка\n");
    else
        printf("выполнено\n");

    coef_int = atoi(coef_num); // преобразуем число в int
    printf("Число коэффициентов в виде int: ");
    printf("%d\n", coef_int);

    printf("\nВведите размер коэффициента (в битах): "); // выводим сообщение
    scanf("%d", &coef_lengt);                            // вводим значения переменной coef_lengt
    printf("\nРазмер одного коэффициента coef_lengt=%d \n",
           coef_lengt); // выводим значение переменной coef_lengt

    coef_lengt_2 = (float) coef_lengt;

    while (coef_lengt_2 / 8 != 1.0 || coef_lengt_2 / 8 != 2.0 || coef_lengt_2 / 8 != 3.0
           || coef_lengt_2 / 8 != 4.0 || coef_lengt_2 / 8 != 5.0 || coef_lengt_2 / 8 != 6.0
           || coef_lengt_2 / 8 != 7.0 || coef_lengt_2 / 8 != 8.0 || coef_lengt_2 / 8 != 9.0
           || coef_lengt_2 / 8 != 10.0 || coef_lengt_2 / 8 != 11.0 || coef_lengt_2 / 8 != 12.0) {
        coef_lengt_2++;
        if (coef_lengt_2 / 8 == 1.0 || coef_lengt_2 / 8 == 2.0 || coef_lengt_2 / 8 == 3.0
            || coef_lengt_2 / 8 == 4.0 || coef_lengt_2 / 8 == 5.0 || coef_lengt_2 / 8 == 6.0
            || coef_lengt_2 / 8 == 7.0 || coef_lengt_2 / 8 == 8.0 || coef_lengt_2 / 8 == 9.0
            || coef_lengt_2 / 8 == 10.0 || coef_lengt_2 / 8 == 11.0 || coef_lengt_2 / 8 == 12.0) {
            break;
        }
    }

    char_number = (int) coef_lengt_2 / 8;

    printf("\nРазмер одного коэффициента в байтах char_number=%d \n", char_number);

    printf("\nЗапуск процедуры определения размера банка памяти\n");

    bank_size = coef_int / y;

    printf("\nгарантированное число коэф. в 1 банке = %d\n", bank_size);

    bank_size = bank_size * ((int) coef_lengt_2) / 8;

    printf("\nвсего байт задействовано в 1 банке = %d\n", bank_size);

    bank_size |= bank_size >> 1;
    bank_size |= bank_size >> 2;
    bank_size |= bank_size >> 4;
    bank_size |= bank_size >> 8;
    bank_size |= bank_size >> 16;

    printf("\nближайшая степень двойки (с учетом 0 ) = %d\n", bank_size);

    getchar();

    printf("\nопределение числа коэффициентов в файлах VMEM для дозаписи нулей в пустые ячейки\n");

    vmem_number_full = (bank_size + 1) / char_number;

    printf("\nвсего коэффициентов должно быть в каждом файле %d \n", vmem_number_full);

    vmem_number_full |= vmem_number_full >> 1;
    vmem_number_full |= vmem_number_full >> 2;
    vmem_number_full |= vmem_number_full >> 4;
    vmem_number_full |= vmem_number_full >> 8;
    vmem_number_full |= vmem_number_full >> 16;

    vmem_number_full = vmem_number_full + 1;

    printf("\nчисло коэффициентов в файлах VMEM с учетом нулевых = %d\n", vmem_number_full);

    printf("\nПовторное чтение файла с коэффициентами для поиска и записи коэффициентов \n");
    printf("\nЗапись коэффициентов в блоки размерами %d байт \n", bank_size);

    fp = fopen("fix_50bit_coef.h", "r");
    //Чтение (побайтно) данных из файла в бесконечном цикле
    while (1) {
        // Чтение одного байта из файла
        sym = fgetc(fp);

        //Проверка на конец файла или ошибку чтения
        if (sym == EOF) {
            // Проверяем что именно произошло: кончился файл
            // или это ошибка чтения
            if (feof(fp) != 0) {
                //Если файл закончился, выводим сообщение о завершении чтения
                //и выходим из бесконечного цикла
                printf("\nЧтение файла закончено\n");
                break;
            } else {
                //Если при чтении произошла ошибка, выводим сообщение об
                // ошибке и выходим из бесконечного цикла
                printf("\nОшибка чтения из файла\n");
                break;
            }
        }

        if (sym == 61) // блок захвата каждого коэффициента
        {
            sym = fgetc(fp);
            {
                if (sym == 32) {
                    sym = fgetc(fp);
                    {
                        if (sym == 123) {
                            for (i_counter = 0; i_counter < coef_int;) {
                                char coef_ascii[16] = {
                                    0}; // массив для буферизации каждого коэффициента
                                i = 0;
                                while (coef_ascii[i - 1] != 44) // поиск символа  ","
                                {
                                    coef_ascii[i] = fgetc(fp);
                                    if (coef_ascii[i] == 125) {
                                        break;
                                    }
                                    i++;
                                }
                                coef_alone_int = atoi(coef_ascii);

                                fwrite(&coef_alone_int, sizeof(char), char_number, fpw[i_file]);

                                i_file++;
                                i_counter++;

                                if (i_file == bank_num) // переключатель банка для записи
                                {
                                    i_file = 0;
                                }
                            }

                            i_file = 0;

                            for (i_nulls = 0;
                                 i_nulls < bank_num;) // цикл для дозаписи нулей в конец файла
                            {
                                fseek(fpw[i_file], 0, SEEK_END);

                                len = ftell(fpw[i_file]);
                                nulls_number = (bank_size + 1) - len;
                                for (i_nulls_write = 0; i_nulls_write < nulls_number;) {
                                    fwrite(&null, sizeof(char), 1, fpw[i_file]);
                                    i_nulls_write++;
                                }

                                i_nulls++;
                                i_file++;
                            }

                            getchar();
                        }
                    }
                }
            }
        }
    }

    for (bank_num = 0; bank_num < y;) // Функция создания файлов vmem
    {
        char filename[20];
        sprintf(filename, "coef%d.vmem", bank_num);
        fph[bank_num] = fopen(filename, "wb");

        bank_num++;
    }

    printf("\nСоздано %d файлов vmem \n", bank_num);

    for (i = 0; i < bank_num;) // Закрываем и сохраняем файлы
    {
        fclose(fpw[i]);
        i++;
    }

    for (bank_num = 0; bank_num < y;) // Функция открытия сохраненных файлов
    {
        char filename[20];
        sprintf(filename, "coef%d.bin", bank_num);
        fpw[bank_num] = fopen(filename, "rb");

        bank_num++;
    }

    i_file = 0; // предварительное обнуление переменных
    i = 0;
    i_counter = 0;

    sz = bank_size + 1; // блок преобразования bin2hex
    output_char = char_number * 2;

    for (i_file = 0; i_file < bank_num;) {
        i = 0;

        for (i_counter = 0; i_counter <= sz;) // цикл записи коэффициентов + нулей из бинарного файла

        {
            fwrite("@", sizeof(char), 1, fph[i_file]);

            adr = i / 8;

            bin2hex((char *) &adr, 8, bufout);

            fwrite(&bufout[8], sizeof(char), 8, fph[i_file]);

            fwrite(" ", sizeof(char), 1, fph[i_file]);

            fread(&bufin, sizeof(char), char_number, fpw[i_file]);

            bin2hex((char *) &bufin, char_number, bufout);

            fwrite(&bufout, sizeof(char), output_char, fph[i_file]);

            fwrite("\n", sizeof(char), 1, fph[i_file]);

            i = i + 8;
            i_counter = i_counter + char_number;
        }

        i_file++;
    }

    i = i / 8; // текущее число коэффициентов в кажом файле

    adr = i;

    for (i_file = 0; i_file < bank_num;) {
        i = adr;

        for (i; i < vmem_number_full;) //  цикл дозаписизаписи нулей в vmem файл.

        {
            fwrite("@", sizeof(char), 1, fph[i_file]);

            bin2hex((char *) &i, 8, bufout);

            fwrite(&bufout[8], sizeof(char), 8, fph[i_file]);

            fwrite(" ", sizeof(char), 1, fph[i_file]);

            bin2hex((char *) zero_buffer, output_char, bufout);

            fwrite(&bufout, sizeof(char), output_char, fph[i_file]);

            i++;

            if (i < vmem_number_full) {
                fwrite("\n",
                       sizeof(char),
                       1,
                       fph[i_file]); //  для того чтобы не возникало пустых строк в vmem файле.
            }
        }

        i_file++;
    }

    for (i = 0; i < bank_num;) {
        fclose(fpw[i]);
        fclose(fph[i]);
        i++;
    }

    printf("\n");
    printf("Закрытие файла: ");
    if (fclose(fp) == EOF)
        printf("ошибка\n");
    else
        printf("выполнено\n");

    getchar();
}

void bin2hex(char *bufin, unsigned int num, char *bufout)
{
    unsigned char ch;
    unsigned int i, j;

    j = (num - 1) << 1;

    for (i = 0; i < num; i++, j = j - 2) {
        ch = ((bufin[i] >> 4) & 0x0f) + 0x30;

        if (ch > 0x39)
            ch = ch + 7;

        bufout[j] = ch;

        ch = (bufin[i] & 0x0f) + 0x30;

        if (ch > 0x39)
            ch = ch + 7;

        bufout[j + 1] = ch;
    }

    return;
}