#include"Manager.h"

//构造函数
Manager::Manager(int id, string name, int Did) {
	this->m_id = id;
	this->m_name = name;
	this->m_part = Did;
}

//显示个人信息
void Manager::showinfo() {
	cout << "职工编号：" << this->m_id
		<< "\t职工姓名：" << this->m_name
		<< "\t所属岗位：" << this->getDeptName()
		<< "\t岗位职责：将任务下发给员工" << endl;
}
//获取岗位名称
string Manager::getDeptName() {
	return string("项目经理");
}