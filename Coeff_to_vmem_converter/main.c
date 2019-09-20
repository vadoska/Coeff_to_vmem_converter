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
    char bank_num;          // ����� ������ ������
    int coef_int;           // ����� ����� ������������ ����� atoi
    int coef_lengt;         // ������ ������ ����. � �����
    float coef_lengt_2 = 0; // ������ ������ ����. � ����� � ������� ������
    int char_number;        // ������ ������ ��� ������ � ���� �������� fwrite
    int i = 0;
    int i_counter = 0; // ������� ���������� ������� ������������
    int i_file = 0;    // ������� ��� ������ ������
    int i_nulls;       // ������� ����� ��� �������� � ����
    int i_nulls_write; // ������� ������ ����� � ������ ����
    int nulls_number;  // ����� �����
    char null = 0;     // ���������� ����
    int sym;
    char coef_num[6];
    char *num = coef_num;
    unsigned long len;    // ������ ����� ��� �����
    int vmem_number_full; // ����� ������������ � ����� vmem � ������ ������������ �����

    signed long long int coef_alone_int; // �����, ������ ���������� ����� atoi

    int bank_size;

    char zero_buffer[20]
        = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // ����� ��� ������ ����� � ����� �����
    char bufin[20]; // ������ ���������� �� ������� �������������� bin hex
    char bufout[100];
    int adr = 0x00000000;
    int sz;
    int output_char; // ����� �������� �������� � vmem �����

    system("chcp 1251");                     // ��������� � ������� �� ������� ����
    system("cls");                           // ������� ���� �������
    printf("������� ����� ������ ������: "); // ������� ���������
    scanf("%d", &y);                         // ������ �������� ���������� y
    printf("����� ������ y=%d \n", y);       // ������� �������� ���������� y

    for (bank_num = 0; bank_num < y;) // ������� �������� ������
    {
        char filename[20];
        sprintf(filename, "coef%d.bin", bank_num);
        fpw[bank_num] = fopen(filename, "wb");

        bank_num++;
    }

    printf("\n������� %d ������ \n", bank_num);

    printf("\n��������� ������������ ����� � ��������������?\n");

    printf("\n����� ����� ������\n");

    getchar();
    getchar();

    fp = fopen("fix_50bit_coef.h", "r"); // ��������� ���� �� ������
                                         //������ (��������) ������ �� ����� � ����������� �����
    while (1) {
        // ������ ������ ����� �� �����
        sym = fgetc(fp);

        //�������� �� ����� ����� ��� ������ ������
        if (sym == EOF) {
            // ��������� ��� ������ ���������: �������� ����
            // ��� ��� ������ ������
            if (feof(fp) != 0) {
                printf(
                    "\n������ ����� ���������\n"); //���� ���� ����������, ������� ��������� � ���������� ������
                                                   //� ������� �� ������������ �����
                break;
            } else {
                printf(
                    "\n������ ������ �� �����\n"); //���� ��� ������ ��������� ������, ������� ��������� ��
                                                   // ������ � ������� �� ������������ �����
                break;
            }
        }

        if (sym == 61) // ���� ������� ����� �������������
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
                            while (coef_num[i - 1] != 59) // ����� �������  ";"
                            {
                                coef_num[i] = fgetc(fp);
                                i++;
                            }
                        }
                    }
                }
            }
        }

        //���� ���� �� ����������, � �� ���� ������ ������
        //������� ��� ���������� ������� �� �����
        printf("%d ", sym);
    }

    // ��������� ���� � ������� �����
    printf("\n");
    printf("\n����� ������������ ASCII\n");
    printf("%d ", coef_num[0]);
    printf("%d ", coef_num[1]);
    printf("%d ", coef_num[2]);
    printf("%d ", coef_num[3]);
    printf("%d ", coef_num[4]);
    printf("%d ", coef_num[5]);

    printf("\n");
    printf("�������� �����: ");
    if (fclose(fp) == EOF)
        printf("������\n");
    else
        printf("���������\n");

    coef_int = atoi(coef_num); // ����������� ����� � int
    printf("����� ������������� � ���� int: ");
    printf("%d\n", coef_int);

    printf("\n������� ������ ������������ (� �����): "); // ������� ���������
    scanf("%d", &coef_lengt);                            // ������ �������� ���������� coef_lengt
    printf("\n������ ������ ������������ coef_lengt=%d \n",
           coef_lengt); // ������� �������� ���������� coef_lengt

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

    printf("\n������ ������ ������������ � ������ char_number=%d \n", char_number);

    printf("\n������ ��������� ����������� ������� ����� ������\n");

    bank_size = coef_int / y;

    printf("\n��������������� ����� ����. � 1 ����� = %d\n", bank_size);

    bank_size = bank_size * ((int) coef_lengt_2) / 8;

    printf("\n����� ���� ������������� � 1 ����� = %d\n", bank_size);

    bank_size |= bank_size >> 1;
    bank_size |= bank_size >> 2;
    bank_size |= bank_size >> 4;
    bank_size |= bank_size >> 8;
    bank_size |= bank_size >> 16;

    printf("\n��������� ������� ������ (� ������ 0 ) = %d\n", bank_size);

    getchar();

    printf("\n����������� ����� ������������� � ������ VMEM ��� �������� ����� � ������ ������\n");

    vmem_number_full = (bank_size + 1) / char_number;

    printf("\n����� ������������� ������ ���� � ������ ����� %d \n", vmem_number_full);

    vmem_number_full |= vmem_number_full >> 1;
    vmem_number_full |= vmem_number_full >> 2;
    vmem_number_full |= vmem_number_full >> 4;
    vmem_number_full |= vmem_number_full >> 8;
    vmem_number_full |= vmem_number_full >> 16;

    vmem_number_full = vmem_number_full + 1;

    printf("\n����� ������������� � ������ VMEM � ������ ������� = %d\n", vmem_number_full);

    printf("\n��������� ������ ����� � �������������� ��� ������ � ������ ������������� \n");
    printf("\n������ ������������� � ����� ��������� %d ���� \n", bank_size);

    fp = fopen("fix_50bit_coef.h", "r");
    //������ (��������) ������ �� ����� � ����������� �����
    while (1) {
        // ������ ������ ����� �� �����
        sym = fgetc(fp);

        //�������� �� ����� ����� ��� ������ ������
        if (sym == EOF) {
            // ��������� ��� ������ ���������: �������� ����
            // ��� ��� ������ ������
            if (feof(fp) != 0) {
                //���� ���� ����������, ������� ��������� � ���������� ������
                //� ������� �� ������������ �����
                printf("\n������ ����� ���������\n");
                break;
            } else {
                //���� ��� ������ ��������� ������, ������� ��������� ��
                // ������ � ������� �� ������������ �����
                printf("\n������ ������ �� �����\n");
                break;
            }
        }

        if (sym == 61) // ���� ������� ������� ������������
        {
            sym = fgetc(fp);
            {
                if (sym == 32) {
                    sym = fgetc(fp);
                    {
                        if (sym == 123) {
                            for (i_counter = 0; i_counter < coef_int;) {
                                char coef_ascii[16] = {
                                    0}; // ������ ��� ����������� ������� ������������
                                i = 0;
                                while (coef_ascii[i - 1] != 44) // ����� �������  ","
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

                                if (i_file == bank_num) // ������������� ����� ��� ������
                                {
                                    i_file = 0;
                                }
                            }

                            i_file = 0;

                            for (i_nulls = 0;
                                 i_nulls < bank_num;) // ���� ��� �������� ����� � ����� �����
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

    for (bank_num = 0; bank_num < y;) // ������� �������� ������ vmem
    {
        char filename[20];
        sprintf(filename, "coef%d.vmem", bank_num);
        fph[bank_num] = fopen(filename, "wb");

        bank_num++;
    }

    printf("\n������� %d ������ vmem \n", bank_num);

    for (i = 0; i < bank_num;) // ��������� � ��������� �����
    {
        fclose(fpw[i]);
        i++;
    }

    for (bank_num = 0; bank_num < y;) // ������� �������� ����������� ������
    {
        char filename[20];
        sprintf(filename, "coef%d.bin", bank_num);
        fpw[bank_num] = fopen(filename, "rb");

        bank_num++;
    }

    i_file = 0; // ��������������� ��������� ����������
    i = 0;
    i_counter = 0;

    sz = bank_size + 1; // ���� �������������� bin2hex
    output_char = char_number * 2;

    for (i_file = 0; i_file < bank_num;) {
        i = 0;

        for (i_counter = 0; i_counter <= sz;) // ���� ������ ������������� + ����� �� ��������� �����

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

    i = i / 8; // ������� ����� ������������� � ����� �����

    adr = i;

    for (i_file = 0; i_file < bank_num;) {
        i = adr;

        for (i; i < vmem_number_full;) //  ���� �������������� ����� � vmem ����.

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
                       fph[i_file]); //  ��� ���� ����� �� ��������� ������ ����� � vmem �����.
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
    printf("�������� �����: ");
    if (fclose(fp) == EOF)
        printf("������\n");
    else
        printf("���������\n");

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