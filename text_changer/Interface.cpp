#include <fstream>
#include <filesystem>
#include "Interface.h"
#include "Algorithm.h"
using namespace std::experimental::filesystem::v1;
using namespace std;
enum Dialog { Yes = 1, No, SaveData, SaveResult };
enum ExceptionType { InvalidArg, NegativArg, InvalidName, FileNotExist, Error };

// Исключения;
class Exception
{
	int num;
	char *str;
public:
	Exception(int num, char *str) {
		this->num = num;
		this->str = str;
	}
	// Вывод исключения;
	void display() {
		cout << "Exception - #" << num << ", "
			<< str << endl;
	}
};
vector<string> splitText(const string& s, char delimiter = '\n')
{
	vector<string> tokens;
	string token;
	istringstream tokenStream(s);

	while (getline(tokenStream, token, delimiter))
		tokens.push_back(token);

	return tokens;
}

vector<string> splitString(const string& s, char delimiter = ' ')
{
	vector<string> tokens;
	string token;
	istringstream tokenStream(s);

	while (getline(tokenStream, token, delimiter))
		tokens.push_back(token);

	return tokens;
}

string uniteText(const vector<string> & textStrings)
{
	string result;
	for (const auto & textString : textStrings)
	{
		result.append(textString);
		result.push_back('\n');
	}
	result.pop_back();
	return result;
}
string uniteString(const vector<string> & textStrings)
{
	string result;
	for (const auto & textString : textStrings)
	{
		result.append(textString);
		//result.push_back(' ');
	}
	result.pop_back();
	return result;
}
//тест на правильность работы алгоритма
void test1() {
	string text = "Hello";
	bool isAlright = true;
	try {
		auto textStrings = splitString(text);
		for (auto & textString : textStrings) {
			WordChange(textString);
		}
		text = uniteString(textStrings);
	}
	catch(Exception e){
		isAlright = false;
		cout << "Тест 1 не прошел" << endl;
		e.display();
	}
	
	if (isAlright && text[0]=='H' && text[4]=='o') {
		cout << "Тест 1 успешной пройден" << endl;
	}else
		cout << "Тест 1 не прошел" << endl;

}
//тест на нахождение и пропускание знаков препинания и др.символов на конце слов
void test2() {
	string text = "Hello!";
	bool isAlright = true;
	try {
		auto textStrings = splitString(text);
		for (auto & textString : textStrings) {
			WordChange(textString);
		}
		text = uniteString(textStrings);
	}
	catch (Exception e) {
		isAlright = false;
		
		e.display();
	}

	if (isAlright && text[0] == 'H' && text[4] == 'o') {
		cout << "Тест 2 успешной пройден" << endl;
	}else
		cout << "Тест 2 не прошел" << endl;

}
//тест на пробелы между словами
void test3() {
	string text = "Hello World";
	bool isAlright = true;
	try {
		auto textStrings = splitString(text);
		for (auto & textString : textStrings) {
			WordChange(textString);
		}
		text = uniteString(textStrings);
	}
	catch (Exception e) {
		isAlright = false;
		cout << "Тест 3 не прошел" << endl;
		e.display();
	}

	if (isAlright && text[0] == 'H' && text[4] == 'o' && text[10] == 'd') {
		cout << "Тест 3 успешной пройден" << endl;
	}else
		cout << "Тест 3 не прошел" << endl;

}
void InterfaceMenu() {
	int answ;
	int exit = 1;
	while (exit == 1) {
		cout << "------------------------------" << endl;
		cout << "(1) задать текст с клавиатуры!" << endl;
		cout << "(2) задать текст из файла" << endl;
		cout << "(3) запустить модульные тесты" << endl;
		cout << "(4) для выхода из программы" << endl;
		answ = ValidateValue();
		enum menu {
			a = 1,
			b,
			c,
			d
		};
		switch (answ) {
		case (a): {
			string tmp; //запись исходных данных
			string text; // переменная для работы с текстом
			cout << "Введите текст и нажмите Enter" << endl;
				try {
					tmp = ValidateString();
					if (tmp.length() == 0 || tmp[0] == ' ') {
						cout << "Ошибка: Пустой ввод" << endl;
						break;
					}
					text = tmp;
					auto textStrings = splitString(text);
					for (auto & textString : textStrings) {
						WordChange(textString);
					}
					text = uniteString(textStrings);
					cout << text;
					SData(text, tmp); //предлагаем сохранить результат
				}
				catch (Exception e) {
					e.display();
				}
				break;
		}
		case (b): {
			ifstream file; // открыть файл на чтение
			string name; //имя файла
			string text; //текст из файла
			string tmp; //запись исходных данных
			bool isAlright = true;
			int ans1; //переменная для записи ответа
			int ans2; //переменная для записи ответа
				try {
						cout << "Введите адрес файла для ввода данных ";
						cin >> name;    // создать поточный объект file
						if (is_regular_file(name)) {
							file.open(name);// открыть файл на чтение
							if (file.good()) {
								bool is_result = false;
								do {
									size_t count = 0; //Число символов в файле
									char S; //для подсчета символов

									/*Просто считаем число символов*/
									ifstream f(name);
									while (!f.eof())
									{
										f.get(S);
										count++;
									}
									f.close();
									
									/*Добавляем текст в переменную*/

									char *S2 = new char[count]; //Выделяем память по определенному числу символов
									for (int i = 0; i < count; i++) S2[i] = NULL; //Очищаем строку от хлама
									ifstream f2(name);  //создаем поток для работы с файлом
									int i = 0; //куроср на текущий символ (как номер буквы в слове)
									while (!f2.eof()) //Проходим ао файлу
									{
										f2.get(S2[i]); //Записываем символ за символом 
										i++; //передвинули курсор для записи следующего символа
									}
									text += S2;
									if (text.length() == 0 || text[0] == ' ') {
										cout << "Ошибка: Пустой ввод" << endl;
										break;
									}
									tmp = text;
									auto textStrings = splitText(text);
									for (auto & textString : textStrings) {
										auto tmp_textString = splitString(textString);
										for (auto & word : tmp_textString) {
											WordChange(word);
										}
										textString = uniteString(tmp_textString);
									}
									
									cout << S2 << endl; //Теперь переменная char[] содержит текст из файла
									text = uniteText(textStrings);
									cout << "\n" << text;
									cin.sync(); cin.get();
									f2.close(); //закончили работу с файлом
									delete[]S2; //освобождаем память
									SData(text, tmp); //предлагаем сохранить результат
									is_result = true;
								} while (!is_result);
							}
							else {
								cout << "Файл с таким именем не существует" << endl;
								break;
							}
						}
						else {
							isAlright = false;
							throw Exception(FileNotExist, (char*)"Файл не существует");
							break;
						}
				}
				catch (Exception e) {
					file.close();
					e.display();
				}
			break;
		}
		case (c): {
			test1();
			test2();
			test3();
			break;
		}
		case (d): {
			exit = 0;
		}
		default: {
			break;
			}
		}
	}
}