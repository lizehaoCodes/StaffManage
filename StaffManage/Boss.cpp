#include"Boss.h"

//���캯��
Boss::Boss(int id, string name, int Did) {
	this->m_id = id;
	this->m_name = name;
	this->m_part = Did;
}

//��ʾ������Ϣ
void Boss::showinfo() {
	cout << "ְ����ţ�" << this->m_id
		<< "\tְ��������" << this->m_name
		<< "\t������λ��" << this->getDeptName()
		<< "\t��λְ�𣺹���˾����������" << endl;
}
//��ȡ��λ����
string Boss::getDeptName() {
	return string("��˾�ܲ�");
}