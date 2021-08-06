/*filename:database.cpp
description:数据库类的定义*/

#include "database.h"
#include <iostream>
#include <fstream>
#include <iomanip>

database::database() {
	stuList.makeEmpty();
}

database::~database() {
	stuList.makeEmpty();
}
//载入信息
void database::load() {
	ifstream ifile("data.txt", ios::in);
	node<student>* stu;
	string type;
	if (ifile) {
		ifile >> type;
		while (!ifile.eof()) {
			if (type.compare("student:") == 0) {
				ifile.seekg(-8, ios::cur);
				stu = new node<student>;
				if (ifile >> stu->data) {
					stuList.push(stu);
				}
				else {
					FileException e("data.txt", "operate", "read");
					throw e;
				}
				ifile >> type;
			}
		}
		ifile.close();
	}
	else {
		FileException e("data.txt", "open", "read");
		throw e;
	}
}
//保存信息
void database::save() {
	ofstream ofile("data.txt", ios::out | ios::trunc);
	node<student>* stu;
	if (ofile) {
		stu = stuList.getFirst();
		while (stu != NULL) {
			if (!(ofile << stu->data)) {
				FileException e("data.txt", "operate", "write");
				throw e;
			}
			stu = stu->next;
		}
		ofile.close();
	}
	else {
		FileException e("data.txt", "open", "write");
		throw e;
	}
}
//录入学生信息
void database::addStu() {
	cout << "         <录入学生信息>" << endl;
	node<student>* newStu = new node<student>;
	newStu->data.setStu();
	stuList.push(newStu);
	cout << "录入学生成功!" << endl;
}
//打印所有学生信息
void database::displayStu() {
	cout << "==========管理学生档案==========" << endl;
	if (stuList.isEmpty()) {
		cout << "       系统中暂无学生信息" << endl;
		return;
	}
	cout << "NO.  " << setw(8) << setiosflags(ios::left) << "姓名" << setw(9) << setiosflags(ios::left) << "性别" << setw(7) << setiosflags(ios::left) << "学号";
	cout << setw(10) << setiosflags(ios::left) << "入学年份" << "院系" << endl;
	node<student>* stu = stuList.getFirst();
	int count = 1;
	while (stu != NULL) {
		cout << setw(4) << setiosflags(ios::left) << count;
		stu->data.printStu();
		count++;
		stu = stu->next;
	}
	cout << "共" << stuList.size() << "位学生" <<endl;
}
//删除学生信息
bool database::delStu() {
	cout << "         <删除学生信息>" << endl;
	int index;
	cout << "请输入想删除的学生编号(输入\"0\"取消删除):";
	cin >> index;
	while (index < 0 || index > stuList.size() || cin.fail()) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			cin.sync();
			cout << "输入不合法,请重新输入:";
			cin >> index;
			continue;
		}
		cout << "学生编号须>=0且<=" << stuList.size() << ",请重新输入:";
		cin >> index;
	}
	if (index == 0)
		return true;
	if (index < 0 || index > stuList.size())
		return false;
	node<student>* tmp = stuList.getFirst();
	index--;
	while (tmp != NULL) {
		if (index == 0) {
			stuList.remove(tmp);
			break;
		}
		index--;
		tmp = tmp->next;
	}
	cout << "删除成功!" << endl;
	return true;
}
//修改学生信息
void database::modifyStu2() {
	cout << "         <修改学生信息>" << endl;
	int index;
	cout << "请输入想修改的学生编号(输入\"0\"取消修改):";
	cin >> index;
	while (index < 0 || index > stuList.size() || cin.fail()) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			cin.sync();
			cout << "输入不合法,请重新输入:";
			cin >> index;
			continue;
		}
		cout << "学生编号须>=0且<=" << stuList.size() << ",请重新输入:";
		cin >> index;
	}
	if (index == 0)
		return;
	node<student>* stu = stuList.getFirst();
	while (--index > 0) {
		stu = stu->next;
	}
	stu->data.modifyStu();
	return;
}
//排序学生:1.按学号排序 2.按均绩排序
void database::sortStu(int flag) {
	switch (flag)
	{
	case 1:
		stuList.sort([](node<student>& s1, node<student>& s2)->bool {
			return (s1.data.getId().compare(s2.data.getId()) >= 0);
			});
		break;
	case 2:
		stuList.sort([](node<student>& s1, node<student>& s2)->bool {
			return (s1.data.getAverageGPA() <= s2.data.getAverageGPA());
			});
		break;
	}
}
//在成绩库中录入成绩
void database::addScore2() {
	cout << "==========录入成绩信息==========" << endl;
	string name_, id_;
	while (true) {
		cout << "请输入学生姓名(未知可输入\"\\\"):";
		cin >> name_;
		cout << "请输入学生学号(未知可输入\"\\\"):";
		cin >> id_;
		if (name_.compare("\\") == 0 && id_.compare("\\") == 0) {
			cout << "学生姓名和学号至少输入一个!" << endl;
		}
		else {
			break;
		}
	}
	if (name_.compare("\\") == 0)
		name_ = "";
	if (id_.compare("\\") == 0)
		id_ = "";
	node<student>* stu = findStu(name_, id_);
	if (stu == NULL) {
		cout << "系统中不存在该学生，是否为其新建档案(y/n)?";
		char c;
		cin.ignore(1024, '\n');
		cin >> c;
		while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
			cout << "输入不合法,请重新输入(y/n):";
			cin.ignore(1024, '\n');
			cin >> c;
		}
		if (c == 'y' || c == 'Y') {
			stu = new node<student>;
			stu->data.setStu();
			stuList.push(stu);
			cout << "新建成功!" << endl;
		}
		else {
			return;
		}
	}
	stu->data.addScore();
	cout << "录入成绩成功!" << endl;
}
//删除某学生的成绩
bool database::delScore2(node<student>* stu) {
	if (stu == NULL)
		return false;
	if (findStu(stu->data.getStuName(), stu->data.getId()) != NULL) {
		cout << "请输入想要删除的成绩信息编号(输入\"0\"取消删除):";
		int index;
		cin >> index;
		while (index < 0 || index > stu->data.getScores().size()) {
			cout << "输入不合法,请重新输入:";
			cin >> index;
		}
		if (index == 0)
			return true;
		stu->data.delScore(index);
		cout << "删除成功!";
		return true;
	}
	return false;
}
//按学生检索成绩
node<student>* database::searchByStu() {
	cout << "          <按学生检索>" << endl;
	string name_, id_;
	while (true) {
		cout << "请输入学生姓名(未知可输入\"\\\"):";
		cin >> name_;
		cout << "请输入学生学号(未知可输入\"\\\"):";
		cin >> id_;
		if (name_.compare("\\") == 0 && id_.compare("\\") == 0) {
			cout << "学生姓名和学号至少输入一个!" << endl;
		}
		else {
			break;
		}
	}
	if (name_.compare("\\") == 0)
		name_ = "";
	if (id_.compare("\\") == 0)
		id_ = "";
	node<student>* stu = findStu(name_, id_);
	if (stu == NULL) {
		cout << "查无此人" << endl;
		return NULL;
	}
	cout << stu->data;
	if (stu->data.getScores().isEmpty()) {
		return NULL;
	}
	else {
		return stu;
	}
}
//按学科检索成绩
void database::searchBySubject() {
	linkedlist<record> subRecord;
	cout << "          <按学科检索>" << endl;
	string subject;
	cout << "请输入学科名称:";
	cin >> subject;
	node<student>* stu = stuList.getFirst();
	node<score>* sco;
	while (stu != NULL) {
		sco = stu->data.getScores().getFirst();
		while (sco != NULL) {
			if (sco->data.getName().compare(subject) == 0) {
				node<record>* newNode = new node<record>;
				newNode->data = record(stu->data, sco->data);
				subRecord.push(newNode);
			}
			sco = sco->next;
		}
		stu = stu->next;
	}
	cout << "检索完毕!" << endl;
	cout << "请选择排序方式(1.按学号排序 2.按成绩排序):";
	char c;
	cin >> c;
	while (c != '1' && c != '2') {
		cout << "输入不合法,请输入\"1\"或\"2\":";
		cin >> c;
	}
	switch (c)
	{
	case '1':
		subRecord.sort([](node<record>& r1, node<record>& r2)->bool {
			return (r1.data.stu.getId().compare(r2.data.stu.getId()) <= 0);
			});
		break;
	case '2':
		subRecord.sort([](node<record>& r1, node<record>& r2)->bool {
			return (r1.data.sco.getValue() <= r2.data.sco.getValue());
			});
	}

	double totalValue = 0;
	node<record>* tmp = subRecord.getFirst();
	cout << "[课程名:" << setw(12) << setiosflags(ios::left) << subject << "课程号:" << setw(8) << setiosflags(ios::left) << tmp->data.sco.getNO();
	cout << "学分" << setw(3) << setiosflags(ios::left) << tmp->data.sco.getCredit() << endl;
	cout << "NO. " << setw(10) << setiosflags(ios::left) << "学生姓名" << setw(12) << setiosflags(ios::left) << "学生学号";
	cout << setw(10) << setiosflags(ios::left) << "必修/选修" << setw(10) << setiosflags(ios::left) << "计分方式";
	cout << "学年-学期 " << setw(5) << setiosflags(ios::left) << "分数" << setw(5) << setiosflags(ios::left) << "绩点" << setw(3) << setiosflags(ios::left) << "等级" << endl;
	int count = 1;
	while (tmp != NULL) {
		cout << setw(4) << setiosflags(ios::left) << count << setw(10) << setiosflags(ios::left) << tmp->data.stu.getStuName() << setw(12) << setiosflags(ios::left) << tmp->data.stu.getId();
		cout << setw(10) << setiosflags(ios::left) << (tmp->data.sco.getState() ? "必修" : "选修") << setw(10) << setiosflags(ios::left) << (tmp->data.sco.getPF() ? "PF" : "绩点");
		tmp->data.sco.printTime();
		cout << setw(4) << setiosflags(ios::left) << tmp->data.sco.getValue() << setw(5) << setiosflags(ios::left) << (tmp->data.sco.getPF()?'\\':(tmp->data.sco.getGPA())) << setw(3) << setiosflags(ios::left) << tmp->data.sco.getGrade() << endl;
		count++;
		totalValue += tmp->data.sco.getValue();
		tmp = tmp->next;
	}
	cout << "共有" << --count << "条记录,平均成绩为" << totalValue / subRecord.size() << endl;
}

node<student>* database::findStu(string name_ , string id_ ) {
	if (stuList.isEmpty())
		return NULL;
	node<student>* stu = stuList.getFirst();
	while (stu != NULL) {
		if (name_.compare("") == 0 && id_.compare("") != 0) {
			if (stu->data.getId().compare(id_) == 0)
				return stu;
		}
		if (name_.compare("") != 0 && id_.compare("") == 0) {
			if (stu->data.getStuName().compare(name_) == 0)
				return stu;
		}
		if (name_.compare("") != 0 && id_.compare("") != 0) {
			if (stu->data.getStuName().compare(name_) == 0 && stu->data.getId().compare(id_)==0)
				return stu;
		}
		stu = stu->next;
	}
	return NULL;
}
