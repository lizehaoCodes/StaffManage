#pragma once;
#include<iostream>
using namespace std;

//职工抽象基类
class Worker {
public:

	int m_id;//职工编号
	string m_name;//职工姓名
	int m_part;//所属部门编号

	//显示个人信息
	virtual void showinfo() = 0;
	//获取岗位名称
	virtual string getDeptName() = 0;

};