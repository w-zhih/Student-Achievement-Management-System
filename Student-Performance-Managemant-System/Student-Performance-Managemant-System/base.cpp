/*filename:base.cpp
description:�����γ���Ķ���*/

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
	cout << "         <¼��γ���Ϣ>" << endl;
	cout << "������γ���:";
	cin >> info;
	setName(info);
	cout << "������γ̺�:";
	cin >> info;
	setNO(info);
	cout << "������γ�ѧ��:";
	cin >> n;
	while (n <= 0) {
		cout << "���벻�Ϸ�,����������:" << endl;
		cin >> n;
	}
	setCredit(n);
}