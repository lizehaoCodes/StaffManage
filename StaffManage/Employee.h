#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

//Ա����
class Employee : public Worker {
public:

	//���캯��
	Employee(int id, string name, int part);

	//��ʾ������Ϣ
	virtual void showinfo();
	//��ȡ��λ����
	virtual string getDeptName();
};