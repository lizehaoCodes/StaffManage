#pragma once;
#include<iostream>
using namespace std;

//ְ���������
class Worker {
public:

	int m_id;//ְ�����
	string m_name;//ְ������
	int m_part;//�������ű��

	//��ʾ������Ϣ
	virtual void showinfo() = 0;
	//��ȡ��λ����
	virtual string getDeptName() = 0;

};