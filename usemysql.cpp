#include "usemysql.h"
usemysql::usemysql()
{
	mysql.Connect("192.168.20.90", "root", "123456", "weedfs");
	cmd =new CDBCommand(mysql.GetMysqlObject());
}
usemysql::~usemysql()
{
}
SelectResult* usemysql::getsearch(string mysql)
{
	cmd->Command(mysql);
	return cmd->GetResult();
}