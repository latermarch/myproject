#include "usemysql.h"
int main()  
{  
    vector<string> name;
    usemysql connectmysql;//连接数据库
    string sql="";
    SelectResult *result;
    sql = "select name from hello_test";
    result = connectmysql.getsearch(sql);

    for (int i = 0; i < result->GetRowCount(); i++)
    {
        name.push_back(result->GetDataAt(i, 0));
    }

    for (auto it : name)
    {
        cout<<it<<endl;
    }
    return 0;  
}