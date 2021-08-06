/*filename:score.h
description:�ɼ��������*/

#pragma once
#include "course.h"
#include "time.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
//�ɼ���
class score :public course, public time
{
private:
	double value;
	double GPA;
	string grade;
public:
	score();
	~score();

	double getValue() { return value; };
	double getGPA() { return GPA; };
	string getGrade() { return grade; };
	void setScore();
	void modifyScore();
	double addup();
	void calGPA();

	friend ostream& operator<<(ostream&, score& s);
	friend ofstream& operator<<(ofstream&, score& s);
	friend ifstream& operator>>(ifstream&, score& s);
};