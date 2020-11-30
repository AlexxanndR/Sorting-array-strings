#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <windows.h>

void cmp_to_sort(char**, int, int);
void InsertSort(char**, int, int);
int  atoi_sum(char*, int);
void SheikerSort(int*, char**, int);
char* str_cpy(char*, char*);

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n, m, num = 0, var, kol = 0;
	char** str_old = 0;
	char** str_new = 0;                 //указатель на указатель для отладки программы
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
		str_new = (char**)calloc(n, sizeof(char*));            //выделяем память под дополнительный массив указателей для отладки
		if (!str_new)
		{
			continue;
		}
		for (int i = 0; i < n; i++)
		{
			*(str_new + i) = (char*)malloc(m * sizeof(char));   //выделяем память под предложения текста
			if (!(*(str_new + i)))
			{
				for (int j = 0; j < i; j++)
				{
					printf_s("Reduce the line size");
					free(*(str_new + j));
				}
				free(str_new);
				str_new = 0;
				break;
			}
		}
	} while (!str_old && !str_new);

	rewind(stdin);                         //чистка буфера ввода (чтобы не было нажатия ENTER)


	for (int i = 0; i < n; i++)
	{
		if (kol > 20 && i == 1)
		{
			printf_s("\n");
			puts("The number of months must be no more than 20. \n");
			rewind(stdin);
			i = 0;
		}
		printf_s("Enter the string #%d: ", i + 1);
		kol = get_str(*(str_old + i), m);
		if (kol > 20 && i > 0)
		{
			printf_s("\n");
			puts("The number of months must be no more than 20 \n");
			rewind(stdin);
			i--;
		}
	}

	//for (int i = 0; i < n; i++)
	//{
	//	printf_s("Sentence # %d: ", i + 1);
	//	fgets(*(str_old + i), m, stdin);

	//	for (int j = 0; j < m; j++)
	//	{
	//		if (*(*(str_old + i) + j) == '.') kol++;
	//		if (kol > 20 && i == 0)
	//		{
	//			rewind(stdin);
	//			i = 0;
	//			break;
	//		}
	//	    if (kol > 20 && i > 0)
	//		{
	//			rewind(stdin);
	//			i--;
	//			break;
	//		}
	//	}
	//}
	printf_s("\n");



	cmp_to_sort(str_old, n, m);
	puts("Sorted text by alphabet - \n");
	for (int i = 0; i < n; i++)
	{	
	    printf_s("%s \n", *(str_old + i));
	}
	printf_s("\n");
	for (int i = 0; i < n; i++)
	{
		if (*(str_old + i) == 0) break;
		printf_s("Total salary on line №%d - %d \n", i + 1, atoi_sum(*(str_old + i), m));
		num++;                               //счётчик количества сумм зарплат для выделения памяти под массив
	}
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
		if (*(str_old + i) == 0) break;
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
	}
	*(st + i) = '\0';
	return kol; 
}

char* str_cpy(char* st_new, char* st_old)
{
	while ((*st_new++ = *st_old++) != '\0');

	return st_new;
}

void InsertSort(char** st, int j1, int i1)
{
	int i, j, temp;

	for (i = i1 + 1; i > 0; i--)
	{
		j = i - 1;
		temp = *(st + i);              //сохраняем указатель на строку, которую отправляем в функцию
		while (j >= 0 && (*(*(st + j) + j1) - *(*(st + i) + j1)) > 0)
		{

			*(st + j-- + 1) = *(st + j);
			j1 = 0;                     //устанавливаем j в начало строки для нового прохода по их элементам
			while (j >= 0 && *(*(st + j) + j1) == *(*(st + i - 1) + j1))  //цикл поиска одинаковых элементов в строках
			{
				j1++;
			}
		}
		*(st + j + 1) = temp;
	}
}

void cmp_to_sort(char** st, int s_str, int s_stl)
{
	for (int i = 0; i < s_str - 1; i++)
	{
		for (int j = 0; j < s_stl - 1; j++)
		{
			if (*(*(st + i) + j) == *(*(st + i + 1) + j))
			{
				continue;
			}
			else
			{
				InsertSort(st, j, i);
				break;
			}
		}
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
		if (*(st + i) == ' ') continue;
		if (*(st + i) >= '0' && *(st + i) <= '9')
		{
			n = n * 10 + (*(st + i) - '0');
		}
		if (*(st + i) == '.') n = 0;      //обнуляем число, если оно обозначает номер месяца
		if (*(st + i) == ';') next = 1;   //найдено число зарплаты за один из месяцев
		if (next)
		{
			sum += n;
			n = 0;                        //обнуление зарплаты для суммирования с зарплатой за другой месяц
		}
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