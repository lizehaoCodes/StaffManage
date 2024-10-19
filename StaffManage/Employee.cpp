#include"Employee.h"

Employee::Employee(int id, string name, int Did)//构造函数
{
	this->m_id = id;
	this->m_name = name;
	this->m_part = Did;
}
void Employee::showinfo()//显示个人信息
{
	cout << "职工编号：" << this->m_id
		<< "\t职工姓名：" << this->m_name
		<< "\t所属岗位：" << this->getDeptName()
		<< "\t岗位职责：完成经理交给的任务" << endl;

}
string Employee::getDeptName()//获取岗位名称
{
	return string("普通员工");
}