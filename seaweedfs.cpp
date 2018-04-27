#include "seaweedfs.h"
//curl -F file=@party2.jpg http://192.168.20.90:9333/submit
int seaweedfs::upload_single_file(char *fileName){

    //执行curl，是否成功？
    //失败则返回
    //执行数据库操作（上传一条数据）是否成功
    //失败也返回
    FILE *upstream=fopen(filename);
    CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl=curl_easy_init();
    curl_easy_setopt(curl,CURLOPT_URL,"http://192.168.20.90:9333/submit");

    //读取文件
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, upstream);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(upstream));

    curl_err=curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}