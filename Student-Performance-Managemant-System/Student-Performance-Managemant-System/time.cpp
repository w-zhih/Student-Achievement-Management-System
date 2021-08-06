/*filename:time.cpp
description:ʱ����Ķ���*/

#include "time.h"
#include <iostream>
#include <iomanip>

time::time() {
	year = 2021;
	term = Autumn;
}

time::~time() {

}

void time::setTime() {
	cout << "         <¼��ʱ����Ϣ>" << endl;
	cout << "������ѧ��:";
	cin.ignore(1024, '\n');
	cin >> year;
	while (year <= 2000 || cin.fail()) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			cin.sync();
		}
		cout << "���벻�Ϸ�,����������:";
		cin.ignore(1024, '\n');
		cin >> year;
		
	}
	cout << "������ѧ��(1.�� 2.�� 3.��):";
	char c;
	cin.ignore(1024, '\n');
	cin >> c;
	while (c != '1' && c != '2' && c != '3') {
		cout << "���벻�Ϸ�,����������:";
		cin.ignore(1024, '\n');
		cin >> c;
	}
	term = TermType(c - '1');
	cout << "ʱ��¼��ɹ�!" << endl;
}

void time::modifyTime() {
	cout << "         <�޸�ʱ����Ϣ>" << endl;
	int flag = 1;
	while (flag) {
		cout << "1.ѧ��" << endl << "2.ѧ��" << endl << "3.����޸�" << endl;
		cout << "��������Ҫ�޸ĵ���Ŀ:";
		char choice, c;
		cin.ignore(1024, '\n');
		cin >> choice;
		
		while (choice != '1' && choice != '2' && choice != '3') {
			cout << "���벻�Ϸ�,����������:";
			cin.ignore(1024, '\n');
			cin >> choice;
		}
		switch (choice)
		{
		case '1':
			cout << "ȷ���Ƿ��޸�ѧ��?(y/n)";
			cin.ignore(1024, '\n');
			cin >> c;
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "���벻�Ϸ�,����������(y/n):";
				cin.ignore(1024, '\n');
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "�������޸ĺ�ѧ��:";
				cin.ignore(1024, '\n');
				cin >> year;
				while (year <= 2000 || cin.fail()) {
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						cin.sync();
					}
					cout << "���벻�Ϸ�,����������:";
					cin.ignore(1024, '\n');
					cin >> year;
				}
				cout << "�޸ĳɹ�!" << endl;
			}
			break;

		case '2':
			cout << "ȷ���Ƿ��޸�ѧ��?(y/n)";
			cin.ignore(1024, '\n');
			cin >> c;
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "���벻�Ϸ�,����������(y/n):";
				cin.ignore(1024, '\n');
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "�������޸ĺ�ѧ��(1.�� 2.�� 3.��):";
				char c;
				cin.ignore(1024, '\n');
				cin >> c;
				while (c != '1' && c != '2' && c != '3') {
					cout << "���벻�Ϸ�,����������:";
					cin.ignore(1024, '\n');cin >> c;
					
				}
				term = TermType(c - '1');
				cout << "�޸ĳɹ�!" << endl;
			}
			break;
		default:
			flag = 0;
			break;
		}
		cout << endl;
	}
	
}

void time::printTime() {
	cout << year << '-';
	switch (term) {
	case Autumn:cout << "��    "; break;
	case Spring:cout << "��    "; break;
	case Summer:cout << "��    "; break;
	}
}