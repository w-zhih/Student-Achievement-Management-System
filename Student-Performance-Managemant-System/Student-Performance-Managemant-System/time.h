/*filename:time.h
description:时间类的声明*/

#pragma once
using namespace std;

enum TermType
{
	Spring,
	Summer,
	Autumn
};
//时间类
class time
{
private:
	int year;
	TermType term;
public:
	time();
	~time();

	int getYear() { return year; };
	TermType getTerm() { return term; };
	void setYear(int y) { year = y; };
	void setTerm(TermType t) { term = t; };

	void setTime();
	void printTime();
	void modifyTime();
};