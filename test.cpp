#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include "curl/curl.h"
#include "cJSON.h"
#include "map"
using namespace std;
//curl -F file=@party2.jpg http://192.168.20.90:9333/submit
//上传文件

typedef struct{
    char *fid;
    char *publicUrl;
    char *name;
    char *size;
    char * result;//存储返回结果
}WEED_INFO; //存储认证令牌

typedef struct{

    char *url;
    char *name;
    char *size;
    char * user;//存储返回结果
}FileInfo; //存储认证令牌

size_t get_info_from_body(char *buffer, size_t size, size_t nmemb, void *userdata){
    WEED_INFO *s_context = (WEED_INFO *)userdata;
    char * stemp;
    size_t len;
    // cout<<buffer<<"---------->test"<<endl;
    cJSON * item;
    cJSON * json = cJSON_Parse(buffer);
    if (json!=NULL)
    {

        if(cJSON_HasObjectItem(json,"fid"))
        {
            item=cJSON_GetObjectItem(json,"fid");
            stemp=cJSON_Print(item);
            len=strlen(stemp);
            s_context->fid=(char *)malloc(sizeof(char)*len-2);
            memcpy(s_context->fid,stemp+1,len-2);
        }

        if(cJSON_HasObjectItem(json,"publicUrl"))
        {
            item=cJSON_GetObjectItem(json,"publicUrl");
            stemp=cJSON_Print(item);
            len=strlen(stemp);
            s_context->publicUrl=(char *)malloc(sizeof(char)*len-2);
            memcpy(s_context->publicUrl,stemp+1,len-2);//为了去掉引号而已
        }

        if(cJSON_HasObjectItem(json,"name"))
        {
            item=cJSON_GetObjectItem(json,"name");
            stemp=cJSON_Print(item);
            len=strlen(stemp);
            s_context->name=(char *)malloc(sizeof(char)*len-2);
            memcpy(s_context->name,stemp+1,len-2);//为了去掉引号而已
        }

        if(cJSON_HasObjectItem(json,"size"))
        {
            item=cJSON_GetObjectItem(json,"size");
            stemp=cJSON_Print(item);
            len=strlen(stemp);
            s_context->size=(char *)malloc(sizeof(char)*len);
            memcpy(s_context->size,stemp,len);//没得引号去
        }

        if(cJSON_HasObjectItem(json,"result"))
        {
            item=cJSON_GetObjectItem(json,"result");
            stemp=cJSON_Print(item);
            len=strlen(stemp);
            // cout<<" len "<<len<<" result "<<stemp<<endl;
            s_context->result=(char *)malloc(sizeof(char)*len-2);
            memcpy(s_context->result,stemp+1,len-2);//没得引号去
        }
    }
    return size*nmemb;
}

// curl -F file=@fish.jpg http://118.24.3.132:9333/submit
void upload_part(char *filename,WEED_INFO *info)
{
    int len=strlen(info->fid)+strlen(info->publicUrl)+2;//给 结束符 和 / 留两个单位的空间
    char *url=(char *)malloc(sizeof(char)*len);
    memset(url,'\0',len);
    snprintf(url,len,"%s/%s",info->publicUrl,info->fid);

    CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl=curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);//打开错误类型，可以报错
    struct curl_httppost *formpost = NULL;
    struct curl_httppost *lastptr  = NULL;
    curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "file", CURLFORM_FILE, filename, CURLFORM_END);
    curl_easy_setopt(curl,CURLOPT_URL,url);
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, get_info_from_body);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, info);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}
// 获取fid和url
//不使用域名：
//curl -X POST http://localhost:93333/dir/assign
//使用域名：curl -X POST http://latermarch.xyz/getfid   
//curl -X PUT -F file=@picpath the_url/fid
void getinfo(WEED_INFO *info)
{
    //取fid号
    CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl=curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);//打开错误类型，可以报错
    curl_easy_setopt(curl,CURLOPT_URL,"http://latermarch.club/getfid");
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_INFILESIZE, 0);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, get_info_from_body);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, info);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);//不发送socket数据
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    // printf("%s\n", info->fid);
    // printf("%s\n", info->publicUrl);

}
void handlesql(string  sql,void *info,int flag)
{

    string tempUrl=(string)"http://latermarch.club";
    string url=tempUrl+sql;
    // cout<<url.c_str()<<endl;
    CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl=curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);//打开错误类型，可以报错
    
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl,CURLOPT_URL,url.c_str());//string转 char *
   // curl_easy_setopt(curl, CURLOPT_INFILESIZE, 0);
    if (flag==1)
    {
        WEED_INFO *userdata=(WEED_INFO *)info;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, get_info_from_body);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, userdata);
    }
    else
    {
        FILE *userdata =(FILE *)info;// fopen("temp.txt", "wb");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, userdata);
    }

    // curl_easy_setopt(curl, CURLOPT_WRITEDATA, userdata);
    // curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);//不发送socket数据
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}

void uploadfile(char * filename)
{
    string username="zhangzuoyun";
    WEED_INFO *info=(WEED_INFO *)malloc(sizeof(WEED_INFO));
    memset(info,0,sizeof(WEED_INFO));
    getinfo(info);
    if(info->fid)
        upload_part(filename,info);
    if(!info->size)
    {
        cout<<"failed to upload picture"<<endl;
        return;
    }
    //if(upload成功) //判断是否上传成功
    // printf("publicUrl:%s  fid:%s  name:%s  size:%s\n", info->publicUrl,info->fid,info->name,info->size);
    //操作数据库
    // char * fid="1,3fe622a7b5";
    string sql= (string)"/handlesql?param=insert into fileinfo(fid,publicurl,filename,size,username) values ('"+(string)info->fid+"','"+ (string)info->publicUrl + "','"+(string)info->name+"','"+ (string)info->size+"','"+(string)username +"');";
       //idea  1 把所有域名地址都放入到info中去，2再在info中加入username  3.返回数据，非json怎么接收？
    handlesql(sql,info,1);
    char *result=info->result;

    free(info->fid);
    free(info->publicUrl);
    free(info->name);
    free(info->size);
    free(info->result);
    free(info);
    // cout<<result<<strlen(result)<<endl;
    if(result[0]=='0')
    {
        cout<<"the picture upload success"<<endl;
    }
    else
    {
        cout<<result<<endl;
    }
    
}
//1 显示所有（filename url/fid time uesr） ,按时间排序  select * from fileinfo
//2 按用户显示    按时间排序
//
void listpicturls()
{
    long lSize;
    char * buffer;
    size_t result;
    map<int,FileInfo>info_map;
    string sql= (string)"/getinfo?param=select concat(publicurl,'/',fid) AS URL,filename,size,username from fileinfo;";
    FILE *info = fopen("temp.txt", "wb+");
    handlesql(sql,info,0);
//1读取文本
 /* 获取文件大小 */  
    fseek (info , 0 , SEEK_END);  
    lSize = ftell (info);  
    rewind (info);
    buffer=(char *)malloc(sizeof(char)*lSize);
    if (buffer == NULL)  
    {  
        fputs ("Memory error",stderr);   
        exit (2);  
    }
    result = fread (buffer,1,lSize,info);  
    if (result != lSize)  
    {  
        fputs ("Reading error",stderr);  
        exit (3);  
    } 
    // printf("%s",buffer);
//2转换成json
    cJSON *json= cJSON_Parse(buffer);
    // char *buf=cJSON_Print(json);
    // printf("data:%s\n",buf);
//3将json截开成一条条，并存入到struct中
    // int num=cJSON_GetArraySize(json);
    // cout<<num<<endl;
    // free(buf);
    cJSON *tnode,*item;

    char * stemp;
    size_t len;
    FileInfo *fileinfo;
    cJSON_ArrayForEach(tnode,json)//相当于for循环
    {

        if(tnode->type == cJSON_Object)
        {

            // printf("int forEach: vale:%s\n",cJSON_Print(tnode));
            if(cJSON_HasObjectItem(tnode,"URL"))
            {
                item=cJSON_GetObjectItem(tnode,"URL");
                stemp=cJSON_Print(item);//分配了内存空间的
                fileinfo->url= stemp;
                cout<<fileinfo->url;
                
                
            }

            // if(cJSON_HasObjectItem(json,"username"))
            // {
            //     item=cJSON_GetObjectItem(json,"username");
            //     stemp=cJSON_Print(item);
            //     len=strlen(stemp);
            //     s_context->name=(char *)malloc(sizeof(char)*len-2);
            //     memcpy(s_context->name,stemp+1,len-2);//为了去掉引号而已
            // }

            // if(cJSON_HasObjectItem(json,"size"))
            // {
            //     item=cJSON_GetObjectItem(json,"size");
            //     stemp=cJSON_Print(item);
            //     len=strlen(stemp);
            //     s_context->size=(char *)malloc(sizeof(char)*len);
            //     memcpy(s_context->size,stemp,len);//没得引号去
            // }
            //  if(cJSON_HasObjectItem(json,"size"))
            // {
            //     item=cJSON_GetObjectItem(json,"size");
            //     stemp=cJSON_Print(item);
            //     len=strlen(stemp);
            //     s_context->size=(char *)malloc(sizeof(char)*len);
            //     memcpy(s_context->size,stemp,len);//没得引号去
            // }


        }
        else
        {
            printf("node's type is not cJSON_Object\n");
        }

    }
    cJSON_Delete(json);
    fclose(info);
}

//curl -X DELETE curl/fid
int deletefile(char * url)//删除文件
{
    //删除文件
    //删除数据库
    // curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    /*
    //清缓存
    CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl=curl_easy_init();
    curl_easy_setopt(curl,CURLOPT_URL,url);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, stream);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);//不发送socket数据
    curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    fclose(stream);
    // printf("containers: %s\n",details);
    return 1;//判断函数
     */
}

int main()
{
    //打开文件失败，测试路径是否存在 
    // 功能测试1 上传
    // uploadfile((char *)"keyboard.png");
    // 功能测试2 显示列表
    listpicturls();
    /*
    string sql="http://latermarch.xyz/handlesql?param=insert into fileinfo(fid,publicurl,filename,size,username) values ('2,7704afb406','118.24.3.132:8080','keyboard.png','395659','zhangzuoyun');";
    WEED_INFO *info=(WEED_INFO *)malloc(sizeof(WEED_INFO));
    memset(info,0,sizeof(WEED_INFO));
    writesql(sql,info);
    cout<<info->result<<endl;
    */
    return 0;
}


//问题1 如何识别错误？执行后没上传从哪里排查？地址问题？还是图片路径问题？还是文件格式问题  