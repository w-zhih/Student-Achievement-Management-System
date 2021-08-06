/*filename:userinterface.cpp
description:用户接口类的定义*/

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
	cout << "按任意键继续...";
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
				cout << "以" << e.type << "方式打开文件" << e.filename << "时出错。" << endl;
			}
			else {
				if (e.type == "read") {
					cout << "从文件" << e.filename << "读取时出错。" << endl;
				}
				else {
					cout << "向文件" << e.filename << "写入时出错。" << endl;
				}
			}
			return false;
		}
	}

	mainMenu();

	int input;
	cin >> input;
	if (!cin) {
		cout << "输入错误,请重新输入。" << endl;
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
		cout<< "输入错误,请重新输入。" << endl;
	}
	pause();
	return true;
}


void userinterface::mainMenu() {
	system("cls");
	cout << "********学生成绩管理系统********" << endl;
	cout << "\t1.管理学生档案" << endl << "\t2.录入成绩信息" << endl << "\t3.检索/管理成绩信息" << endl << "\t4.退出系统" << endl;
	cout << "输入编号进行操作:";
}

void userinterface::manageStu() {
	int flag = 1;
	while (flag) {
		system("cls");
		stu_database->displayStu();
		cout << endl;
		cout << "\t1.录入学生信息" << endl << "\t2.修改学生信息" << endl << "\t3.删除学生信息" << endl << "\t4.排序学生信息" << endl << "\t5.查询学生成绩" << endl << "\t6.返回主菜单" << endl;
		cout << "输入编号进行操作:";
		char c;
		cin >> c;
		while (c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6') {
			cout << "输入不合法,请重新输入:";
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
			cout << "         <排序学生信息>" << endl;
			cout << "\t1.按学号排序" << endl << "\t2.按均绩排序" << endl << "\t3.返回上级菜单" << endl;
			cout << "输入编号进行操作:";
			char c;
			cin >> c;
			while (c != '1' && c != '2' && c!= '3') {
				cout << "输入不合法,请重新输入:";
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
				cout << "排序成功!" <<endl;
			pause();
			break;
		case '5': {
			cout << "         <查询学生成绩>" << endl;
			int index;
			cout << "请输入想查询的学生编号(输入\"0\"取消查询):";
			cin >> index;
			while (index < 0 || index > stu_database->getStuList().size() || cin.fail()) {
				if (cin.fail()) {
					cout << "输入不合法,请重新输入:";
					cin.clear();
					cin.ignore(1024, '\n');
					cin.sync();
					cin >> index;
					continue;
				}
				cout << "学生编号须>=0且<=" << stu_database->getStuList().size() << ",请重新输入:";
				cin.ignore(1024, '\n');
				cin >> index;
			}
			if (index == 0) {
				pause();
				break;
			}
			node<student>* target = stu_database->getStuList().getByIndex(index - 1);
			cout << endl << target->data << endl;

			cout << "\t1.管理成绩信息" << endl << "\t2.返回上级菜单" << endl << "\t3.返回主菜单" << endl;
			cout << "输入编号进行操作:";
			cin >> c;
			while (c != '1' && c != '2' && c != '3') {
				cout << "输入不合法,请重新输入:";
				cin.ignore(1024, '\n');
				cin >> c;
			}
			if (c == '1') {
				flag = 0;
				while (true) {
					system("cls");
					cout << "         <查询学生成绩>" << endl;
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
	cout << "==========检索成绩信息==========" << endl;
	cout << "1.按学生检索" << endl << "2.按学科检索" << endl << "3.返回主菜单" << endl;
	cout << "请输入检索方式:";
	char c;
	cin >> c;
	while (c != '1' && c != '2' && c != '3') {
		cout << "输入不合法,请重新输入:";
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
			cout << "          <按学生检索>" << endl;
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
	cout << "         <管理成绩信息>" << endl;
	cout << "\t1.修改成绩信息" << endl << "\t2.删除成绩信息" << endl << "\t3.排序成绩信息" << endl << "\t4.查看学生详细信息" << endl << "\t5.返回主菜单" << endl;
	cout << "输入编号进行操作:";
	char c;
	cin >> c;
	while (c != '1' && c != '2' && c != '3' && c!='4' && c!='5') {
		cout << "输入不合法,请重新输入:";
		cin >> c;
	}
	cout << endl;
	switch (c) {
	case '1': {
		if (stu->data.getScores().isEmpty()) {
			cout << "该学生暂无成绩信息,无法修改。" << endl;
			break;
		}
		cout << "请输入想修改的成绩编号(输入\"0\"取消修改):";
		int index;
		cin >> index;
		while (index < 0 || index > stu->data.getScores().size() || cin.fail()) {
			if (cin.fail()) {
				cout << "输入不合法,请重新输入:";
				cin.clear();
				cin.ignore(1024, '\n');
				cin.sync();
				cin >> index;
				continue;
			}
			cout << "学生编号须>=0且<=" << stu_database->getStuList().size() << ",请重新输入:";
			cin >> index;
		}
		node<score>* target_score = stu->data.getScores().getByIndex(index - 1);
		target_score->data.modifyScore();
		break;
	}
	case '2': {
		if (stu->data.getScores().isEmpty()) {
			cout << "该学生暂无成绩信息,无法删除。" << endl;
			break;
		}
		cout << "请输入想删除的成绩编号(输入\"0\"取消删除):";
		int index = 0;
		cin.ignore(1024, '\n');
		cin >> index;
		while (index < 0 || index > stu->data.getScores().size() || cin.fail()) {
			if (cin.fail()) {
				cout << "输入不合法,请重新输入:";
				cin.clear();
				cin.ignore(1024, '\n');
				cin.sync();
				cin >> index;
				continue;
			}
			cout << "成绩编号须>=0且<=" << stu->data.getScores().size() << ",请重新输入:";
			cin.ignore(1024, '\n');
			cin >> index;
		}
		stu->data.delScore(index - 1);
		break;
	}
	case '3': {
		if (stu->data.getScores().isEmpty()) {
			cout << "该学生暂无成绩信息,无法排序。" << endl;
			break;
		}
		cout << "\t1.按成绩排序" << endl << "\t2.按学分排序" << endl << "\t3.返回上级菜单" << endl;
		cout << "输入编号进行操作:";
		char choice;
		cin.ignore(1024, '\n');cin >> choice;
		
		while (choice != '1' && choice != '2' && choice != '3') {
			cout << "输入不合法,请重新输入:";
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
		cout << "排序成功!" << endl;
		break;
	}
	case '4': {
		cout << "[学生详细信息]" << endl;
		cout << "姓名:" << setw(10) << setiosflags(ios::left) << stu->data.getStuName() << "性别:" << setw(4) << setiosflags(ios::left) << (stu->data.getSex() ? "男" : "女");
		cout << "学号:" << setw(10) << setiosflags(ios::left) << stu->data.getId() << endl;
		cout << "入学年份:" << setw(6) << setiosflags(ios::left) << stu->data.getEnrollmentYear() << "院系:" << stu->data.getDepartment() << endl << endl;
		break;
	}
	case '5':
		return false;
	}
	pause();
	return true;
}

void userinterface::quit() {
	cout << "是否保存数据?(y/n):";
	char input;
	cin >> input;
	cin.ignore(1024, '\n');
	while (input != 'y' && input != 'Y' && input != 'n' && input != 'N') {
		cout << "输入不合法,请重新输入:";
		cin >> input;
		cin.ignore(1024, '\n');
	}
	if (input == 'y' || input == 'Y') {
		try {
			stu_database->save();
		}
		catch (FileException e) {
			if (e.mode == "open") {
				cout << "以" << e.type << "方式打开文件" << e.filename << "时出错。" << endl;
			}
			else {
				if (e.type == "read") {
					cout << "从文件" << e.filename << "读取时出错。" << endl;
				}
				else {
					cout << "向文件" << e.filename << "写入时出错。" << endl;
				}
			}
		}
	}
	cout << "谢谢使用,再见!" << endl;
}