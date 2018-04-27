#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <map>
// #include "curl/curl.h"
// #include "cJSON.h"
using namespace std;

int main()
{
    map<string,int> mymap;
    mymap["zhangzuoyun"]=18;
    mymap.insert(pair<string,int>("shabiping",27));
    mymap.insert(make_pair("shenyue",19));
    map<string,int>::iterator it=mymap.find("zhangzuoyun");
    if(it==mymap.end())
    {
        cout<<"can not find this key";
    }
    
    cout<<it->first<<it->second<<endl;
    return 0;

}
/*void test()
{
    char *fid="3,1979ea2eaf";
    char *url="118.24.3.132:8081";

    int len=strlen(fid)+strlen(url)+2;
    printf("%d\n",len);
    char *publicUrl=(char *)malloc(sizeof(char)*len);
    memset(publicUrl,'\0',len);
    snprintf(publicUrl,len,"%s/%s",url,fid);
    printf("%s\n",publicUrl);
    printf("%d\n",strlen(publicUrl));
}



int main(int argc,char *argv[])
{
     CURL *curl;
     curl_global_init(CURL_GLOBAL_ALL);
     curl=curl_easy_init();
     curl_easy_setopt(curl,CURLOPT_URL,"latermarch.xyz/handlesql?param=\"insert into fileinfo(fid,publicurl,filename,size,username)values('3,017cf1e119','latermarch.club','fuckme.png','1435435','zhangzuoyun');\" ");
     // if((fp=fopen("record","w"))==NULL)
     // {   
     //    curl_easy_cleanup(curl);
     //    exit(1);
     // }   
    
  
     curl_easy_perform(curl);
     curl_easy_cleanup(curl);
     exit(0);
 

} 
*/
/*
int main()
{
    string tempUrl=(string)"latermarch.xyz" + "/handlesql?param="+"fucklyou";
    string sql= "\"insert into fileinfo(filename,publicurl,fid,size,username)values('fuckme.png','latermarch.club','3,017cf1e119','1435435','latermarch');\"";
    string url=tempUrl+sql;
    cout<<url<<endl;
    return 0;
}

int test4()
{


    string s = "\r\n\t \t这是随便写的一句话。\t\t ";
    cout<< s.size()<<endl;
    size_t n = s.find_last_not_of( " \r\n\t" );
   
    if( n != string::npos )
    {
        s.erase( n + 1 , s.size() - n );
    }
    cout<<s.size()<<endl;
     n = s.find_first_not_of ( " \r\n\t" );
    cout<<n<<endl;
    if( n != string::npos )
    {
        // s.erase( s.begin()+1 , s.begin()+n);
        s.erase( 1 , n);
        
    }
    cout<<s<<endl;


}



int test5()
{

    char *a="0fd";
    if(a[0]=='0')
    {
        cout<<"fuck"<<endl;
    }
}
*/

// g++ test2.c cJSON.c  -DCURL_STATICLIB -I include -L lib -lcurl -lwldap32 -lws2_32  -o fuck
// 
