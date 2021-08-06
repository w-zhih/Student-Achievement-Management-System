/*filename:base.h
description:基础课程类的声明*/

#pragma once
#include <string>
using namespace std;
//基础课程类
class base
{
private:
	string courseName;//课程名
	string courseNO;//课程号
	int credit;//学分

public:
	base();
	~base();

	string getName() { return courseName; };
	string getNO() { return courseNO; };
	int getCredit() { return credit; };
	void setName(string inputName) { courseName = inputName; };
	void setNO(string inputNO) { courseNO = inputNO; };
	void setCredit(int inputCredit) { credit = inputCredit; };
	
	virtual void setCourse();//设置课程信息
	virtual void printCourse() = 0;//打印课程信息
	virtual void modifyCourse() = 0;//修改课程信息
};