/*filename:base.h
description:�����γ��������*/

#pragma once
#include <string>
using namespace std;
//�����γ���
class base
{
private:
	string courseName;//�γ���
	string courseNO;//�γ̺�
	int credit;//ѧ��

public:
	base();
	~base();

	string getName() { return courseName; };
	string getNO() { return courseNO; };
	int getCredit() { return credit; };
	void setName(string inputName) { courseName = inputName; };
	void setNO(string inputNO) { courseNO = inputNO; };
	void setCredit(int inputCredit) { credit = inputCredit; };
	
	virtual void setCourse();//���ÿγ���Ϣ
	virtual void printCourse() = 0;//��ӡ�γ���Ϣ
	virtual void modifyCourse() = 0;//�޸Ŀγ���Ϣ
};