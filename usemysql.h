#pragma once
#include "mysqlmanage.h"
class usemysql
{
public:
	usemysql();
	~usemysql();
	SelectResult* getsearch(string mysql);
private:
	mysqlmanage mysql;
	CDBCommand *cmd;
};

