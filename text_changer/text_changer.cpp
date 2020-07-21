// text_changer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// Лабораторная работа №1. 
// Задан текст. В каждом слове текста оставить на своих местах первую и последнюю буквы, а в середине слова буквы перемешать
// Студенты группы 465, Лубенец Георгий Николаевич, Копелев А.О.  2019 год 

#include <iostream>
#include <windows.h>
#include <string>
#include <cmath>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <filesystem>
#include "Interface.h"

using namespace std;
int main()
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	setlocale(LC_ALL, "Russian");
	cout << "Лабораторная работа №1"<< endl
		<<"Задан текст. В каждом слове текста оставить на своих местах первую и" << endl
		<<"последнюю буквы, а в середине слова буквы перемешать"<< endl
		<<"Студенты группы 465 Лубенец Г.Н., Копелев А.О.  2019 год " << endl;
	InterfaceMenu();
	return 0;
}

