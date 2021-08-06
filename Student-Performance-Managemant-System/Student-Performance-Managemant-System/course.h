/*filename:course.h
description:课程类的声明*/

#pragma once

#include "base.h"
#include <string>
using namespace std;
//课程类
class course :public base
{
private:
	bool state;//true:必修 false:选修
	bool isPF;//计分方式:true:PF false:GPA

public:
	course();
	~course();

	bool getState() { return state; };
	bool getPF() { return isPF; };
	void changeState();//切换必修/选修
	bool changePF();//切换计分方式

	virtual void setCourse();//设置课程信息
	virtual void printCourse();//打印课程信息
	virtual void modifyCourse();//修改课程信息
};