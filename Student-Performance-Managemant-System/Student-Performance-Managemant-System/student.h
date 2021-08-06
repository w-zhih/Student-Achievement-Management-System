/*filename:student.h
description:学生类的声明*/

#pragma once
#include "score.h"
#include "linkedlist.h"
#include <string>
using namespace std;
//学生类
class student
{
private:
	string name;//学生姓名
	bool sex;//性别: true:male false:female
	string id;//学号
	int enrollment_year;//入学年份
	string department;//院系
	linkedlist<score> scores;//成绩链表
	double average_GPA;//均绩
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
	void addScore();//增添成绩信息
	bool delScore(int index);//删除成绩信息,以编号为索引
	double calAverageGPA();//计算均绩
	void sortScores(int flag);//排序成绩:0:按时间排序 1:按成绩排序 2:按学分排序

	friend ostream& operator<<(ostream&, student& s);
	friend ofstream& operator<<(ofstream&, student& s);
	friend ifstream& operator>>(ifstream&, student& s);
};