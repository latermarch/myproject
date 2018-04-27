#include "mysql.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
#pragma once
// 连接服务器时的返回消息
#define MYSQL_MSG_EMPTY 0
#define MYSQL_CONNECT_ERROR -1
#define MYSQL_CONNECT_SUCCESS 1
// 获取查询语句的需要返回的数据类型
class SelectResult;
struct dataPos;

class mysqlmanage
{
public:
	mysqlmanage();
	~mysqlmanage();
public:
	int Connect(string hostAddress, string userName, string password, string dbName, int port = 3306); //创建数据库连接
	bool SelectDataBase(string dbName); //选择数据库
	void Close(); //关闭数据库连接
	MYSQL* GetMysqlObject(); //返回MYSQL*
private:
	MYSQL m_mysql;
};

//-------------------------命令类-------------------------------
class CDBCommand
{
public:
	CDBCommand(MYSQL* mysql);
	~CDBCommand();
public:
	bool Command(string sql); //执行sql语句
	SelectResult* GetResult(); //获取查询结果
	void Clear();
private:
	void FreeDataList();
private:
	MYSQL* m_ptMysql;
	MYSQL_RES* m_ptResult;
	vector<SelectResult*> m_resultList;
};


//------------------定义一个查询结果类---------------------------------
class SelectResult
{
	friend class CDBCommand;
public:
	SelectResult();
	SelectResult(vector<vector<string>> tempList);
	~SelectResult();
	int GetRowCount(); //返回查询结果的行数
	int GetColCount(); //返回查询结果的列数
	string GetDataAt(int row, int col); //取某一位置的数据
private:
	void SetRowCount(int rowCount);
	void SetColCount(int colCount);
private:
	vector<vector<string>> m_dataList;
	int m_numRow;
	int m_numCol;
};
 


