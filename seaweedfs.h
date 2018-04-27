#ifndef _SEAWEEDFS_H_
#define _SEAWEEDFS_H_


#include "usemysql.h"
#include "curl/curl.h"
#include "cJSON.h"

//管理方式 （只许目录方式上传，不准普通上传，一个目录对应一个用户，访问方式1：url/fid;2:url/dir/filename）

class seaweedfs{

private:

public:
    seaweedfs();  
    ~seaweedfs(); 
    //上传数据
    int upload_single_file(char *fileName);



    //表一 序号  名称  识别码  url  大小  所属目录 上传者 上传时间
    //表二 上传者名单管理
    //表三 上传目录管理

    //显示目录中的文件
    int list_dir_files(char *dirName);

};
#endif