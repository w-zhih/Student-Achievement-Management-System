/*filename:database.cpp
description:���ݿ���Ķ���*/

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
//������Ϣ
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
//������Ϣ
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
//¼��ѧ����Ϣ
void database::addStu() {
	cout << "         <¼��ѧ����Ϣ>" << endl;
	node<student>* newStu = new node<student>;
	newStu->data.setStu();
	stuList.push(newStu);
	cout << "¼��ѧ���ɹ�!" << endl;
}
//��ӡ����ѧ����Ϣ
void database::displayStu() {
	cout << "==========����ѧ������==========" << endl;
	if (stuList.isEmpty()) {
		cout << "       ϵͳ������ѧ����Ϣ" << endl;
		return;
	}
	cout << "NO.  " << setw(8) << setiosflags(ios::left) << "����" << setw(9) << setiosflags(ios::left) << "�Ա�" << setw(7) << setiosflags(ios::left) << "ѧ��";
	cout << setw(10) << setiosflags(ios::left) << "��ѧ���" << "Ժϵ" << endl;
	node<student>* stu = stuList.getFirst();
	int count = 1;
	while (stu != NULL) {
		cout << setw(4) << setiosflags(ios::left) << count;
		stu->data.printStu();
		count++;
		stu = stu->next;
	}
	cout << "��" << stuList.size() << "λѧ��" <<endl;
}
//ɾ��ѧ����Ϣ
bool database::delStu() {
	cout << "         <ɾ��ѧ����Ϣ>" << endl;
	int index;
	cout << "��������ɾ����ѧ�����(����\"0\"ȡ��ɾ��):";
	cin >> index;
	while (index < 0 || index > stuList.size() || cin.fail()) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			cin.sync();
			cout << "���벻�Ϸ�,����������:";
			cin >> index;
			continue;
		}
		cout << "ѧ�������>=0��<=" << stuList.size() << ",����������:";
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
	cout << "ɾ���ɹ�!" << endl;
	return true;
}
//�޸�ѧ����Ϣ
void database::modifyStu2() {
	cout << "         <�޸�ѧ����Ϣ>" << endl;
	int index;
	cout << "���������޸ĵ�ѧ�����(����\"0\"ȡ���޸�):";
	cin >> index;
	while (index < 0 || index > stuList.size() || cin.fail()) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			cin.sync();
			cout << "���벻�Ϸ�,����������:";
			cin >> index;
			continue;
		}
		cout << "ѧ�������>=0��<=" << stuList.size() << ",����������:";
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
//����ѧ��:1.��ѧ������ 2.����������
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
//�ڳɼ�����¼��ɼ�
void database::addScore2() {
	cout << "==========¼��ɼ���Ϣ==========" << endl;
	string name_, id_;
	while (true) {
		cout << "������ѧ������(δ֪������\"\\\"):";
		cin >> name_;
		cout << "������ѧ��ѧ��(δ֪������\"\\\"):";
		cin >> id_;
		if (name_.compare("\\") == 0 && id_.compare("\\") == 0) {
			cout << "ѧ��������ѧ����������һ��!" << endl;
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
		cout << "ϵͳ�в����ڸ�ѧ�����Ƿ�Ϊ���½�����(y/n)?";
		char c;
		cin.ignore(1024, '\n');
		cin >> c;
		while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
			cout << "���벻�Ϸ�,����������(y/n):";
			cin.ignore(1024, '\n');
			cin >> c;
		}
		if (c == 'y' || c == 'Y') {
			stu = new node<student>;
			stu->data.setStu();
			stuList.push(stu);
			cout << "�½��ɹ�!" << endl;
		}
		else {
			return;
		}
	}
	stu->data.addScore();
	cout << "¼��ɼ��ɹ�!" << endl;
}
//ɾ��ĳѧ���ĳɼ�
bool database::delScore2(node<student>* stu) {
	if (stu == NULL)
		return false;
	if (findStu(stu->data.getStuName(), stu->data.getId()) != NULL) {
		cout << "��������Ҫɾ���ĳɼ���Ϣ���(����\"0\"ȡ��ɾ��):";
		int index;
		cin >> index;
		while (index < 0 || index > stu->data.getScores().size()) {
			cout << "���벻�Ϸ�,����������:";
			cin >> index;
		}
		if (index == 0)
			return true;
		stu->data.delScore(index);
		cout << "ɾ���ɹ�!";
		return true;
	}
	return false;
}
//��ѧ�������ɼ�
node<student>* database::searchByStu() {
	cout << "          <��ѧ������>" << endl;
	string name_, id_;
	while (true) {
		cout << "������ѧ������(δ֪������\"\\\"):";
		cin >> name_;
		cout << "������ѧ��ѧ��(δ֪������\"\\\"):";
		cin >> id_;
		if (name_.compare("\\") == 0 && id_.compare("\\") == 0) {
			cout << "ѧ��������ѧ����������һ��!" << endl;
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
		cout << "���޴���" << endl;
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
//��ѧ�Ƽ����ɼ�
void database::searchBySubject() {
	linkedlist<record> subRecord;
	cout << "          <��ѧ�Ƽ���>" << endl;
	string subject;
	cout << "������ѧ������:";
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
	cout << "�������!" << endl;
	cout << "��ѡ������ʽ(1.��ѧ������ 2.���ɼ�����):";
	char c;
	cin >> c;
	while (c != '1' && c != '2') {
		cout << "���벻�Ϸ�,������\"1\"��\"2\":";
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
	cout << "[�γ���:" << setw(12) << setiosflags(ios::left) << subject << "�γ̺�:" << setw(8) << setiosflags(ios::left) << tmp->data.sco.getNO();
	cout << "ѧ��" << setw(3) << setiosflags(ios::left) << tmp->data.sco.getCredit() << endl;
	cout << "NO. " << setw(10) << setiosflags(ios::left) << "ѧ������" << setw(12) << setiosflags(ios::left) << "ѧ��ѧ��";
	cout << setw(10) << setiosflags(ios::left) << "����/ѡ��" << setw(10) << setiosflags(ios::left) << "�Ʒַ�ʽ";
	cout << "ѧ��-ѧ�� " << setw(5) << setiosflags(ios::left) << "����" << setw(5) << setiosflags(ios::left) << "����" << setw(3) << setiosflags(ios::left) << "�ȼ�" << endl;
	int count = 1;
	while (tmp != NULL) {
		cout << setw(4) << setiosflags(ios::left) << count << setw(10) << setiosflags(ios::left) << tmp->data.stu.getStuName() << setw(12) << setiosflags(ios::left) << tmp->data.stu.getId();
		cout << setw(10) << setiosflags(ios::left) << (tmp->data.sco.getState() ? "����" : "ѡ��") << setw(10) << setiosflags(ios::left) << (tmp->data.sco.getPF() ? "PF" : "����");
		tmp->data.sco.printTime();
		cout << setw(4) << setiosflags(ios::left) << tmp->data.sco.getValue() << setw(5) << setiosflags(ios::left) << (tmp->data.sco.getPF()?'\\':(tmp->data.sco.getGPA())) << setw(3) << setiosflags(ios::left) << tmp->data.sco.getGrade() << endl;
		count++;
		totalValue += tmp->data.sco.getValue();
		tmp = tmp->next;
	}
	cout << "����" << --count << "����¼,ƽ���ɼ�Ϊ" << totalValue / subRecord.size() << endl;
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
