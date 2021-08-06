/*filename:course.cpp
description:课程类的定义*/

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
	cout << "         <录入课程信息>" << endl;
	cout << "请输入课程名:";
	cin >> info;
	setName(info);
	cout << "请输入课程号:";
	cin >> info;
	setNO(info);
	cout << "请输入课程学分:";
	cin.ignore(1024, '\n');
	cin >> n;
	while (n <= 0 || cin.fail()) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			cin.sync();
		}
		cout << "输入不合法,请重新输入:" << endl;
		cin.ignore(1024, '\n');
		cin >> n;
	}
	setCredit(n);
	cout << "请输入是否必修?(y/n)";
	cin.ignore(1024, '\n');cin >> c;
	
	while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
		cout << "输入不合法,请重新输入(y/n):";
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
		cout << "请输入是否PF计分?(y/n)";
		cin.ignore(1024, '\n');cin >> c;
		
		while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
			cout << "输入不合法,请重新输入(y/n):";
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
	cout << "课程录入成功!" << endl;
}

void course::printCourse() {
	cout << setw(12) << setiosflags(ios::left) << getName() << setw(9) << setiosflags(ios::left) << getNO() << setw(6) << setiosflags(ios::left) << getCredit();
	cout << setw(9) << setiosflags(ios::left) << (getState() ? "必修" : "选修") << setw(10) << setiosflags(ios::left) << (getPF() ? "PF" : "绩点");
}

void course::modifyCourse() {
	cout << "         <修改课程信息>" << endl;
	int flag = 1;
	while (flag) {
		cout << "1.课程名" << endl << "2.课程号" << endl << "3.课程学分" << endl << "4.必修/选修" << endl << "5.计分方式(PF/绩点)" << endl << "6.完成修改" << endl;
		cout << "请输入想要修改的项目:";
		char choice, c;
		cin.ignore(1024, '\n');cin >> choice;
		
		while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6') {
			cout << "输入不合法,请重新输入:";
			cin.ignore(1024, '\n');
			cin >> choice;
		}
		switch (choice) {
		case '1':
			cout << "确认是否修改课程名?(y/n)";
			cin.ignore(1024, '\n');cin >> c;
			
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "输入不合法,请重新输入(y/n):";
				cin.ignore(1024, '\n');
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "请输入修改后课程名:";
				string newName;
				cin >> newName;
				setName(newName);
				cout << "修改成功!" << endl;
			}
			break;
		case '2':
			cout << "确认是否修改课程号?(y/n)";
			cin.ignore(1024, '\n');
			cin >> c;
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "输入不合法,请重新输入(y/n):";
				cin.ignore(1024, '\n');
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "请输入修改后课程号:";
				string newNO;
				cin >> newNO;
				setName(newNO);
				cout << "修改成功!" << endl;
			}
			break;
		case '3':
			cout << "确认是否修改课程学分?(y/n)";
			cin.ignore(1024, '\n');
			cin >> c;
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "输入不合法,请重新输入(y/n):";
				cin.ignore(1024, '\n');
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "请输入修改后课程学分:";
				int n;
				cin.ignore(1024, '\n');
				cin >> n;
				
				while (n <= 0 || cin.fail()) {
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						cin.sync();
					}
					cout << "输入不合法,请重新输入:" << endl;
					cin.ignore(1024, '\n');
					cin >> n;
				}
				setCredit(n);
				cout << "修改成功!" << endl;
			}
			break;
		case '4':
			cout << "确认是否切换必修/选修状态?(y/n)";
			cin.ignore(1024, '\n');cin >> c;
			
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "输入不合法,请重新输入(y/n):";
				cin.ignore(1024, '\n');cin >> c;
				
			}
			if (c == 'y' || c == 'Y') {
				changeState();
				cout << "修改成功!" << endl;
			}
			break;
		case '5':
			cout << "确认是否切换绩点/PF计分方式?(y/n)";
			cin.ignore(1024, '\n');cin >> c;
			
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "输入不合法,请重新输入(y/n):";
				cin.ignore(1024, '\n');cin >> c;
				
			}
			if (c == 'y' || c == 'Y') {
				if (changePF()) {
					cout << "修改成功!" << endl;
				}
				else {
					cout << "该课程为必修课,无法记PF,修改失败!" << endl;
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