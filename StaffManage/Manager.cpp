#include"Manager.h"

//���캯��
Manager::Manager(int id, string name, int Did) {
	this->m_id = id;
	this->m_name = name;
	this->m_part = Did;
}

//��ʾ������Ϣ
void Manager::showinfo() {
	cout << "ְ����ţ�" << this->m_id
		<< "\tְ��������" << this->m_name
		<< "\t������λ��" << this->getDeptName()
		<< "\t��λְ�𣺽������·���Ա��" << endl;
}
//��ȡ��λ����
string Manager::getDeptName() {
	return string("��Ŀ����");
}