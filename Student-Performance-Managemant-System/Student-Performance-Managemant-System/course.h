/*filename:course.h
description:�γ��������*/

#pragma once

#include "base.h"
#include <string>
using namespace std;
//�γ���
class course :public base
{
private:
	bool state;//true:���� false:ѡ��
	bool isPF;//�Ʒַ�ʽ:true:PF false:GPA

public:
	course();
	~course();

	bool getState() { return state; };
	bool getPF() { return isPF; };
	void changeState();//�л�����/ѡ��
	bool changePF();//�л��Ʒַ�ʽ

	virtual void setCourse();//���ÿγ���Ϣ
	virtual void printCourse();//��ӡ�γ���Ϣ
	virtual void modifyCourse();//�޸Ŀγ���Ϣ
};