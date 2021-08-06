/*filename:userinterface.cpp
description:�û��ӿ���Ķ���*/

#include "userinterface.h"
#include "linkedlist.h"
#include <iostream>
#include <iomanip>

userinterface::userinterface() {
	stu_database = NULL;
}

userinterface::~userinterface() {
	delete stu_database;
}

void userinterface::pause() {
	cin.clear();
	cin.ignore(1024, '\n');
	cin.sync();
	cout << "�����������...";
	getchar();
}

bool userinterface::running() {
	system("cls");
	cin.clear();
	cin.sync();

	if (stu_database == NULL) {
		stu_database = new database();
		try {
			stu_database->load();
		}
		catch (FileException e) {
			if (e.mode == "open") {
				cout << "��" << e.type << "��ʽ���ļ�" << e.filename << "ʱ����" << endl;
			}
			else {
				if (e.type == "read") {
					cout << "���ļ�" << e.filename << "��ȡʱ����" << endl;
				}
				else {
					cout << "���ļ�" << e.filename << "д��ʱ����" << endl;
				}
			}
			return false;
		}
	}

	mainMenu();

	int input;
	cin >> input;
	if (!cin) {
		cout << "�������,���������롣" << endl;
		pause();
		return true;
	}

	switch (input) {
	case 1:
		manageStu();
		break;
	case 2:
		enterScore();
		break;
	case 3:
		searchScore();
		break;
	case 4:
		quit();
		return false;
	default:
		cout<< "�������,���������롣" << endl;
	}
	pause();
	return true;
}


void userinterface::mainMenu() {
	system("cls");
	cout << "********ѧ���ɼ�����ϵͳ********" << endl;
	cout << "\t1.����ѧ������" << endl << "\t2.¼��ɼ���Ϣ" << endl << "\t3.����/����ɼ���Ϣ" << endl << "\t4.�˳�ϵͳ" << endl;
	cout << "�����Ž��в���:";
}

void userinterface::manageStu() {
	int flag = 1;
	while (flag) {
		system("cls");
		stu_database->displayStu();
		cout << endl;
		cout << "\t1.¼��ѧ����Ϣ" << endl << "\t2.�޸�ѧ����Ϣ" << endl << "\t3.ɾ��ѧ����Ϣ" << endl << "\t4.����ѧ����Ϣ" << endl << "\t5.��ѯѧ���ɼ�" << endl << "\t6.�������˵�" << endl;
		cout << "�����Ž��в���:";
		char c;
		cin >> c;
		while (c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6') {
			cout << "���벻�Ϸ�,����������:";
			cin.ignore(1024, '\n');
			cin >> c;
		}
		cout << endl;
		switch (c) {
		case '1':
			stu_database->addStu();
			pause();
			break;
		case '2':
			stu_database->modifyStu2();
			pause();
			break;
		case '3':
			while(!stu_database->delStu());
			pause();
			break;
		case '4':
			cout << "         <����ѧ����Ϣ>" << endl;
			cout << "\t1.��ѧ������" << endl << "\t2.����������" << endl << "\t3.�����ϼ��˵�" << endl;
			cout << "�����Ž��в���:";
			char c;
			cin >> c;
			while (c != '1' && c != '2' && c!= '3') {
				cout << "���벻�Ϸ�,����������:";
				cin.ignore(1024, '\n');
				cin >> c;
			}
			if (c == '1') {
				stu_database->sortStu(1);
			}
			else if (c == '2') {
				stu_database->sortStu(2);
			}
			if (c != '3')
				cout << "����ɹ�!" <<endl;
			pause();
			break;
		case '5': {
			cout << "         <��ѯѧ���ɼ�>" << endl;
			int index;
			cout << "���������ѯ��ѧ�����(����\"0\"ȡ����ѯ):";
			cin >> index;
			while (index < 0 || index > stu_database->getStuList().size() || cin.fail()) {
				if (cin.fail()) {
					cout << "���벻�Ϸ�,����������:";
					cin.clear();
					cin.ignore(1024, '\n');
					cin.sync();
					cin >> index;
					continue;
				}
				cout << "ѧ�������>=0��<=" << stu_database->getStuList().size() << ",����������:";
				cin.ignore(1024, '\n');
				cin >> index;
			}
			if (index == 0) {
				pause();
				break;
			}
			node<student>* target = stu_database->getStuList().getByIndex(index - 1);
			cout << endl << target->data << endl;

			cout << "\t1.����ɼ���Ϣ" << endl << "\t2.�����ϼ��˵�" << endl << "\t3.�������˵�" << endl;
			cout << "�����Ž��в���:";
			cin >> c;
			while (c != '1' && c != '2' && c != '3') {
				cout << "���벻�Ϸ�,����������:";
				cin.ignore(1024, '\n');
				cin >> c;
			}
			if (c == '1') {
				flag = 0;
				while (true) {
					system("cls");
					cout << "         <��ѯѧ���ɼ�>" << endl;
					cout << target->data << endl;
					if (!manageScore(target))
						break;
				}

				break;
			}
			else if (c == '2') {
				pause();
				break;
			}
			else if (c == '3') {
				flag = 0;
				break;
			}
		}
		case '6': 
			flag = 0;
			break;
		
		}
		
	}
	
}

void userinterface::enterScore() {
	system("cls");
	stu_database->addScore2();
}

void userinterface::searchScore() {
	cout << "==========�����ɼ���Ϣ==========" << endl;
	cout << "1.��ѧ������" << endl << "2.��ѧ�Ƽ���" << endl << "3.�������˵�" << endl;
	cout << "�����������ʽ:";
	char c;
	cin >> c;
	while (c != '1' && c != '2' && c != '3') {
		cout << "���벻�Ϸ�,����������:";
		cin >> c;
	}
	switch (c) {
	case '1': {
		node<student>* stu = stu_database->searchByStu();
		if (stu == NULL)
			break;
		cout << endl;
		pause();
		while (true) {
			system("cls");
			cout << "          <��ѧ������>" << endl;
			cout << stu->data <<endl;
			if (!manageScore(stu))
				break;
		}
		break;
	}
	case '2':
		stu_database->searchBySubject();
		break;
	case '3':
		break;
	}

}

bool userinterface::manageScore(node<student>* stu) {
	cout << "         <����ɼ���Ϣ>" << endl;
	cout << "\t1.�޸ĳɼ���Ϣ" << endl << "\t2.ɾ���ɼ���Ϣ" << endl << "\t3.����ɼ���Ϣ" << endl << "\t4.�鿴ѧ����ϸ��Ϣ" << endl << "\t5.�������˵�" << endl;
	cout << "�����Ž��в���:";
	char c;
	cin >> c;
	while (c != '1' && c != '2' && c != '3' && c!='4' && c!='5') {
		cout << "���벻�Ϸ�,����������:";
		cin >> c;
	}
	cout << endl;
	switch (c) {
	case '1': {
		if (stu->data.getScores().isEmpty()) {
			cout << "��ѧ�����޳ɼ���Ϣ,�޷��޸ġ�" << endl;
			break;
		}
		cout << "���������޸ĵĳɼ����(����\"0\"ȡ���޸�):";
		int index;
		cin >> index;
		while (index < 0 || index > stu->data.getScores().size() || cin.fail()) {
			if (cin.fail()) {
				cout << "���벻�Ϸ�,����������:";
				cin.clear();
				cin.ignore(1024, '\n');
				cin.sync();
				cin >> index;
				continue;
			}
			cout << "ѧ�������>=0��<=" << stu_database->getStuList().size() << ",����������:";
			cin >> index;
		}
		node<score>* target_score = stu->data.getScores().getByIndex(index - 1);
		target_score->data.modifyScore();
		break;
	}
	case '2': {
		if (stu->data.getScores().isEmpty()) {
			cout << "��ѧ�����޳ɼ���Ϣ,�޷�ɾ����" << endl;
			break;
		}
		cout << "��������ɾ���ĳɼ����(����\"0\"ȡ��ɾ��):";
		int index = 0;
		cin.ignore(1024, '\n');
		cin >> index;
		while (index < 0 || index > stu->data.getScores().size() || cin.fail()) {
			if (cin.fail()) {
				cout << "���벻�Ϸ�,����������:";
				cin.clear();
				cin.ignore(1024, '\n');
				cin.sync();
				cin >> index;
				continue;
			}
			cout << "�ɼ������>=0��<=" << stu->data.getScores().size() << ",����������:";
			cin.ignore(1024, '\n');
			cin >> index;
		}
		stu->data.delScore(index - 1);
		break;
	}
	case '3': {
		if (stu->data.getScores().isEmpty()) {
			cout << "��ѧ�����޳ɼ���Ϣ,�޷�����" << endl;
			break;
		}
		cout << "\t1.���ɼ�����" << endl << "\t2.��ѧ������" << endl << "\t3.�����ϼ��˵�" << endl;
		cout << "�����Ž��в���:";
		char choice;
		cin.ignore(1024, '\n');cin >> choice;
		
		while (choice != '1' && choice != '2' && choice != '3') {
			cout << "���벻�Ϸ�,����������:";
			cin.ignore(1024, '\n');
			cin >> choice;
			
		}
		if (choice == '1') {
			stu->data.sortScores(1);
		}
		else if (choice == '2') {
			stu->data.sortScores(2);
		}
		else if (choice == '3') {
			break;
		}
		cout << "����ɹ�!" << endl;
		break;
	}
	case '4': {
		cout << "[ѧ����ϸ��Ϣ]" << endl;
		cout << "����:" << setw(10) << setiosflags(ios::left) << stu->data.getStuName() << "�Ա�:" << setw(4) << setiosflags(ios::left) << (stu->data.getSex() ? "��" : "Ů");
		cout << "ѧ��:" << setw(10) << setiosflags(ios::left) << stu->data.getId() << endl;
		cout << "��ѧ���:" << setw(6) << setiosflags(ios::left) << stu->data.getEnrollmentYear() << "Ժϵ:" << stu->data.getDepartment() << endl << endl;
		break;
	}
	case '5':
		return false;
	}
	pause();
	return true;
}

void userinterface::quit() {
	cout << "�Ƿ񱣴�����?(y/n):";
	char input;
	cin >> input;
	cin.ignore(1024, '\n');
	while (input != 'y' && input != 'Y' && input != 'n' && input != 'N') {
		cout << "���벻�Ϸ�,����������:";
		cin >> input;
		cin.ignore(1024, '\n');
	}
	if (input == 'y' || input == 'Y') {
		try {
			stu_database->save();
		}
		catch (FileException e) {
			if (e.mode == "open") {
				cout << "��" << e.type << "��ʽ���ļ�" << e.filename << "ʱ����" << endl;
			}
			else {
				if (e.type == "read") {
					cout << "���ļ�" << e.filename << "��ȡʱ����" << endl;
				}
				else {
					cout << "���ļ�" << e.filename << "д��ʱ����" << endl;
				}
			}
		}
	}
	cout << "ллʹ��,�ټ�!" << endl;
}