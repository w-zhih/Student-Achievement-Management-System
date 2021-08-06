/*filename:database.h
description:���ݿ��������*/

#pragma once
#include "student.h"
#include "fileexception.h"
#include "linkedlist.h"
using namespace std;

class database
{
private:
	linkedlist<student> stuList;
	
public:
	database();
	~database();

	linkedlist<student>& getStuList() { return stuList; };
	//�ļ���д����
	void load();
	void save();
	//����ѧ���⺯��
	void addStu();
	void modifyStu2();
	bool delStu();
	void displayStu();
	void sortStu(int flag);//1.��ѧ������ 2.����������
	//����ɼ��⺯��
	void addScore2();
	bool delScore2(node<student>* stu);
	node<student>* searchByStu();
	void searchBySubject();
	//��������
	node<student>* findStu(string name_ = "", string id_ = "");

};

//���ڱ��浥���ɼ�����
struct record
{
	student stu;
	score sco;
	record(student s1, score s2) :stu(s1), sco(s2) { };
	record() :stu(), sco() {};
};