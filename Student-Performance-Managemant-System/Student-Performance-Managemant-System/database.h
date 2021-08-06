/*filename:database.h
description:数据库类的声明*/

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
	//文件读写函数
	void load();
	void save();
	//管理学生库函数
	void addStu();
	void modifyStu2();
	bool delStu();
	void displayStu();
	void sortStu(int flag);//1.按学号排序 2.按均绩排序
	//管理成绩库函数
	void addScore2();
	bool delScore2(node<student>* stu);
	node<student>* searchByStu();
	void searchBySubject();
	//辅助函数
	node<student>* findStu(string name_ = "", string id_ = "");

};

//用于保存单条成绩数据
struct record
{
	student stu;
	score sco;
	record(student s1, score s2) :stu(s1), sco(s2) { };
	record() :stu(), sco() {};
};