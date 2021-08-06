/*filename:course.cpp
description:�γ���Ķ���*/

#include "course.h"
#include <iostream>
#include <iomanip>

course::course() :base() {
	state = true;
	isPF = false;
}

course::~course() {

}

void course::changeState() {
	if (state) {
		state = false;
		return;
	}
	else {
		state = true;
		if (isPF) {
			isPF = false;
		}
	}
}

bool course::changePF() {
	if (state) {
		return false;
	}
	else {
		if (isPF)
			isPF = false;
		else
			isPF = true;
		return true;
	}
}

void course::setCourse() {
	string info;
	int n;
	char c;
	cout << "         <¼��γ���Ϣ>" << endl;
	cout << "������γ���:";
	cin >> info;
	setName(info);
	cout << "������γ̺�:";
	cin >> info;
	setNO(info);
	cout << "������γ�ѧ��:";
	cin.ignore(1024, '\n');
	cin >> n;
	while (n <= 0 || cin.fail()) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			cin.sync();
		}
		cout << "���벻�Ϸ�,����������:" << endl;
		cin.ignore(1024, '\n');
		cin >> n;
	}
	setCredit(n);
	cout << "�������Ƿ����?(y/n)";
	cin.ignore(1024, '\n');cin >> c;
	
	while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
		cout << "���벻�Ϸ�,����������(y/n):";
		cin.ignore(1024, '\n');
		cin >> c;
	}
	if (c == 'y' || c == 'Y') {
		state = true;
	}
	else {
		state = false;
	}
	if (state == false) {
		cout << "�������Ƿ�PF�Ʒ�?(y/n)";
		cin.ignore(1024, '\n');cin >> c;
		
		while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
			cout << "���벻�Ϸ�,����������(y/n):";
			cin.ignore(1024, '\n');
			cin >> c;
		}
		if (c == 'y' || c == 'Y') {
			isPF = true;
		}
		else {
			isPF = false;
		}
	}
	cout << "�γ�¼��ɹ�!" << endl;
}

void course::printCourse() {
	cout << setw(12) << setiosflags(ios::left) << getName() << setw(9) << setiosflags(ios::left) << getNO() << setw(6) << setiosflags(ios::left) << getCredit();
	cout << setw(9) << setiosflags(ios::left) << (getState() ? "����" : "ѡ��") << setw(10) << setiosflags(ios::left) << (getPF() ? "PF" : "����");
}

void course::modifyCourse() {
	cout << "         <�޸Ŀγ���Ϣ>" << endl;
	int flag = 1;
	while (flag) {
		cout << "1.�γ���" << endl << "2.�γ̺�" << endl << "3.�γ�ѧ��" << endl << "4.����/ѡ��" << endl << "5.�Ʒַ�ʽ(PF/����)" << endl << "6.����޸�" << endl;
		cout << "��������Ҫ�޸ĵ���Ŀ:";
		char choice, c;
		cin.ignore(1024, '\n');cin >> choice;
		
		while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6') {
			cout << "���벻�Ϸ�,����������:";
			cin.ignore(1024, '\n');
			cin >> choice;
		}
		switch (choice) {
		case '1':
			cout << "ȷ���Ƿ��޸Ŀγ���?(y/n)";
			cin.ignore(1024, '\n');cin >> c;
			
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "���벻�Ϸ�,����������(y/n):";
				cin.ignore(1024, '\n');
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "�������޸ĺ�γ���:";
				string newName;
				cin >> newName;
				setName(newName);
				cout << "�޸ĳɹ�!" << endl;
			}
			break;
		case '2':
			cout << "ȷ���Ƿ��޸Ŀγ̺�?(y/n)";
			cin.ignore(1024, '\n');
			cin >> c;
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "���벻�Ϸ�,����������(y/n):";
				cin.ignore(1024, '\n');
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "�������޸ĺ�γ̺�:";
				string newNO;
				cin >> newNO;
				setName(newNO);
				cout << "�޸ĳɹ�!" << endl;
			}
			break;
		case '3':
			cout << "ȷ���Ƿ��޸Ŀγ�ѧ��?(y/n)";
			cin.ignore(1024, '\n');
			cin >> c;
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "���벻�Ϸ�,����������(y/n):";
				cin.ignore(1024, '\n');
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "�������޸ĺ�γ�ѧ��:";
				int n;
				cin.ignore(1024, '\n');
				cin >> n;
				
				while (n <= 0 || cin.fail()) {
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						cin.sync();
					}
					cout << "���벻�Ϸ�,����������:" << endl;
					cin.ignore(1024, '\n');
					cin >> n;
				}
				setCredit(n);
				cout << "�޸ĳɹ�!" << endl;
			}
			break;
		case '4':
			cout << "ȷ���Ƿ��л�����/ѡ��״̬?(y/n)";
			cin.ignore(1024, '\n');cin >> c;
			
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "���벻�Ϸ�,����������(y/n):";
				cin.ignore(1024, '\n');cin >> c;
				
			}
			if (c == 'y' || c == 'Y') {
				changeState();
				cout << "�޸ĳɹ�!" << endl;
			}
			break;
		case '5':
			cout << "ȷ���Ƿ��л�����/PF�Ʒַ�ʽ?(y/n)";
			cin.ignore(1024, '\n');cin >> c;
			
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "���벻�Ϸ�,����������(y/n):";
				cin.ignore(1024, '\n');cin >> c;
				
			}
			if (c == 'y' || c == 'Y') {
				if (changePF()) {
					cout << "�޸ĳɹ�!" << endl;
				}
				else {
					cout << "�ÿγ�Ϊ���޿�,�޷���PF,�޸�ʧ��!" << endl;
				}
			}
			break;
		default:
			flag = 0;
			break;
		}
		cout << endl;
	}
	
}