#include"Employee.h"

Employee::Employee(int id, string name, int Did)//���캯��
{
	this->m_id = id;
	this->m_name = name;
	this->m_part = Did;
}
void Employee::showinfo()//��ʾ������Ϣ
{
	cout << "ְ����ţ�" << this->m_id
		<< "\tְ��������" << this->m_name
		<< "\t������λ��" << this->getDeptName()
		<< "\t��λְ����ɾ�����������" << endl;

}
string Employee::getDeptName()//��ȡ��λ����
{
	return string("��ͨԱ��");
}