#include <filesystem>
#include "Algorithm.h"
#include <ctype.h>


using namespace std::experimental::filesystem::v1;
using namespace std;
enum Command_mode { Exit = 1, inFile, User, Unit_Test };
enum Dialog { Yes = 1, No, SaveData, SaveResult };
enum ExceptionType { InvalidArg, NegativArg, InvalidName, FileNotExist, Error };



//��������� ����� ����� �� ���-�� ����, ��� ����� ������ ��������
int LineWoSymbol(string w, int s) {
	for (auto & character : w) {

		if (isalpha(character))
			s++;
	}
	return s;
}


//������������ ����� � �����, ����� ������ � ���������
void WordChange(string & textString)
{
	string firstChar;
	string lastChar;
	string others;
	string symbols;
	int count = 0;
	firstChar = textString[0];
	auto tmp_textString = textString;
		for (int i = size(textString); i >= 1; i--) {

			if (isalpha(textString[i])) {
				lastChar = textString[i];
				count = i;
				break;
			}

		}
		for (int i = 1; i < count; i++) {
			others += textString[i];
		}
		for (count; count < size(textString); count++) {
			symbols += textString[count + 1];
		}

		for (size_t i = 0; i < size(others); i++) {
			swap(others[i], others[rand() % size(others)]);
		}
		textString = firstChar + others + lastChar + symbols;
}

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

// ������� ����������� ����� �����;
double ValidateValue() {
	double tmp;
	bool isInputSuccessful = true;
	do {
		try {
			cin >> tmp;
			isInputSuccessful = true;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				isInputSuccessful = false;
				throw Exception(InvalidArg, (char*)"������������ ����! ���������:");
			}
			else {
				cin.ignore(INT_MAX, '\n');
				return tmp;
			}
		}
		catch (Exception e) {
			e.display();
		}
	} while (!isInputSuccessful);
}

// ������� ����������� ����� ������;
string ValidateString() {
	string tmp;
	bool isInputSuccessful = true;
	do {
			try {
				getline(cin, tmp);
				isInputSuccessful = true;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					isInputSuccessful = false;
					throw Exception(InvalidArg, (char*)"������������ ����! ���������:");
				}
				else {
					return tmp;
				}
			}
			catch (Exception e) {
				e.display();
			}
	} while (!isInputSuccessful);
}

int SData(string result, string data) {
	string name;
	for (int i = 0; i < 1;) {
		try {
			for (int n = 0; n < 1;) {
				cout << "\n�������� ��������:" << endl;
				cout << "2-����������, 3-��������� �������� ������, 4-��������� ���������" << endl;
				switch ((int)ValidateValue()) {
				case No: return 1; break;
				case SaveData: {
					cout << "������� ��� �����:" << endl;
					cin >> name;
					if (is_regular_file(name)) {
						ifstream infile(name);
						if (infile.good()) {
							bool is_result = false;
							do {
								cout << "������������ ����?" << endl;
								cout << "1-��, 2-���" << endl;
								switch ((int)ValidateValue()) {
								case Yes: {
									ofstream file_temp(name);
									file_temp << data;
									is_result = true;
									cout << endl << "������!" << endl;
									break;
								}
								case No: {
									bool is_result_sec = false;
									do {
										// ���������� ������ � ����� �����
										cout << "�������� ������ � ����� �����?" << endl;
										cout << "1-��, 2-���" << endl;
										switch ((int)ValidateValue()) {
										case Yes: {
											ofstream file_temp;
											file_temp.open(name, std::ios::app);
											file_temp << "\n";
											file_temp << data;
											is_result = true;
											is_result_sec = true;
											cout << endl << "������!" << endl;
											break;
										}
										case No: is_result = true; is_result_sec = true; break;
										default: is_result_sec = false; break;
										}
									}while (!is_result_sec);
								}break;
								default: is_result = false; break;
								}
							
							}while (!is_result);
							
						}
						else {
							
							bool is_result = false;
							do {
									ofstream file_temp(name);
									file_temp << data;
									is_result = true;
									cout << endl << "������!" << endl;
									break;
								is_result = true; break;
								
							} while (!is_result);
						}
					}
					else
						break;
				} break;
				case SaveResult: {
					cout << "������� ��� �����:" << endl;
					cin >> name;
					if (is_regular_file(name)) {
						ifstream infile(name);
						if (infile.good()) {
							bool is_result = false;
							do {
								cout << "������������ ����?" << endl;
								cout << "1-��, 2-���" << endl;
								switch ((int)ValidateValue()) {
								case Yes: {
									ofstream file_temp(name);
									file_temp << result;
									is_result = true;
									cout << "������!" << endl;
									break;
								}
								case No: {
									bool is_result_sec = false;
									do {
										// ���������� ������ � ����� �����
										cout << "�������� ������ � ����� �����?" << endl;
										cout << "1-��, 2-���" << endl;
										switch ((int)ValidateValue()) {
										case Yes: {
											ofstream file_temp;
											file_temp.open(name, std::ios::app);
											file_temp << "\n";
											file_temp << result;
											is_result = true;
											is_result_sec = true;
											cout << endl << "������!" << endl;
											break;
										}
										case No: is_result = true; is_result_sec = true; break;
										default: is_result_sec = false; break;
										}
									} while (!is_result_sec);
								}break;
								default: is_result = false; break;
								}
							} while (!is_result);
						}
						else {							
							bool is_result = false;
							do {
									ofstream file_temp(name);
									file_temp << result;
									is_result = true;
									cout << endl << "������!" << endl;
									break;
								 is_result = true; break;
								
							} while (!is_result);
						}
					}
					else break;
				} break;
				default:
					throw Exception(NegativArg, (char*)"������������ ����!"); break;
				}
			}

		}
		catch (Exception e) {
			e.display();
		}
	}
}


