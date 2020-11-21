#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

void cmp_to_sort(char**, int, int);
void InsertSort(char**, int, int);
int atoi_sum(char*, int);
void SheikerSort(int*, char**, int);

int main()
{
	setlocale(LC_ALL, "Russian");
	int n, m, num = 0, var;
	char** str = 0;
	char** str1 = 0;                 //указатель на указатель для отладки программы
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
		str = (char**)calloc(n, sizeof(char*));            //выделяем память под массив указателей (строки текста)
		if (!str)
		{
			continue;
		}
		for (int i = 0; i < n; i++)
		{
			*(str + i) = (char*)malloc(m * sizeof(char));   //выделяем память под предложения текста
			if (!(*(str + i)))
			{
				for (int j = 0; j < i; j++)
				{
					printf_s("Reduce the line size");
					free(*(str + j));
				}
				free(str);
				str = 0;
				break;
			}
		}
		str1 = (char**)calloc(n, sizeof(char*));            //выделяем память под дополнительный массив указателей для отладки
		if (!str1)
		{
			continue;
		}
		for (int i = 0; i < n; i++)
		{
			*(str1 + i) = (char*)malloc(m * sizeof(char));   //выделяем память под предложения текста
			if (!(*(str1 + i)))
			{
				for (int j = 0; j < i; j++)
				{
					printf_s("Reduce the line size");
					free(*(str1 + j));
				}
				free(str1);
				str1 = 0;
				break;
			}
		}
	} while (!str && !str1);

	rewind(stdin);                         //чистка буфера ввода (чтобы не было нажатия ENTER)
	printf_s("Select: \n");
	printf_s("1. Take a ready - made string; \n");
	printf_s("2. Write yourself; \n");
	printf_s("Write your choice: ");
	scanf_s("%d", &var);
	switch (var)
	{
	case 1:
		*(str + 0) = "Ю.А. Алексов, 1. 10; 2. 11; 3. 12; 4. 13; 5. 14; 6. 20; 7. 30; 8. 41; 9. 42; 10. 32;";
		*(str + 1) = "К.Л. Иванов, 1. 11; 2. 15; 3. 17; 4. 20; 5. 41; 6. 52; 7. 36; 8. 49; 9. 48; 10. 37;";
		*(str + 2) = "В.К. Попов, 1. 9; 2. 8; 3. 7; 4. 60; 5. 40; 6. 50; 7. 70; 8. 80; 9. 42; 10. 32;";
		printf_s("%s \n", *(str + 0));
		printf_s("%s \n", *(str + 1));
		printf_s("%s \n", *(str + 2));
		printf_s("\n");
		for (int i = 0; i < n; i++)
		{
			if (*(str + i) == 0) break;
			strcpy_s(*(str1 + i), m, *(str + i));       //отладка программы
		}
		break;
	case 2:
		rewind(stdin);
		for (int i = 0; i < n; i++)
		{
			printf_s("Sentence # %d: ", i);
			fgets(*(str + i), m, stdin);
			printf_s("\n");
		}
		break;
	default: printf_s("Error");
		break;
	}

	cmp_to_sort(str1, n, m);
	puts("Sorted text by alphabet - \n");
	for (int i = 0; i < n; i++)
	{	
	    printf_s("%s \n", *(str1 + i));
	}
	printf_s("\n");
	for (int i = 0; i < n; i++)
	{
		printf_s("Total salary on line №%d - %d \n", i + 1, atoi_sum(*(str1 + i), m));
		num++;                   //счётчик количества сумм зарплат для выделения памяти под массив
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
		*(ms + i) = atoi_sum(*(str1 + i), m);
	}
	
	SheikerSort(ms, str1, num);
	printf_s("Sorted text by salary - \n");
	printf_s("\n");
	for (int i = 0; i < n; i++)
	{
		printf_s("Line with total salary %d - %s \n", atoi_sum(*(str1 + i), m), *(str1 + i));
	}

	for (int i = 0; i < n; i++)
	{
		free(*(str1 + i));
	}
	free(str1);
	return 0;
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
	if (*(st + i) == ' ') i++;
	if (!st) return 0;                          //прерываем работу функции (строка содержит только пробелы)
	for (i ; i < s_stl; i++)
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
		if (*(st + i) == '\0') break;     //прекращаем цикл, если достигнут нулевой цикл
	}

	return sum;
	
}
//цикл сортировки строк строкового массива по сумме зарплат
void SheikerSort(int* arr, char** st, int kol)
{
	int left = 0, right = kol - 1, temp;
	int flag = 1;                     //флаг наличия перемещений
	while ((left < right) && flag)
	{
		flag = 0;
		for (int i = left; i < right; i++)
		{
			if (*(arr + i) > *(arr + i + 1))
			{
				temp = *(arr + i);
				*(arr + i) = *(arr + i + 1);
				*(arr + i + 1) = temp;

				temp = *(st + i);
				*(st + i) = *(st + i + 1);
				*(st + i + 1) = temp;

				flag = 1;	
			}
		}
		right--;
		for (int i = right; i > left; i--)
		{
			if (*(arr + i - 1) > *(arr + i))
			{
				temp = *(arr + i);
				*(arr + i) = *(arr + i - 1);
				*(arr + i - 1) = temp;

				temp = *(st + i);
				*(st + i) = *(st + i - 1);
				*(st + i - 1) = temp;
			}
		}
		left--;
	}

}