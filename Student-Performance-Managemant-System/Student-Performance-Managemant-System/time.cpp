/*filename:time.cpp
description:时间类的定义*/

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
	cout << "         <录入时间信息>" << endl;
	cout << "请输入学年:";
	cin.ignore(1024, '\n');
	cin >> year;
	while (year <= 2000 || cin.fail()) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			cin.sync();
		}
		cout << "输入不合法,请重新输入:";
		cin.ignore(1024, '\n');
		cin >> year;
		
	}
	cout << "请输入学期(1.春 2.夏 3.秋):";
	char c;
	cin.ignore(1024, '\n');
	cin >> c;
	while (c != '1' && c != '2' && c != '3') {
		cout << "输入不合法,请重新输入:";
		cin.ignore(1024, '\n');
		cin >> c;
	}
	term = TermType(c - '1');
	cout << "时间录入成功!" << endl;
}

void time::modifyTime() {
	cout << "         <修改时间信息>" << endl;
	int flag = 1;
	while (flag) {
		cout << "1.学年" << endl << "2.学期" << endl << "3.完成修改" << endl;
		cout << "请输入想要修改的项目:";
		char choice, c;
		cin.ignore(1024, '\n');
		cin >> choice;
		
		while (choice != '1' && choice != '2' && choice != '3') {
			cout << "输入不合法,请重新输入:";
			cin.ignore(1024, '\n');
			cin >> choice;
		}
		switch (choice)
		{
		case '1':
			cout << "确认是否修改学年?(y/n)";
			cin.ignore(1024, '\n');
			cin >> c;
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "输入不合法,请重新输入(y/n):";
				cin.ignore(1024, '\n');
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "请输入修改后学年:";
				cin.ignore(1024, '\n');
				cin >> year;
				while (year <= 2000 || cin.fail()) {
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						cin.sync();
					}
					cout << "输入不合法,请重新输入:";
					cin.ignore(1024, '\n');
					cin >> year;
				}
				cout << "修改成功!" << endl;
			}
			break;

		case '2':
			cout << "确认是否修改学期?(y/n)";
			cin.ignore(1024, '\n');
			cin >> c;
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "输入不合法,请重新输入(y/n):";
				cin.ignore(1024, '\n');
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "请输入修改后学期(1.秋 2.夏 3.秋):";
				char c;
				cin.ignore(1024, '\n');
				cin >> c;
				while (c != '1' && c != '2' && c != '3') {
					cout << "输入不合法,请重新输入:";
					cin.ignore(1024, '\n');cin >> c;
					
				}
				term = TermType(c - '1');
				cout << "修改成功!" << endl;
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
	case Autumn:cout << "秋    "; break;
	case Spring:cout << "春    "; break;
	case Summer:cout << "夏    "; break;
	}
}