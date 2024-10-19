#pragma once //防止头文件重复包含
#include<iostream>//包含输入输出流头文件
using namespace std;//使用标准命名空间

#include"Worker.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"

#include<fstream>
#define FILENAME "职工人员名单.txt"

class WorkerManager {
public:		
	//记录职工人数
	int m_WorkerNum;
	//职工数组指针
	Worker** m_WorkerArray;//数组内存放基类指针，指向不同的派生类对象
	//判断文件是否为空 标志
	bool m_File_IsEmpty;

	//构造函数
	WorkerManager();
	//析构函数
	~WorkerManager();

	//展示菜单
	void show_menu();
	//退出菜单
	void ExitSystem();

	//添加职工
	void Add_Worker();

	//保存文件
	void save_file();
	//转换岗位信息到文件
	string transform_info(int part);
	//统计文件中的人数
	int get_Num();
	//根据文件人数，初始化职工数组
	void init_worker();

	//显示职工
	void show_worker();

	//删除、修改、查找操作前，判断职工是否存在(存在返回位置，否则返回-1）
	int exist(int id);
	//删除职工
	void del_worker();
	//修改职工
	void modify_worker();
	//查找职工
	void find_worker();

	//排序职工
	void sort_worker();

	//清空文件
	void clean_file();



};