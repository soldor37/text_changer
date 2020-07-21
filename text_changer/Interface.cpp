#include <fstream>
#include <filesystem>
#include "Interface.h"
#include "Algorithm.h"
using namespace std::experimental::filesystem::v1;
using namespace std;
enum Dialog { Yes = 1, No, SaveData, SaveResult };
enum ExceptionType { InvalidArg, NegativArg, InvalidName, FileNotExist, Error };

// ����������;
class Exception
{
	int num;
	char *str;
public:
	Exception(int num, char *str) {
		this->num = num;
		this->str = str;
	}
	// ����� ����������;
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
//���� �� ������������ ������ ���������
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
		cout << "���� 1 �� ������" << endl;
		e.display();
	}
	
	if (isAlright && text[0]=='H' && text[4]=='o') {
		cout << "���� 1 �������� �������" << endl;
	}else
		cout << "���� 1 �� ������" << endl;

}
//���� �� ���������� � ����������� ������ ���������� � ��.�������� �� ����� ����
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
		cout << "���� 2 �������� �������" << endl;
	}else
		cout << "���� 2 �� ������" << endl;

}
//���� �� ������� ����� �������
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
		cout << "���� 3 �� ������" << endl;
		e.display();
	}

	if (isAlright && text[0] == 'H' && text[4] == 'o' && text[10] == 'd') {
		cout << "���� 3 �������� �������" << endl;
	}else
		cout << "���� 3 �� ������" << endl;

}
void InterfaceMenu() {
	int answ;
	int exit = 1;
	while (exit == 1) {
		cout << "------------------------------" << endl;
		cout << "(1) ������ ����� � ����������!" << endl;
		cout << "(2) ������ ����� �� �����" << endl;
		cout << "(3) ��������� ��������� �����" << endl;
		cout << "(4) ��� ������ �� ���������" << endl;
		answ = ValidateValue();
		enum menu {
			a = 1,
			b,
			c,
			d
		};
		switch (answ) {
		case (a): {
			string tmp; //������ �������� ������
			string text; // ���������� ��� ������ � �������
			cout << "������� ����� � ������� Enter" << endl;
				try {
					tmp = ValidateString();
					if (tmp.length() == 0 || tmp[0] == ' ') {
						cout << "������: ������ ����" << endl;
						break;
					}
					text = tmp;
					auto textStrings = splitString(text);
					for (auto & textString : textStrings) {
						WordChange(textString);
					}
					text = uniteString(textStrings);
					cout << text;
					SData(text, tmp); //���������� ��������� ���������
				}
				catch (Exception e) {
					e.display();
				}
				break;
		}
		case (b): {
			ifstream file; // ������� ���� �� ������
			string name; //��� �����
			string text; //����� �� �����
			string tmp; //������ �������� ������
			bool isAlright = true;
			int ans1; //���������� ��� ������ ������
			int ans2; //���������� ��� ������ ������
				try {
						cout << "������� ����� ����� ��� ����� ������ ";
						cin >> name;    // ������� �������� ������ file
						if (is_regular_file(name)) {
							file.open(name);// ������� ���� �� ������
							if (file.good()) {
								bool is_result = false;
								do {
									size_t count = 0; //����� �������� � �����
									char S; //��� �������� ��������

									/*������ ������� ����� ��������*/
									ifstream f(name);
									while (!f.eof())
									{
										f.get(S);
										count++;
									}
									f.close();
									
									/*��������� ����� � ����������*/

									char *S2 = new char[count]; //�������� ������ �� ������������� ����� ��������
									for (int i = 0; i < count; i++) S2[i] = NULL; //������� ������ �� �����
									ifstream f2(name);  //������� ����� ��� ������ � ������
									int i = 0; //������ �� ������� ������ (��� ����� ����� � �����)
									while (!f2.eof()) //�������� �� �����
									{
										f2.get(S2[i]); //���������� ������ �� �������� 
										i++; //����������� ������ ��� ������ ���������� �������
									}
									text += S2;
									if (text.length() == 0 || text[0] == ' ') {
										cout << "������: ������ ����" << endl;
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
									
									cout << S2 << endl; //������ ���������� char[] �������� ����� �� �����
									text = uniteText(textStrings);
									cout << "\n" << text;
									cin.sync(); cin.get();
									f2.close(); //��������� ������ � ������
									delete[]S2; //����������� ������
									SData(text, tmp); //���������� ��������� ���������
									is_result = true;
								} while (!is_result);
							}
							else {
								cout << "���� � ����� ������ �� ����������" << endl;
								break;
							}
						}
						else {
							isAlright = false;
							throw Exception(FileNotExist, (char*)"���� �� ����������");
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