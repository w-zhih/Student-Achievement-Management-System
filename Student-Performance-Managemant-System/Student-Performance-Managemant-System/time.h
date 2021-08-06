/*filename:time.h
description:ʱ���������*/

#pragma once
using namespace std;

enum TermType
{
	Spring,
	Summer,
	Autumn
};
//ʱ����
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