#pragma once;
#include<iostream>
using namespace std;
#include"Worker.h"

//�ϰ���
class Boss : public Worker {
public:

	//���캯��
	Boss(int id, string name, int part);

	//��ʾ������Ϣ
	virtual void showinfo();
	//��ȡ��λ����
	virtual string getDeptName();
};