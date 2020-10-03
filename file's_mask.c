/*
Миша готовится к ЕГЭ по информатике. Сейчас он изучает задачу A4, в которой описывается работа с масками файлов:

Для групповых операций с файлами используются маски имён файлов. Маска представляет собой последовательность букв, цифр и прочих допустимых в именах файлов символов, в которой также могут встречаться следующие символы.

Символ «?» (вопросительный знак) означает ровно один произвольный символ.

Символ «*» (звёздочка) означает любую последовательность символов произвольной длины, в том числе «*» может задавать и пустую последовательность.

Поскольку открытого банка задач для ЕГЭ по информатике не существует, Мише приходится тренироваться самостоятельно. Напишите программу, которая для каждого имени файла определит, подходит ли оно под заданную маску, чтобы Миша мог сверить свои ответы. Гарантируется, что в маске файла присутствует не более одного символа «*».

ВХОДНЫЕ ДАННЫЕ
 

В первой строке содержится маска файла. В следующих 5 строках содержатся имена файлов по одному в строке. Имена файлов состоят из маленьких латинских букв, цифр и символа «.» (точка), в маске также могут содержаться символы «?» и «*» (символ «*» — не более одного раза). Длина каждой строки не превосходит 20 символов.

ВЫХОДНЫЕ ДАННЫЕ
 

Для каждого имени файла выведите слово «YES» если оно удовлетворяет маске и «NO» иначе. Выводить слова следует большими латинскими буквами без кавычек, каждое в новой строке.

 

ввод	вывод

?or*.d??
fort.doc
ford.doc
lord2.doc
orsk.dat
port

YES
YES
YES
NO
NO

*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool check (const char* _Mask, size_t _MSize, const char* _String, size_t _StrSize)
{
	int mi = 0, stri = 0, starStop = 0;

	while (mi < _MSize && stri < _StrSize)
	{
		switch (_Mask[mi])
		{
		case '?':
			mi++, stri++;
			break;

		case '*':
			starStop = stri;
			goto STAR;

		default:
			if (_String[stri++] != _Mask[mi++])
				return false;
			break;
		}
	}

	return stri == _StrSize && mi == _MSize;

STAR: mi = (int)_MSize - 1, stri = (int)_StrSize - 1;

	while (_Mask[mi] != '*' && stri >= starStop)
	{
		switch (_Mask[mi])
		{
		case '?':
			mi--, stri--;
			break;

		default:
			if (_String[stri--] != _Mask[mi--])
				return false;
			break;
		}
	}

	return _Mask[mi] == '*' && stri >= starStop - 1;
}

int main()
{
	char mask[20];
	fgets(mask, 20, stdin);
	const size_t sizem = strlen(mask) - 1;

	for (int i = 0; i < 5; i++)
	{
		char string[20];
		fgets(string, 20, stdin);
		puts(check(mask, sizem, string, strlen(string) - 1) ? "YES" : "NO");
	}

	return 0;
}