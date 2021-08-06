/*filename:student.cpp
description:学生类的定义*/

#include "student.h"
#include <iostream>
#include <iomanip>
using namespace std;

student::student() :name(""), sex(true), id(""), enrollment_year(2020), department(""), average_GPA(0.0) {
	scores.makeEmpty();
}

student::~student() {

}

void student::setStu() {
	cout << "请输入学生姓名:";
	cin >> name;
	cout << "请输入学生性别(男/女):";
	string s;
	cin >> s;
	while (s.compare("男") != 0 && s.compare("女") != 0) {
		cout << "输入不合法,请重新输入:";
		cin >> s;
	}
	if (s.compare("男") == 0)
		sex = true;
	if (s.compare("女") == 0)
		sex = false;
	cout << "请输入学生学号:";
	cin >> id;
	cout << "请输入学生入学年份:";
	cin >> enrollment_year;
	while(enrollment_year <= 2000) {
		cout << "输入不合法,请重新输入:";
		cin >> enrollment_year;
	}
	cout << "请输入学生院系:";
	cin >> department;
}

void student::printStu() {
	cout << setw(10) << setiosflags(ios::left) << name << setw(5) << setiosflags(ios::left) << (sex ? "男" : "女") << setw(12) << setiosflags(ios::left) << id;
	cout << setw(7) << setiosflags(ios::left) << enrollment_year << department << endl;
}

void student::modifyStu() {
	cout << "修改学生 "<< name <<" 的信息:" << endl;
	int flag = 1;
	while (flag) {
		cout << "1.学生姓名" << endl << "2.学生性别" << endl << "3.学生学号" << endl << "4.入学年份" << endl << "5.学生院系" << endl << "6.完成修改" << endl;
		cout << "请输入想要修改的项目:";
		char choice, c;
		cin >> choice;
		while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6') {
			cout << "输入不合法,请重新输入:";
			cin >> choice;
		}
		switch (choice) {
		case '1':
			cout << "确认是否修改学生姓名?(y/n)";
			cin >> c;
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "输入不合法,请重新输入(y/n):";
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "请输入修改后姓名:";
				cin >> name;
				cout << "修改成功!" << endl;
			}
			break;
		case '2':
			cout << "确认是否修改学生性别?(y/n)";
			cin >> c;
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "输入不合法,请重新输入(y/n):";
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "请输入修改后学生性别(男/女):";
				string s;
				cin >> s;
				while (s.compare("男") != 0 && s.compare("女") != 0) {
					cout << "输入不合法,请重新输入:";
					cin >> s;
				}
				if (s.compare("男") == 0)
					sex = true;
				if (s.compare("女") == 0)
					sex = false;
				cout << "修改成功!" << endl;
			}
			break;
		case '3':
			cout << "确认是否修改学生学号?(y/n)";
			cin >> c;
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "输入不合法,请重新输入(y/n):";
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "请输入修改后学生学号:";
				cin >> id;
				cout << "修改成功!" << endl;
			}
			break;
		case '4':
			cout << "确认是否修改入学年份?(y/n)";
			cin >> c;
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "输入不合法,请重新输入(y/n):";
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "请输入修改后入学年份:";
				cin >> enrollment_year;
				while (enrollment_year <= 2020) {
					cout << "输入不合法,年份须>=2021,请重新输入:";
					cin >> enrollment_year;
				}
				cout << "修改成功!" << endl;
			}
			break;
		case '5':
			cout << "确认是否修改学生院系?(y/n)";
			cin >> c;
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "输入不合法,请重新输入(y/n):";
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "请输入修改后学生院系:";
				cin >> department;
				cout << "修改成功!" << endl;
			}
			break;
		case '6':
			flag = 0;
		}
		cout << endl;
	}
	
	
}

void student::addScore() {
	node<score>* sco = new node<score>;
	sco->data.setScore();
	scores.push(sco);
	sortScores(1);
	average_GPA=calAverageGPA();
}

bool student::delScore(int index) {
	if (index < 0 || index >= scores.size())
		return false;
	scores.remove(scores.getByIndex(index));
	sortScores(1);
	average_GPA = calAverageGPA();
	cout << "删除成功!" << endl;
	return true;
}

double student::calAverageGPA() {
	if (scores.isEmpty())
		return 0.0;
	double total = 0, totalCredit = 0;
	node<score>* tmp = scores.getFirst();
	while (tmp != NULL) {
		total += tmp->data.addup();
		if (!tmp->data.getPF())
			totalCredit += tmp->data.getCredit();
		tmp = tmp->next;
	}
	return total / totalCredit;
}

void student::sortScores(int flag) {
	switch (flag) {
	case 1://在按时间排序的基础上按成绩排序
		scores.sort([](node<score>& s1, node<score>& s2)->bool{
			int yearDiff = s1.data.getYear() - s2.data.getYear();
			if (yearDiff != 0)
				return (yearDiff > 0) ? true : false;
			int termDiff = s1.data.getTerm() - s2.data.getTerm();
			if (termDiff != 0)
				return (termDiff > 0) ? true : false;
			double valueDiff = s1.data.getValue() - s2.data.getValue();
			return (valueDiff <= 0) ? true : false;
			});
		break;
	case 2://在按时间排序的基础上按学分排序
		scores.sort([](node<score>& s1, node<score>& s2)->bool {
			int yearDiff = s1.data.getYear() - s2.data.getYear();
			if (yearDiff != 0)
				return (yearDiff > 0) ? true : false;
			int termDiff = s1.data.getTerm() - s2.data.getTerm();
			if (termDiff != 0)
				return (termDiff > 0) ? true : false;
			double creditDiff = s1.data.getCredit() - s2.data.getCredit();
			return (creditDiff <= 0) ? true : false;
			});
	}
	return;
}

ostream& operator<<(ostream& output, student& s) {
	cout << "[学生姓名:" << setw(10) << setiosflags(ios::left) << s.name << "学号:" << setw(10) << setiosflags(ios::left) << s.id << "]" << endl;
	if (s.scores.isEmpty()) {
		cout << "暂无成绩信息" << endl;
		return output;
	}
	cout << "NO. ";
	cout << setw(11) << setiosflags(ios::left) << "课程名" << setw(8) << setiosflags(ios::left) << "课程号" << setw(5) << setiosflags(ios::left) << "学分";
	cout << setw(10) << setiosflags(ios::left) << "必修/选修" << setw(10) << setiosflags(ios::left) << "计分方式";
	cout << "学年-学期  " << setw(4) << setiosflags(ios::left) << "分数" << setw(5) << setiosflags(ios::left) << "绩点" << setw(3) << setiosflags(ios::left) << "等级" << endl;
	int count = 1;
	node<score>* tmp = s.scores.getFirst();
	int time[2] = { 0,0 };
	while (tmp != NULL) {
		if (tmp->data.getYear() != time[0] || tmp->data.getTerm() != time[1]) {
			if(time[0]!=0)
				cout << endl;
			time[0] = tmp->data.getYear();
			time[1] = tmp->data.getTerm();
		}
		cout << setw(4) << setiosflags(ios::left) << count << tmp->data << endl;
		count++;
		tmp = tmp->next;
	}
	count--;
	cout << "共有" << count << "条记录,平均GPA为" << s.average_GPA << endl;
	return output;
}

ofstream& operator<<(ofstream& ofile, student& s) {
	string stu = "student:", sco = "score:";
	ofile << stu << endl << s.name << ' ' << s.sex << ' ' << s.id << ' ' << s.enrollment_year << ' ' << s.department << endl;
	node<score>* tmp = s.scores.getFirst();
	while (tmp != NULL) {
		ofile << sco << endl;
		ofile << tmp->data;
		tmp = tmp->next;
	}
	return ofile;
}

ifstream& operator>>(ifstream& ifile, student& s) {
	string type;
	ifile >> type;
	if (type.compare("student:") == 0) {
		ifile >> s.name;ifile >> s.sex;ifile >> s.id;
		ifile >> s.enrollment_year;ifile >> s.department;
		ifile >> type;
		if (ifile.fail()) {
			ifile.clear();
			return ifile;
		}
			
		
		while (type.compare("score:") == 0) {
			node<score>* newNode = new node<score>;
			ifile >> newNode->data;
			s.scores.push(newNode);
			ifile >> type;
			if (ifile.fail()) {
				ifile.clear();
				return ifile;
			}
				
			
		}
		if (type.compare("score:") != 0)
			ifile.seekg(-8, ios::cur);
	}
	s.average_GPA = s.calAverageGPA();
	return ifile;
}
