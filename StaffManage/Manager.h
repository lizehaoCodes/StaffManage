#pragma once;
#include<iostream>
using namespace std;
#include"Worker.h"

//������
class Manager :public Worker {
public:

	//���캯��
	Manager(int id, string name, int part);

	//��ʾ������Ϣ
	virtual void showinfo();
	//��ȡ��λ����
	virtual string getDeptName();
};