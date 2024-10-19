#include"WorkerManager.h"

//初始化属性
WorkerManager::WorkerManager() {
	//判断文件是否存在
	//1.文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open()) {

		this->m_WorkerNum = 0;//初始化记录人数
		this->m_WorkerArray = NULL;//初始化数组指针
		this->m_File_IsEmpty = true;//初始化文件为空

		ifs.close();
		return;
	}

	//2.文件存在，数据为空
	char c;
	ifs >> c;//读取一个字符

	if (ifs.eof()) {//（end of file)随机输入打开的文件末尾时，返回一个整数值True

		this->m_WorkerNum = 0;//初始化记录人数
		this->m_WorkerArray = NULL;//初始化数组指针
		this->m_File_IsEmpty = true;//初始化文件为空

		ifs.close();
		return;
	}

	//3.文件存在，并记录数据
	int num = this->get_Num();
	cout << "*************|当前职工人数：" << num<<"|**************" << endl; //测试代码
	this->m_WorkerNum = num; //通过文件，更新人数


	this->m_WorkerArray = new Worker * [this->m_WorkerNum];	//开辟空间
	this->init_worker();//初始化文件内的职工


}    

//析构函数
WorkerManager::~WorkerManager() {
	if (this->m_WorkerArray != NULL) {

		for (int i = 0; i < this->m_WorkerNum; i++) {
			if (this->m_WorkerArray[i] != NULL) {

				delete this->m_WorkerArray[i];//删除堆区的每个职工对象
				//针对数组中的每个元素进行删除，确保每个职工对象都被正确释放

			}
		}

		delete[] this->m_WorkerArray;//删除堆区数组指针
		//针对整个数组指针进行删除，确保数组指针不再指向堆区内存
		this->m_WorkerArray = NULL;

	}
}

//展示菜单
void WorkerManager::show_menu() {
	cout << "********************************************" << endl;
	cout << "********* 欢迎使用职工管理系统！ ***********" << endl;
	cout << "************* 0.退出管理程序 ***************" << endl;
	cout << "************* 1.增加职工信息 ***************" << endl;
	cout << "************* 2.显示职工信息 ***************" << endl;
	cout << "************* 3.删除离职职工 ***************" << endl;
	cout << "************* 4.修改职工信息 ***************" << endl;
	cout << "************* 5.查找职工信息 ***************" << endl;
	cout << "************* 6.按照编号排序 ***************" << endl;
	cout << "************* 7.清空所有文档 ***************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//退出菜单
void WorkerManager::ExitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);//退出程序
}

//添加职工
void WorkerManager::Add_Worker() {

	cout << "请输入添加的职工数量：" << endl;

	int addNum = 0;//新添加的员工数
	cin >> addNum;

	if (addNum > 0) {

		//新空间大小=原人数+新增人数
		int newSize = this->m_WorkerNum + addNum;

		//开辟新空间
		Worker** newSpace = new Worker* [newSize];

		//将之前的职工数据，转移到新空间下
		if (this->m_WorkerArray != NULL) {
			for (int i = 0; i < this->m_WorkerNum; i++) {
				newSpace[i] = this->m_WorkerArray[i];
			}
		}
		
		for (int i = 0; i < addNum; i++) {//批量添加新数据

			int new_id=0;//职工编号
			string new_name;//职工姓名
			int new_apart=0;//所属部门

			cout << "请输入第" << i + 1 << "个新职工的编号： " << endl;
			cin >> new_id;

			cout << "请输入第" << i + 1 << "个新职工的姓名： " << endl;
			cin >> new_name;


			while(true){
				cout << "请输入该职工所属的岗位：" << endl;
				cout << "1-------------普通职工" << endl;
				cout << "2-------------项目经理" << endl;
				cout << "3-------------公司总裁" << endl;

				cin >> new_apart;
		
				if (new_apart == 1 || new_apart == 2 || new_apart == 3) {

					break;//跳出循环

				}
				else {

					cout << "请按照提示重新输入" << endl;

					system("pause");
					system("cls");
				}
			}

			Worker* worker = NULL;//初始化派生类对象

			switch (new_apart)
			{
			case 1:
				worker = new Employee(new_id, new_name, 1);
				break;
			case 2:
				worker = new Manager(new_id, new_name, 2);
				break;
			case 3:
				worker = new Boss(new_id, new_name, 3);
				break;
			default:
				break;
			}

			//将新创建的职工指针，保存到数组中
			newSpace[this->m_WorkerNum + i] = worker;

		}


		delete[] this->m_WorkerArray;//释放原来的空间
		this->m_WorkerArray = newSpace;//更改新空间的指针
		this->m_WorkerNum = newSize;//更新职工人数


		this->save_file();//添加数据到文件
		this->m_File_IsEmpty = false;//更新文件不为空


		cout << "您已成功添加" << addNum << "名新职工！" << endl;


		system("pause");
		system("cls");
	}
	else{
		cout << "输入有误" << endl;
		system("pause");
		system("cls");
	}

}

//保存文件
void WorkerManager::save_file() {
	ofstream ofs(FILENAME, ios::out);
	for (int i  = 0; i < this->m_WorkerNum; i++) {
		ofs <<this->m_WorkerArray[i]->m_id << "\t"
			<< this->m_WorkerArray[i]->m_name << "\t"
			<<this->transform_info(this->m_WorkerArray[i]->m_part) << "\t" << endl;
			//<< this->m_WorkerArray[i]->m_part << endl;
	}
	ofs.close();
}

//转换岗位信息到文件
string WorkerManager::transform_info(int part) {
	if (part == 1) {
		return string("普通职工");
	}
	else if (part == 2) {
		return string("项目经理");
	}
	else if (part == 3) {
		return string("公司总裁");
	}
	else {
		return string("未知职位");
	}
}

//统计文件中的人数
int WorkerManager::get_Num(){
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;//编号
	string name;//姓名
	string apartment;//部门

	int num = 0;//统计人数变量
	while (ifs >> id&&ifs>>name&&ifs>>apartment) {
		num++;
	}  
	ifs.close();
	return num;
}

//初始化文件内的职工
void WorkerManager::init_worker() {

	ifstream ifs(FILENAME, ios::in);

	int id;
	string name;
	string apartment;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> apartment) {

		Worker* worker = NULL;//初始化派生类对象

		if (apartment == "普通职工") {
			worker = new Employee(id, name, 1);
		}
		else if (apartment == "项目经理") {
			worker = new Manager(id, name, 2);
		}
		else {
			worker = new Boss(id, name, 3);
		}

		this->m_WorkerArray[index] = worker;

		index++;
	}

	//关闭文件
	ifs.close();

}

//显示职工
void WorkerManager::show_worker() {
	if (this->m_File_IsEmpty) {
		cout << "职工文件不存在或记录为空！" << endl;
	}
	else {
		cout << "职工的信息如下：" << endl;
		for (int i = 0; i < this->m_WorkerNum; i++) {
			//利用多态，调用子类对象的接口
			this->m_WorkerArray[i]->showinfo();
		}
	}

	system("pause");
	system("cls");

}

//判断职工是否存在(存在返回位置，否则返回-1）
int WorkerManager::exist(int id) {//根据职工编号判断

	for (int i = 0; i < this->m_WorkerNum; i++) {

		if (this->m_WorkerArray[i]->m_id == id) {

			return i;

		}
	}
	return -1;
}

//删除职工
void WorkerManager::del_worker() {
	if (this->m_File_IsEmpty) {
		cout << "职工文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
	}
	else {
		//按照员工的编号来删除职工
		cout << "请输入要删除的员工编号：" << endl;

		int id = 0;//职工编号
		cin >> id;

		int index=this->exist(id);//首先判断存在

		if (index != -1) {//职工存在，删除index位置上的职工
			for (int i = index; i < this->m_WorkerNum - 1; i++) {

				this->m_WorkerArray[i] = this->m_WorkerArray[i + 1];//数据前移

			}

			this->m_WorkerNum--;//更新数组人员个数
			this->save_file();//同步到文件

			cout << "删除成功" << endl;
		}
		else {
			cout << "删除失败，未找到该职工" << endl;
		}

		system("pause");
		system("cls");
	}
	      
}

//修改职工
void WorkerManager::modify_worker() {
	if (this->m_File_IsEmpty) {
		cout << "职工文件为空或数据不存在" << endl;
	}
	else {
		cout << "请输入您要修改的职工号：" << endl;
		int id = 0;
		cin >> id;
	//判断职工是否存在
		int result=this->exist(id);
		if (result != -1) {
			delete this->m_WorkerArray[result];

			int new_id = 0;
			string new_name = "";
			int new_apart = 0;

			cout << "已查到： " << id << "号职工，请输入新的职工编号： " << endl;
			cin >> new_id;

			cout << "请输入新的职工姓名：" << endl;
			cin >> new_name;

			while(true){
				cout << "请输入新的职工岗位岗位：" << endl;
				cout << "1-------------普通职工" << endl;
				cout << "2-------------项目经理" << endl;
				cout << "3-------------公司总裁" << endl;

				cin >> new_apart;
				if (new_apart == 1 || new_apart == 2 || new_apart == 3) {
					break;
				}
				else {
					cout << "请按照提示重新输入：" << endl;

					system("pause");
					system("cls");
				}
			}
			Worker* worker = NULL;
			switch (new_apart)
			{
			case 1:
				worker = new Employee(new_id, new_name, new_apart);
				break;
			case 2:
				worker = new Manager(new_id, new_name, new_apart);
				break;
			case 3:
				worker = new Boss(new_id, new_name, new_apart);
			default:
				cout << "数据错误" << endl;
				break;
			}

			//更新数据到数组中
			this->m_WorkerArray[result] = worker;
			
			//保存到文件
			this->save_file();

			cout << "修改成功：" << this->m_WorkerArray[result]->m_id << endl;
		}
		else {
			cout << "查无此人，修改失败" << endl;
		}
	}

	system("pause");
	system("cls");
	
}

//查找职工
void WorkerManager::find_worker() {

	if (this->m_File_IsEmpty) {

		cout << "职工文件不存在或数据为空" << endl;

	}

	else {
		cout << "请输入查找的方式:" << endl;
		cout << "1-----按职工编号查找" << endl;
		cout << "2-----按职工姓名查找" << endl;

		int select = 0;
		cin >> select;
		
		if (select == 1) {

			int id = 0;
			cout << "请输入职工编号：" << endl;
			cin >> id;

			int ret = this->exist(id);
			if (ret != -1) {

				cout << "查找成功，该员工的信息如下：" << endl;
				this->m_WorkerArray[ret]->showinfo();

			}
			else {
				cout << "查无此人" << endl;
			}
		}
		else if (select == 2) {

			string name;
			cout << "请输入员工姓名：" << endl;
			cin >> name;


			//判断for循环，是否查找到职工的标志
			bool flag = false;//默认未找到

			for (int i = 0; i < this->m_WorkerNum; i++) {
				 
				if (this->m_WorkerArray[i]->m_name == name) {

					cout << "查找成功，" << this->m_WorkerArray[i]->m_id << "号职工的信息如下：" << endl;
					this->m_WorkerArray[i]->showinfo();

					cout << endl;

					flag = true;//成功查找到
				}
			}
			if (flag == 0) {

				cout << "查无此人" << endl;

			}
		}
		else {
			cout << "输入的选项有误" << endl;
		}
	}

	//按任意键清屏
	system("pause");
	system("cls");


}

//排序职工（选择排序）
void WorkerManager::sort_worker() {
	if (this->m_File_IsEmpty) {
		cout << "职工文件不存在或数据为空" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "请选择排序的方式：" << endl;
		cout << "1.按职工编号进行升序排列" << endl;
		cout << "2.按职工编号进行降序排列" << endl;

		int select = 0;
		cin >> select;

		for (int i = 0; i < this->m_WorkerNum; i++) {

			int min_or_max = i;//声明 最小值 或 最大值的下标

			for (int j = i + 1; j < this->m_WorkerNum; j++) {
				if (select == 1) {//升序
					if (this->m_WorkerArray[min_or_max]->m_id > this->m_WorkerArray[j]->m_id) {
						min_or_max = j;//更新最小值下标
					}
				}
				else if(select==2){//降序
					if (this->m_WorkerArray[min_or_max]->m_id < this->m_WorkerArray[j]->m_id) {
						min_or_max = j;//更新最大值下标
					}

				}
			}
			if (i != min_or_max) {//让第i个下标元素为 最小值 或 最大值
				Worker* temp = this->m_WorkerArray[i];
				this->m_WorkerArray[i] = this->m_WorkerArray[min_or_max];
				this->m_WorkerArray[min_or_max] = temp;
			}
		}

		cout << "排序成功，排序后的结果为：" << endl;

		this->show_worker();
		//保存到文件
		this->save_file();
	}

}

//清空文件
void  WorkerManager::clean_file() {
	if (this->m_File_IsEmpty) {
		cout << "文件已是空文件，无需再次清空" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "是否确认清空文件" << endl;
	cout << "1----------确定" << endl;
	cout << "2----------取消" << endl;

	int select = 0;
	cin >> select;
	
	if (select == 1) {

		ofstream ofs(FILENAME, ios::trunc);//删除文件后，重新创建
		ofs.close();

		if (this->m_WorkerArray != NULL) {
			for (int i = 0; i < this->m_WorkerNum; i++) {

				delete this->m_WorkerArray[i];//删除堆区的每个职工对象
				//针对数组中的每个元素进行删除，确保每个职工对象都被正确释放
			}

			delete[]this->m_WorkerArray;//删除堆区数组指针
		//针对整个数组指针进行删除，确保数组指针不再指向堆区内存
			this->m_WorkerArray = NULL;
			this->m_WorkerNum = 0;
			this->m_File_IsEmpty = true;	

		}

		cout << "文件删除成功" << endl;
		system("pause");
		system("cls");

	}
	else  {
		cout << "删除操作已经取消" << endl;
		system("pause");
		system("cls");
	}
}
