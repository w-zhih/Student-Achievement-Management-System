/*filename:base.cpp
description:基础课程类的定义*/

#include "base.h"
#include <iostream>

base::base() {
	courseName = "";
	courseNO = "";
	credit = 0;
}

base::~base() {

}

void base::setCourse() {
	string info;
	int n;
	cout << "         <录入课程信息>" << endl;
	cout << "请输入课程名:";
	cin >> info;
	setName(info);
	cout << "请输入课程号:";
	cin >> info;
	setNO(info);
	cout << "请输入课程学分:";
	cin >> n;
	while (n <= 0) {
		cout << "输入不合法,请重新输入:" << endl;
		cin >> n;
	}
	setCredit(n);
}