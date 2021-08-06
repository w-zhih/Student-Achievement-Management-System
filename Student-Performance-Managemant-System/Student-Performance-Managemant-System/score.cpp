/*filename:score.cpp
description:成绩类的定义*/

#include "score.h"
#include <iomanip>

score::score() :course(), time() {
	value = 0.0;
	GPA = 0.0;
	grade = "";
}

score::~score() {

}

void score::setScore() {
	setCourse();
	setTime();
	cout << "         <录入分数信息>" << endl;
	cout << "请输入百分制分数:";
	cin >> value;
	while (value < 0 || value>100 || cin.fail()) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			cin.sync();
		}
		cout << "输入不合法,请重新输入:";
		cin.ignore(1024, '\n');
		cin >> value;
	}
	calGPA();
}

void score::modifyScore() {
	modifyCourse();
	modifyTime();
	cout << "         <修改分数信息>" << endl;
	cout << "确认是否修改百分制分数?(y/n)";
	char c;
	cin.ignore(1024, '\n');cin >> c;
	
	while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
		cout << "输入不合法,请重新输入(y/n):";
		cin.ignore(1024, '\n');
		cin >> c;
	}
	if (c == 'y' || c == 'Y') {
		cout << "请输入修改后分数:";
		cin.ignore(1024, '\n');cin >> value;
		
		while (value < 0 || value>100 || cin.fail()) {
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1024, '\n');
				cin.sync();
			}
			cout << "输入不合法,请重新输入:";
			cin.ignore(1024, '\n');	
			cin >> value;
		}
		calGPA();
		cout << "修改成功!" << endl;
	}
}

double score::addup() {
	if (getPF()) {
		return 0.0;
	}
	else {
		return getCredit() * GPA;
	}
}

void score::calGPA() {
	if (!getPF()) {
		if (value >= 90) {
			GPA = 4.0;
			if (value >= 98) {
				grade = "A+";
			}
			else if (value >= 95) {
				grade = "A";
			}
			else {
				grade = "A-";
			}
		}
		else if (value >= 85) {
			GPA = 3.6;
			grade = "B+";
		}
		else if (value >= 80) {
			GPA = 3.3;
			grade = "B";
		}
		else if (value >= 77) {
			GPA = 3.0;
			grade = "B-";
		}
		else if (value >= 73) {
			GPA = 2.6;
			grade = "C+";
		}
		else if (value >= 70) {
			GPA = 2.3;
			grade = "C";
		}
		else if (value >= 67) {
			GPA = 2.0;
			grade = "C-";
		}
		else if (value >= 63) {
			GPA = 1.6;
			grade = "D+";
		}
		else if (value >= 60) {
			GPA = 1.3;
			grade = "D";
		}
		else {
			GPA = 0.0;
			grade = "F";
		}
	}
	else {
		GPA = 0.0;
		if (value >= 60) {
			grade = "P";
		}
		else {
			grade = "F";
		}
	}
}

ostream& operator<<(ostream& output, score& s) {
	s.printCourse();
	s.printTime();
	cout << setw(4) << setiosflags(ios::left) << s.value;
	if (s.getPF())
		cout << setw(5) << setiosflags(ios::left) << '\\';
	else
		cout << setw(5) << setiosflags(ios::left) << s.GPA;
	cout << setw(3) << setiosflags(ios::left) << s.grade;
	return output;
}

ofstream& operator<<(ofstream& ofile, score& s) {
	ofile << s.getName() << ' ' << s.getNO() << ' ' << s.getCredit() << ' ' << s.getState() << ' ' << s.getPF() << ' ' << s.getYear() << ' ' << s.getTerm() << ' ' << s.value << endl;
	return ofile;
}

ifstream& operator>>(ifstream& ifile, score& s) {
	string str;
	double dou;
	int i;
	bool b;
	ifile >> str; s.setName(str);
	ifile >> str; s.setNO(str);
	ifile >> i; s.setCredit(i);
	ifile >> b;
	if (!b) {
		s.changeState();
	}
	ifile >> b;
	if (b) {
		s.changePF();
	}
	ifile >> i; s.setYear(i);
	ifile >> i; s.setTerm(TermType(i));
	ifile >> dou; s.value = dou;
	s.calGPA();
	return ifile;
}