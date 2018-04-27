#include "mysqlmanage.h"
mysqlmanage::mysqlmanage()
{
	mysql_init(&m_mysql);
}
mysqlmanage::~mysqlmanage()
{
	Close();
}
int mysqlmanage::Connect(string hostAddress, string userName, string password, string dbName, int port)
{
	if (hostAddress.empty() || userName.empty() || password.empty() || dbName.empty())
	{
		return MYSQL_MSG_EMPTY;
	}
	if (mysql_real_connect(&m_mysql, hostAddress.c_str(), userName.c_str(), password.c_str(), dbName.c_str(),
		port, NULL, 0))
	{
		mysql_query(&m_mysql, "set names gbk"); //设置gbk编码格式,否则在cmd下无法显示中文
		return MYSQL_CONNECT_SUCCESS;
	}
	return MYSQL_CONNECT_ERROR;
}
bool mysqlmanage::SelectDataBase(string dbName)
{
	if (mysql_select_db(&m_mysql, dbName.c_str()) != 0)
	{
		return false;
	}
	return true;
}
void mysqlmanage::Close()
{
	mysql_close(&m_mysql);
}
MYSQL* mysqlmanage::GetMysqlObject()
{
	return &m_mysql;
}


//----------------------------CDBCommand-------------------------------
CDBCommand::CDBCommand(MYSQL* mysql) :m_ptMysql(mysql)
{
}
CDBCommand::~CDBCommand()
{
	Clear();
}
void CDBCommand::FreeDataList()
{
	int count = m_resultList.size();
	for (int i = count - 1; i >= 0; i--)
	{
		delete m_resultList[i];
		m_resultList.clear();
	}
}
bool CDBCommand::Command(string sql)
{
	if (mysql_query(m_ptMysql, sql.c_str()) != 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}


//----------------------------SelectResult-------------------------------
SelectResult* CDBCommand::GetResult()
{
	MYSQL_ROW row;
	MYSQL_RES* res_set;
	res_set = mysql_store_result(m_ptMysql);
	if (res_set == NULL)
	{
		return NULL;
	}
	vector<vector<string>> dataList;
	int rowCount = 0;
	while ((row = mysql_fetch_row(res_set)) != NULL)
	{
		vector<string> list;
		for (size_t i = 0; i < mysql_num_fields(res_set); i++)
		{
			if (row[i]==NULL)
			{
				list.push_back("null");//修改版，如果出现空字段就会出现这个问题
			}
			else
			{
				list.push_back(row[i]);

			}
		}
		dataList.push_back(list);
		++rowCount;
	}
	SelectResult* result = new SelectResult(dataList);
	result->SetColCount(mysql_num_fields(res_set));
	result->SetRowCount(rowCount);
	m_resultList.push_back(result);
	mysql_free_result(res_set);
	return result;
}

void CDBCommand::Clear()
{
	FreeDataList();
}




SelectResult::SelectResult()
{
	//构造函数为空
}

SelectResult::SelectResult(vector<vector<string>> tempList)
{
	for (vector<vector<string>>::iterator it = tempList.begin(); it != tempList.end(); it++)
	{
		vector<string> temp(it->size());
		std::copy(it->begin(), it->end(), temp.begin());
		m_dataList.push_back(temp);
	}
}
SelectResult::~SelectResult()
{
	//析构函数为空
}
string SelectResult::GetDataAt(int row, int col)
{
	if (row > m_numRow || row < 0 || col > m_numCol || col < 0)
	{
		return "#Error#";
	}
	else
	{
		return m_dataList[row][col];
	}
}
int SelectResult::GetRowCount()
{
	return m_numRow;
}
int SelectResult::GetColCount()
{
	return m_numCol;
}
void SelectResult::SetRowCount(int rowCount)
{
	m_numRow = rowCount;
}
void SelectResult::SetColCount(int colCount)
{
	m_numCol = colCount;
}
