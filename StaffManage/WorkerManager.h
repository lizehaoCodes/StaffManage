#pragma once //��ֹͷ�ļ��ظ�����
#include<iostream>//�������������ͷ�ļ�
using namespace std;//ʹ�ñ�׼�����ռ�

#include"Worker.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"

#include<fstream>
#define FILENAME "ְ����Ա����.txt"

class WorkerManager {
public:		
	//��¼ְ������
	int m_WorkerNum;
	//ְ������ָ��
	Worker** m_WorkerArray;//�����ڴ�Ż���ָ�룬ָ��ͬ�����������
	//�ж��ļ��Ƿ�Ϊ�� ��־
	bool m_File_IsEmpty;

	//���캯��
	WorkerManager();
	//��������
	~WorkerManager();

	//չʾ�˵�
	void show_menu();
	//�˳��˵�
	void ExitSystem();

	//���ְ��
	void Add_Worker();

	//�����ļ�
	void save_file();
	//ת����λ��Ϣ���ļ�
	string transform_info(int part);
	//ͳ���ļ��е�����
	int get_Num();
	//�����ļ���������ʼ��ְ������
	void init_worker();

	//��ʾְ��
	void show_worker();

	//ɾ�����޸ġ����Ҳ���ǰ���ж�ְ���Ƿ����(���ڷ���λ�ã����򷵻�-1��
	int exist(int id);
	//ɾ��ְ��
	void del_worker();
	//�޸�ְ��
	void modify_worker();
	//����ְ��
	void find_worker();

	//����ְ��
	void sort_worker();

	//����ļ�
	void clean_file();



};