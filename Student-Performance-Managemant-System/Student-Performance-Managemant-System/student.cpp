/*filename:student.cpp
description:ѧ����Ķ���*/

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
	cout << "������ѧ������:";
	cin >> name;
	cout << "������ѧ���Ա�(��/Ů):";
	string s;
	cin >> s;
	while (s.compare("��") != 0 && s.compare("Ů") != 0) {
		cout << "���벻�Ϸ�,����������:";
		cin >> s;
	}
	if (s.compare("��") == 0)
		sex = true;
	if (s.compare("Ů") == 0)
		sex = false;
	cout << "������ѧ��ѧ��:";
	cin >> id;
	cout << "������ѧ����ѧ���:";
	cin >> enrollment_year;
	while(enrollment_year <= 2000) {
		cout << "���벻�Ϸ�,����������:";
		cin >> enrollment_year;
	}
	cout << "������ѧ��Ժϵ:";
	cin >> department;
}

void student::printStu() {
	cout << setw(10) << setiosflags(ios::left) << name << setw(5) << setiosflags(ios::left) << (sex ? "��" : "Ů") << setw(12) << setiosflags(ios::left) << id;
	cout << setw(7) << setiosflags(ios::left) << enrollment_year << department << endl;
}

void student::modifyStu() {
	cout << "�޸�ѧ�� "<< name <<" ����Ϣ:" << endl;
	int flag = 1;
	while (flag) {
		cout << "1.ѧ������" << endl << "2.ѧ���Ա�" << endl << "3.ѧ��ѧ��" << endl << "4.��ѧ���" << endl << "5.ѧ��Ժϵ" << endl << "6.����޸�" << endl;
		cout << "��������Ҫ�޸ĵ���Ŀ:";
		char choice, c;
		cin >> choice;
		while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6') {
			cout << "���벻�Ϸ�,����������:";
			cin >> choice;
		}
		switch (choice) {
		case '1':
			cout << "ȷ���Ƿ��޸�ѧ������?(y/n)";
			cin >> c;
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "���벻�Ϸ�,����������(y/n):";
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "�������޸ĺ�����:";
				cin >> name;
				cout << "�޸ĳɹ�!" << endl;
			}
			break;
		case '2':
			cout << "ȷ���Ƿ��޸�ѧ���Ա�?(y/n)";
			cin >> c;
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "���벻�Ϸ�,����������(y/n):";
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "�������޸ĺ�ѧ���Ա�(��/Ů):";
				string s;
				cin >> s;
				while (s.compare("��") != 0 && s.compare("Ů") != 0) {
					cout << "���벻�Ϸ�,����������:";
					cin >> s;
				}
				if (s.compare("��") == 0)
					sex = true;
				if (s.compare("Ů") == 0)
					sex = false;
				cout << "�޸ĳɹ�!" << endl;
			}
			break;
		case '3':
			cout << "ȷ���Ƿ��޸�ѧ��ѧ��?(y/n)";
			cin >> c;
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "���벻�Ϸ�,����������(y/n):";
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "�������޸ĺ�ѧ��ѧ��:";
				cin >> id;
				cout << "�޸ĳɹ�!" << endl;
			}
			break;
		case '4':
			cout << "ȷ���Ƿ��޸���ѧ���?(y/n)";
			cin >> c;
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "���벻�Ϸ�,����������(y/n):";
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "�������޸ĺ���ѧ���:";
				cin >> enrollment_year;
				while (enrollment_year <= 2020) {
					cout << "���벻�Ϸ�,�����>=2021,����������:";
					cin >> enrollment_year;
				}
				cout << "�޸ĳɹ�!" << endl;
			}
			break;
		case '5':
			cout << "ȷ���Ƿ��޸�ѧ��Ժϵ?(y/n)";
			cin >> c;
			while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
				cout << "���벻�Ϸ�,����������(y/n):";
				cin >> c;
			}
			if (c == 'y' || c == 'Y') {
				cout << "�������޸ĺ�ѧ��Ժϵ:";
				cin >> department;
				cout << "�޸ĳɹ�!" << endl;
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
	cout << "ɾ���ɹ�!" << endl;
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
	case 1://�ڰ�ʱ������Ļ����ϰ��ɼ�����
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
	case 2://�ڰ�ʱ������Ļ����ϰ�ѧ������
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
	cout << "[ѧ������:" << setw(10) << setiosflags(ios::left) << s.name << "ѧ��:" << setw(10) << setiosflags(ios::left) << s.id << "]" << endl;
	if (s.scores.isEmpty()) {
		cout << "���޳ɼ���Ϣ" << endl;
		return output;
	}
	cout << "NO. ";
	cout << setw(11) << setiosflags(ios::left) << "�γ���" << setw(8) << setiosflags(ios::left) << "�γ̺�" << setw(5) << setiosflags(ios::left) << "ѧ��";
	cout << setw(10) << setiosflags(ios::left) << "����/ѡ��" << setw(10) << setiosflags(ios::left) << "�Ʒַ�ʽ";
	cout << "ѧ��-ѧ��  " << setw(4) << setiosflags(ios::left) << "����" << setw(5) << setiosflags(ios::left) << "����" << setw(3) << setiosflags(ios::left) << "�ȼ�" << endl;
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
	cout << "����" << count << "����¼,ƽ��GPAΪ" << s.average_GPA << endl;
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
