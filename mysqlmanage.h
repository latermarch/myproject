#include "mysql.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
#pragma once
// ���ӷ�����ʱ�ķ�����Ϣ
#define MYSQL_MSG_EMPTY 0
#define MYSQL_CONNECT_ERROR -1
#define MYSQL_CONNECT_SUCCESS 1
// ��ȡ��ѯ������Ҫ���ص���������
class SelectResult;
struct dataPos;

class mysqlmanage
{
public:
	mysqlmanage();
	~mysqlmanage();
public:
	int Connect(string hostAddress, string userName, string password, string dbName, int port = 3306); //�������ݿ�����
	bool SelectDataBase(string dbName); //ѡ�����ݿ�
	void Close(); //�ر����ݿ�����
	MYSQL* GetMysqlObject(); //����MYSQL*
private:
	MYSQL m_mysql;
};

//-------------------------������-------------------------------
class CDBCommand
{
public:
	CDBCommand(MYSQL* mysql);
	~CDBCommand();
public:
	bool Command(string sql); //ִ��sql���
	SelectResult* GetResult(); //��ȡ��ѯ���
	void Clear();
private:
	void FreeDataList();
private:
	MYSQL* m_ptMysql;
	MYSQL_RES* m_ptResult;
	vector<SelectResult*> m_resultList;
};


//------------------����һ����ѯ�����---------------------------------
class SelectResult
{
	friend class CDBCommand;
public:
	SelectResult();
	SelectResult(vector<vector<string>> tempList);
	~SelectResult();
	int GetRowCount(); //���ز�ѯ���������
	int GetColCount(); //���ز�ѯ���������
	string GetDataAt(int row, int col); //ȡĳһλ�õ�����
private:
	void SetRowCount(int rowCount);
	void SetColCount(int colCount);
private:
	vector<vector<string>> m_dataList;
	int m_numRow;
	int m_numCol;
};
 


