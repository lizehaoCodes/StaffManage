#include<iostream>
using namespace std;

#include"WorkerManager.h"

#include"Worker.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"

int main() {
	//ʵ���������߶���
	WorkerManager wm;
	int choice = 0;//�û�ѡ��
	while (true) {
		wm.show_menu();
		cout << "***����������ѡ��***" << endl;
		cin >> choice;//�����û�ѡ��
		switch (choice)
		{
		case 0://�˳�ϵͳ
			wm.ExitSystem();
			break;
		case 1://���ְ��
			wm.Add_Worker();
			break;
		case 2://��ʾְ��
			wm.show_worker();
			break;
		case 3://ɾ��ְ��
			wm.del_worker();
			break;
		case 4://�޸�ְ��
			wm.modify_worker();
			break;
		case 5://����ְ��
			wm.find_worker();
			break;
		case 6://����ְ��
			wm.sort_worker();
			break;
		case 7://����ļ�
			wm.clean_file();
			break;
		default:
			system("cls");//����
			break;
		}
	}
	system("pause");
	return 0;
}