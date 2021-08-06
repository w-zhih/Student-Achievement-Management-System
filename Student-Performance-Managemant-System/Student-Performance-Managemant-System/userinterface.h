/*filename:userinterface.h
description:用户接口类的声明*/

#pragma once
#include "database.h"
using namespace std;

class userinterface
{
private:
	database* stu_database;
public:
	userinterface();
	~userinterface();
	//运行与交互主函数
	bool running();
	//主菜单
	void mainMenu();
	//管理学生档案
	void manageStu();
	//录入成绩信息
	void enterScore();
	//检索成绩信息
	void searchScore();
	//管理成绩信息(若返回主菜单,return false)
	bool manageScore(node<student>* stu);
	//退出界面
	void quit();
	//暂停函数
	void pause();
};