/*filename:student.h
description:ѧ���������*/

#pragma once
#include "score.h"
#include "linkedlist.h"
#include <string>
using namespace std;
//ѧ����
class student
{
private:
	string name;//ѧ������
	bool sex;//�Ա�: true:male false:female
	string id;//ѧ��
	int enrollment_year;//��ѧ���
	string department;//Ժϵ
	linkedlist<score> scores;//�ɼ�����
	double average_GPA;//����
public:
	student();
	~student();
	
	string getStuName() { return name; };
	bool getSex() { return sex; };
	string getId() { return id; };
	int getEnrollmentYear() { return enrollment_year; };
	string getDepartment() { return department; };
	double getAverageGPA() { return average_GPA; };
	linkedlist<score>& getScores() { return scores; };

	void setStu();
	void printStu();
	void modifyStu();
	void addScore();//����ɼ���Ϣ
	bool delScore(int index);//ɾ���ɼ���Ϣ,�Ա��Ϊ����
	double calAverageGPA();//�������
	void sortScores(int flag);//����ɼ�:0:��ʱ������ 1:���ɼ����� 2:��ѧ������

	friend ostream& operator<<(ostream&, student& s);
	friend ofstream& operator<<(ofstream&, student& s);
	friend ifstream& operator>>(ifstream&, student& s);
};