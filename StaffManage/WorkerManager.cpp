#include"WorkerManager.h"

//��ʼ������
WorkerManager::WorkerManager() {
	//�ж��ļ��Ƿ����
	//1.�ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open()) {

		this->m_WorkerNum = 0;//��ʼ����¼����
		this->m_WorkerArray = NULL;//��ʼ������ָ��
		this->m_File_IsEmpty = true;//��ʼ���ļ�Ϊ��

		ifs.close();
		return;
	}

	//2.�ļ����ڣ�����Ϊ��
	char c;
	ifs >> c;//��ȡһ���ַ�

	if (ifs.eof()) {//��end of file)�������򿪵��ļ�ĩβʱ������һ������ֵTrue

		this->m_WorkerNum = 0;//��ʼ����¼����
		this->m_WorkerArray = NULL;//��ʼ������ָ��
		this->m_File_IsEmpty = true;//��ʼ���ļ�Ϊ��

		ifs.close();
		return;
	}

	//3.�ļ����ڣ�����¼����
	int num = this->get_Num();
	cout << "*************|��ǰְ��������" << num<<"|**************" << endl; //���Դ���
	this->m_WorkerNum = num; //ͨ���ļ�����������


	this->m_WorkerArray = new Worker * [this->m_WorkerNum];	//���ٿռ�
	this->init_worker();//��ʼ���ļ��ڵ�ְ��


}    

//��������
WorkerManager::~WorkerManager() {
	if (this->m_WorkerArray != NULL) {

		for (int i = 0; i < this->m_WorkerNum; i++) {
			if (this->m_WorkerArray[i] != NULL) {

				delete this->m_WorkerArray[i];//ɾ��������ÿ��ְ������
				//��������е�ÿ��Ԫ�ؽ���ɾ����ȷ��ÿ��ְ�����󶼱���ȷ�ͷ�

			}
		}

		delete[] this->m_WorkerArray;//ɾ����������ָ��
		//�����������ָ�����ɾ����ȷ������ָ�벻��ָ������ڴ�
		this->m_WorkerArray = NULL;

	}
}

//չʾ�˵�
void WorkerManager::show_menu() {
	cout << "********************************************" << endl;
	cout << "********* ��ӭʹ��ְ������ϵͳ�� ***********" << endl;
	cout << "************* 0.�˳�������� ***************" << endl;
	cout << "************* 1.����ְ����Ϣ ***************" << endl;
	cout << "************* 2.��ʾְ����Ϣ ***************" << endl;
	cout << "************* 3.ɾ����ְְ�� ***************" << endl;
	cout << "************* 4.�޸�ְ����Ϣ ***************" << endl;
	cout << "************* 5.����ְ����Ϣ ***************" << endl;
	cout << "************* 6.���ձ������ ***************" << endl;
	cout << "************* 7.��������ĵ� ***************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//�˳��˵�
void WorkerManager::ExitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);//�˳�����
}

//���ְ��
void WorkerManager::Add_Worker() {

	cout << "��������ӵ�ְ��������" << endl;

	int addNum = 0;//����ӵ�Ա����
	cin >> addNum;

	if (addNum > 0) {

		//�¿ռ��С=ԭ����+��������
		int newSize = this->m_WorkerNum + addNum;

		//�����¿ռ�
		Worker** newSpace = new Worker* [newSize];

		//��֮ǰ��ְ�����ݣ�ת�Ƶ��¿ռ���
		if (this->m_WorkerArray != NULL) {
			for (int i = 0; i < this->m_WorkerNum; i++) {
				newSpace[i] = this->m_WorkerArray[i];
			}
		}
		
		for (int i = 0; i < addNum; i++) {//�������������

			int new_id=0;//ְ�����
			string new_name;//ְ������
			int new_apart=0;//��������

			cout << "�������" << i + 1 << "����ְ���ı�ţ� " << endl;
			cin >> new_id;

			cout << "�������" << i + 1 << "����ְ���������� " << endl;
			cin >> new_name;


			while(true){
				cout << "�������ְ�������ĸ�λ��" << endl;
				cout << "1-------------��ְͨ��" << endl;
				cout << "2-------------��Ŀ����" << endl;
				cout << "3-------------��˾�ܲ�" << endl;

				cin >> new_apart;
		
				if (new_apart == 1 || new_apart == 2 || new_apart == 3) {

					break;//����ѭ��

				}
				else {

					cout << "�밴����ʾ��������" << endl;

					system("pause");
					system("cls");
				}
			}

			Worker* worker = NULL;//��ʼ�����������

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

			//���´�����ְ��ָ�룬���浽������
			newSpace[this->m_WorkerNum + i] = worker;

		}


		delete[] this->m_WorkerArray;//�ͷ�ԭ���Ŀռ�
		this->m_WorkerArray = newSpace;//�����¿ռ��ָ��
		this->m_WorkerNum = newSize;//����ְ������


		this->save_file();//������ݵ��ļ�
		this->m_File_IsEmpty = false;//�����ļ���Ϊ��


		cout << "���ѳɹ����" << addNum << "����ְ����" << endl;


		system("pause");
		system("cls");
	}
	else{
		cout << "��������" << endl;
		system("pause");
		system("cls");
	}

}

//�����ļ�
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

//ת����λ��Ϣ���ļ�
string WorkerManager::transform_info(int part) {
	if (part == 1) {
		return string("��ְͨ��");
	}
	else if (part == 2) {
		return string("��Ŀ����");
	}
	else if (part == 3) {
		return string("��˾�ܲ�");
	}
	else {
		return string("δְ֪λ");
	}
}

//ͳ���ļ��е�����
int WorkerManager::get_Num(){
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;//���
	string name;//����
	string apartment;//����

	int num = 0;//ͳ����������
	while (ifs >> id&&ifs>>name&&ifs>>apartment) {
		num++;
	}  
	ifs.close();
	return num;
}

//��ʼ���ļ��ڵ�ְ��
void WorkerManager::init_worker() {

	ifstream ifs(FILENAME, ios::in);

	int id;
	string name;
	string apartment;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> apartment) {

		Worker* worker = NULL;//��ʼ�����������

		if (apartment == "��ְͨ��") {
			worker = new Employee(id, name, 1);
		}
		else if (apartment == "��Ŀ����") {
			worker = new Manager(id, name, 2);
		}
		else {
			worker = new Boss(id, name, 3);
		}

		this->m_WorkerArray[index] = worker;

		index++;
	}

	//�ر��ļ�
	ifs.close();

}

//��ʾְ��
void WorkerManager::show_worker() {
	if (this->m_File_IsEmpty) {
		cout << "ְ���ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		cout << "ְ������Ϣ���£�" << endl;
		for (int i = 0; i < this->m_WorkerNum; i++) {
			//���ö�̬�������������Ľӿ�
			this->m_WorkerArray[i]->showinfo();
		}
	}

	system("pause");
	system("cls");

}

//�ж�ְ���Ƿ����(���ڷ���λ�ã����򷵻�-1��
int WorkerManager::exist(int id) {//����ְ������ж�

	for (int i = 0; i < this->m_WorkerNum; i++) {

		if (this->m_WorkerArray[i]->m_id == id) {

			return i;

		}
	}
	return -1;
}

//ɾ��ְ��
void WorkerManager::del_worker() {
	if (this->m_File_IsEmpty) {
		cout << "ְ���ļ������ڻ��¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else {
		//����Ա���ı����ɾ��ְ��
		cout << "������Ҫɾ����Ա����ţ�" << endl;

		int id = 0;//ְ�����
		cin >> id;

		int index=this->exist(id);//�����жϴ���

		if (index != -1) {//ְ�����ڣ�ɾ��indexλ���ϵ�ְ��
			for (int i = index; i < this->m_WorkerNum - 1; i++) {

				this->m_WorkerArray[i] = this->m_WorkerArray[i + 1];//����ǰ��

			}

			this->m_WorkerNum--;//����������Ա����
			this->save_file();//ͬ�����ļ�

			cout << "ɾ���ɹ�" << endl;
		}
		else {
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}

		system("pause");
		system("cls");
	}
	      
}

//�޸�ְ��
void WorkerManager::modify_worker() {
	if (this->m_File_IsEmpty) {
		cout << "ְ���ļ�Ϊ�ջ����ݲ�����" << endl;
	}
	else {
		cout << "��������Ҫ�޸ĵ�ְ���ţ�" << endl;
		int id = 0;
		cin >> id;
	//�ж�ְ���Ƿ����
		int result=this->exist(id);
		if (result != -1) {
			delete this->m_WorkerArray[result];

			int new_id = 0;
			string new_name = "";
			int new_apart = 0;

			cout << "�Ѳ鵽�� " << id << "��ְ�����������µ�ְ����ţ� " << endl;
			cin >> new_id;

			cout << "�������µ�ְ��������" << endl;
			cin >> new_name;

			while(true){
				cout << "�������µ�ְ����λ��λ��" << endl;
				cout << "1-------------��ְͨ��" << endl;
				cout << "2-------------��Ŀ����" << endl;
				cout << "3-------------��˾�ܲ�" << endl;

				cin >> new_apart;
				if (new_apart == 1 || new_apart == 2 || new_apart == 3) {
					break;
				}
				else {
					cout << "�밴����ʾ�������룺" << endl;

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
				cout << "���ݴ���" << endl;
				break;
			}

			//�������ݵ�������
			this->m_WorkerArray[result] = worker;
			
			//���浽�ļ�
			this->save_file();

			cout << "�޸ĳɹ���" << this->m_WorkerArray[result]->m_id << endl;
		}
		else {
			cout << "���޴��ˣ��޸�ʧ��" << endl;
		}
	}

	system("pause");
	system("cls");
	
}

//����ְ��
void WorkerManager::find_worker() {

	if (this->m_File_IsEmpty) {

		cout << "ְ���ļ������ڻ�����Ϊ��" << endl;

	}

	else {
		cout << "��������ҵķ�ʽ:" << endl;
		cout << "1-----��ְ����Ų���" << endl;
		cout << "2-----��ְ����������" << endl;

		int select = 0;
		cin >> select;
		
		if (select == 1) {

			int id = 0;
			cout << "������ְ����ţ�" << endl;
			cin >> id;

			int ret = this->exist(id);
			if (ret != -1) {

				cout << "���ҳɹ�����Ա������Ϣ���£�" << endl;
				this->m_WorkerArray[ret]->showinfo();

			}
			else {
				cout << "���޴���" << endl;
			}
		}
		else if (select == 2) {

			string name;
			cout << "������Ա��������" << endl;
			cin >> name;


			//�ж�forѭ�����Ƿ���ҵ�ְ���ı�־
			bool flag = false;//Ĭ��δ�ҵ�

			for (int i = 0; i < this->m_WorkerNum; i++) {
				 
				if (this->m_WorkerArray[i]->m_name == name) {

					cout << "���ҳɹ���" << this->m_WorkerArray[i]->m_id << "��ְ������Ϣ���£�" << endl;
					this->m_WorkerArray[i]->showinfo();

					cout << endl;

					flag = true;//�ɹ����ҵ�
				}
			}
			if (flag == 0) {

				cout << "���޴���" << endl;

			}
		}
		else {
			cout << "�����ѡ������" << endl;
		}
	}

	//�����������
	system("pause");
	system("cls");


}

//����ְ����ѡ������
void WorkerManager::sort_worker() {
	if (this->m_File_IsEmpty) {
		cout << "ְ���ļ������ڻ�����Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "��ѡ������ķ�ʽ��" << endl;
		cout << "1.��ְ����Ž�����������" << endl;
		cout << "2.��ְ����Ž��н�������" << endl;

		int select = 0;
		cin >> select;

		for (int i = 0; i < this->m_WorkerNum; i++) {

			int min_or_max = i;//���� ��Сֵ �� ���ֵ���±�

			for (int j = i + 1; j < this->m_WorkerNum; j++) {
				if (select == 1) {//����
					if (this->m_WorkerArray[min_or_max]->m_id > this->m_WorkerArray[j]->m_id) {
						min_or_max = j;//������Сֵ�±�
					}
				}
				else if(select==2){//����
					if (this->m_WorkerArray[min_or_max]->m_id < this->m_WorkerArray[j]->m_id) {
						min_or_max = j;//�������ֵ�±�
					}

				}
			}
			if (i != min_or_max) {//�õ�i���±�Ԫ��Ϊ ��Сֵ �� ���ֵ
				Worker* temp = this->m_WorkerArray[i];
				this->m_WorkerArray[i] = this->m_WorkerArray[min_or_max];
				this->m_WorkerArray[min_or_max] = temp;
			}
		}

		cout << "����ɹ��������Ľ��Ϊ��" << endl;

		this->show_worker();
		//���浽�ļ�
		this->save_file();
	}

}

//����ļ�
void  WorkerManager::clean_file() {
	if (this->m_File_IsEmpty) {
		cout << "�ļ����ǿ��ļ��������ٴ����" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "�Ƿ�ȷ������ļ�" << endl;
	cout << "1----------ȷ��" << endl;
	cout << "2----------ȡ��" << endl;

	int select = 0;
	cin >> select;
	
	if (select == 1) {

		ofstream ofs(FILENAME, ios::trunc);//ɾ���ļ������´���
		ofs.close();

		if (this->m_WorkerArray != NULL) {
			for (int i = 0; i < this->m_WorkerNum; i++) {

				delete this->m_WorkerArray[i];//ɾ��������ÿ��ְ������
				//��������е�ÿ��Ԫ�ؽ���ɾ����ȷ��ÿ��ְ�����󶼱���ȷ�ͷ�
			}

			delete[]this->m_WorkerArray;//ɾ����������ָ��
		//�����������ָ�����ɾ����ȷ������ָ�벻��ָ������ڴ�
			this->m_WorkerArray = NULL;
			this->m_WorkerNum = 0;
			this->m_File_IsEmpty = true;	

		}

		cout << "�ļ�ɾ���ɹ�" << endl;
		system("pause");
		system("cls");

	}
	else  {
		cout << "ɾ�������Ѿ�ȡ��" << endl;
		system("pause");
		system("cls");
	}
}
