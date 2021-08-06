/*filename:userinterface.h
description:�û��ӿ��������*/

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
	//�����뽻��������
	bool running();
	//���˵�
	void mainMenu();
	//����ѧ������
	void manageStu();
	//¼��ɼ���Ϣ
	void enterScore();
	//�����ɼ���Ϣ
	void searchScore();
	//����ɼ���Ϣ(���������˵�,return false)
	bool manageScore(node<student>* stu);
	//�˳�����
	void quit();
	//��ͣ����
	void pause();
};