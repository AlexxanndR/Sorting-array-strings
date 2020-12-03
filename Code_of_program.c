#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <windows.h>
#include <stdbool.h>

void skipSpace(char**, char*, int, int, int*, int*);
void InsertSort(char**, int, int);
int  atoi_sum(char*, int);
void SheikerSort(int*, char**, int);

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n, m, num = 0, var, kol = 0;
	char** str_old = 0;
	int* ms = 0;
	do
	{
		system("CLS");
		printf_s("Enter the number of the sentences: ");
		if (!(scanf_s("%d", &n)))
		{
			rewind(stdin);
			continue;
		}
		printf_s("Allocate memory for the sentence: ");
		if (!(scanf_s("%d", &m)))
		{
			rewind(stdin);
			continue;
		}
		str_old = (char**)calloc(n, sizeof(char*));            //выделяем память под массив указателей (строки текста)
		if (!str_old)
		{
			free(str_old);
			continue;
		}
		for (int i = 0; i < n; i++)
		{
			*(str_old + i) = (char*)malloc(m * sizeof(char));   //выделяем память под предложения текста
			if (!(*(str_old + i)))
			{
				for (int j = 0; j < i; j++)
				{
					printf_s("Reduce the line size");
					free(*(str_old + j));
				}
				free(str_old);
				str_old = 0;
				break;
			}
		}
	} while (!str_old);

	rewind(stdin);                         //чистка буфера ввода (чтобы не было учтено на;атие ENTER при вводе строк)

	for (int i = 0; i < n; i++)
	{
		if (kol > 20 && i == 1)           //если введена зарплата для более 20 месяцев и было введено 1-ое предложение
		{                                 //то делаем повторный ввод
			printf_s("\n");
			puts("The number of months must be no more than 20. \n");
			rewind(stdin);
			i = 0;
		}
		printf_s("Enter the string #%d: ", i + 1);
		kol = get_str(*(str_old + i), m);
		if (kol > 20 && i > 0)            //если введена зарплата для более 20 месяцев и было введено не 1-ое предложение
		{                                 //то делаем повторный ввод этого предложения
			printf_s("\n");
			puts("The number of months must be no more than 20 \n");
			rewind(stdin);
			i--;
		}
	}

	printf_s("\n");

	InsertSort(str_old, n, m);
	puts("Sorted text by alphabet - \n");
	for (int i = 0; i < n; i++)
	{	
	    printf_s("%s \n", *(str_old + i));
	}
	printf_s("\n");
	for (int i = 0; i < n; i++)
	{
		printf_s("Total salary on line №%d - %d \n", i + 1, atoi_sum(*(str_old + i), m));
		num++;                               //счётчик количества сумм зарплат для выделения памяти под массив для сортировки
	}                                        //по сумме зарплат 
	printf_s("\n");
	ms = (int*)malloc(num * sizeof(int));   //выделение памяти пол дополнительный массив
	if (!ms)                                //проверка выделения памяти
	{
		puts("Memory is not alocated.");
		return 1;
	}
	//цикл заполнения массива
	for (int i = 0; i < n; i++)
	{
		*(ms + i) = atoi_sum(*(str_old + i), m);
	}
	
	SheikerSort(ms, str_old, num);
	printf_s("Sorted text by salary - \n");
	printf_s("\n");
	for (int i = 0; i < n; i++)
	{
		printf_s("Line with total salary %d - %s \n", atoi_sum(*(str_old + i), m), *(str_old + i));
	}

	for (int i = 0; i < n; i++)
	{
		free(*(str_old + i));
	}
	free(str_old);
	return 0;
}

int get_str(char* st, int num)
{
	char c = 0;
	int i = 0, kol = 0;
	while (--num > 0 && (c = getchar()) != EOF && c != '\n')
	{
		*(st + i++) = c;
		if (c == '.') kol++;
		else if ((*(st + i - 2) >= '0' && *(st + i - 2) <= '9') && (*(st + i - 1) == ' ' || *(st + i - 1) == '\n')) kol++; //если введена цифра
		                                                                                                               //а после неё пробел, то
	}                                                                                                                  //то найдена зарплата
	*(st + i) = '\0';                                                                                  
	return kol; 
}
//функция расстановки сим-ов в строках, если встретились лишние пробелы, чтобы их не сортировать с буквами
void skipSpace(char** st, char * temp, int j, int i, int* symb, int* lett)
{
	while (*(*(st + j) + *symb) != ' ' && *(temp + (*symb)) == ' ')
	{
		*lett = *symb; (*symb)++;
	}
	while (*(*(st + j) + *symb) == ' ' && *(temp + (*symb)) != ' ')
	{
		*lett = *symb; (*symb)++;
	}
}

void InsertSort(char** st, int s_str, int str_size)
{
	int i, j, symb = 0, lett = 0;
	char *temp, temp_s;

	for (i = 1; i < s_str; i++)
	{
		j = i - 1;
		temp = *(st + i);              //сохраняем указатель на строку
		while (*(*(st + j) + symb) == *(*(st + i) + symb)) symb++;  //пропуск одинаковых символов
		if (*(*(st + j) + symb) >= '0' && *(*(st + j) + symb) <= '9') symb++; //достигнуты цифры в строке
		if (*(*(st + i) + symb) >= '0' && *(*(st + i) + symb) <= '9') symb++; //достигнуты цифры в другой строке
		lett = symb;
		skipSpace(st, temp, j, i, &symb, &lett);   //пропуск пробелов в одной из строк
		while (j >= 0 && (*(*(st + j) + lett) - *(temp + symb) > 0))
		{
			*(st + j-- + 1) = *(st + j);
			symb = 0; lett = 0;                    //устанавливаемся в начало строки для нового прохода по их элементам
			while (j >= 0 && *(*(st + j) + lett) == *(temp + symb))     //цикл поиска одинаковых элементов в строках
			{                                                           //т.к. начинают сравниваються строки, в которых
				symb++; lett++;                                         //символы под установленным номером, могут быть уже не одинаковыми
				skipSpace(st, temp, j, i, &symb, &lett);                //пропуск пробелов в одной из строк
			}
		}
		*(st + j + 1) = temp; //запись в освободившийся или в тот же элемент
		symb = 0; lett = 0;
	}
}

int atoi_sum(char* st, int s_stl)
{
	int i = 0, n = 0, sum = 0;
	int numl = 0;
	bool next = 0;                              //флаг прохола в массиве зарплаты за один месяца
	while (*(st + i) == ' ') i++;
	if (!st) return 0;                          //прерываем работу функции (строка содержит только пробелы)
	for (i = 0 ; i < s_stl; i++)
	{
		next = 0;
		if (*(st + i) >= 'A' && *(st + i) <= 'z') continue; 
		if (*(st + i) >= 'A' && *(st + i) <= 'я') continue;
		if (*(st + i) >= '0' && *(st + i) <= '9')
		{
			n = n * 10 + (*(st + i) - '0');
		}
		if (*(st + i) == '.') n = 0;      //обнуляем число, если оно обозначает номер месяца
		if (*(st + i) == ';' || *(st + i) == ' ' || *(st + i) == '\0' || *(st + i) == '\n')
		{
			if (*(st + i - 1) >= '0' && *(st + i - 1) <= '9') next = 1;   //найдено число зарплаты за один из месяцев
		}
		if (next)
		{
			sum += n;
			n = 0;                        //обнуление зарплаты для суммирования с зарплатой за другой месяц
		}
		if (*(st + i) == ' ') continue;
		if (*(st + i) == '\0') break;     //прекращаем цикл, если достигнут нулевой символ
	}

	return sum;
	
}
//цикл сортировки строк строкового массива по сумме зарплат
void SheikerSort(int* arr, char** st, int kol)
{
	int left = 0, right = kol - 1, temp_dg;
	char* temp_str;
	int flag = 1;                         //флаг наличия перемещений
	while ((left < right) && flag)
	{
		flag = 0;
		for (int i = left; i < right; i++)
		{
			if (*(arr + i) > *(arr + i + 1))
			{
				temp_dg = *(arr + i);
				*(arr + i) = *(arr + i + 1);
				*(arr + i + 1) = temp_dg;

				temp_str = *(st + i);
				*(st + i) = *(st + i + 1);
				*(st + i + 1) = temp_str;

				flag = 1;	
			}
		}
		right--;
		for (int i = right; i > left; i--)
		{
			if (*(arr + i - 1) > *(arr + i))
			{
				temp_dg = *(arr + i);
				*(arr + i) = *(arr + i - 1);
				*(arr + i - 1) = temp_dg;

				temp_str = *(st + i);
				*(st + i) = *(st + i - 1);
				*(st + i - 1) = temp_str;
				flag = 1;
			}
		}
		left++;
	}

}