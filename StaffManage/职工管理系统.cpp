#include<iostream>
using namespace std;

#include"WorkerManager.h"

#include"Worker.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"

int main() {
	//实例化管理者对象
	WorkerManager wm;
	int choice = 0;//用户选项
	while (true) {
		wm.show_menu();
		cout << "***请输入您的选择***" << endl;
		cin >> choice;//接受用户选项
		switch (choice)
		{
		case 0://退出系统
			wm.ExitSystem();
			break;
		case 1://添加职工
			wm.Add_Worker();
			break;
		case 2://显示职工
			wm.show_worker();
			break;
		case 3://删除职工
			wm.del_worker();
			break;
		case 4://修改职工
			wm.modify_worker();
			break;
		case 5://查找职工
			wm.find_worker();
			break;
		case 6://排序职工
			wm.sort_worker();
			break;
		case 7://清空文件
			wm.clean_file();
			break;
		default:
			system("cls");//清屏
			break;
		}
	}
	system("pause");
	return 0;
}