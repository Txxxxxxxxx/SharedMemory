#pragma once
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <iostream>
#include <cstring>

class SharedMemory
{
    public:
        SharedMemory(const char *filepath, int len, int key_num);
        ~SharedMemory();

        void* connect();
        void disconnect();
        void remove();
        template <typename T> void write(T *data, int len, int offset=0){
            memcpy(beginAddress + offset, data, len * sizeof(T));
        };
        template <typename T> void read(T *data, int len, int offset=0){
            memcpy(data, beginAddress + offset, len * sizeof(T));
        }


    private:
        key_t key;
        int shmid;
        // 起始地址 
        void *beginAddress;
};





/***********************************
 * @func ftok
 * @para pathname 一个已经存在的文件名
 * @para proj_id 一个整数，用于生成key值
 * @return 成功时，返回生成的key值
 *           失败时，返回-1，并设置相应的错误码
 *  
 * 只要pathname和proj_id一样，生成的key值就一样（不同应用程序也可以）
 *********************************/

/***********************************
* @func shmget
* @para key 共享内存的键值，用于标识共享内存段。通常使用 ftok 函数生成键值。
* @para size 共享内存段的大小，以字节为单位
* @para shmflg 共享内存的标志位，用于指定创建共享内存的权限和行为
* @return 成功时，返回共享内存的标识符（即共享内存的ID）
* 		  失败时，返回-1，并设置相应的错误码
* 
*********************************/

/***********************************
 * @func shmat
 * @para shmid 共享内存的标识符（即共享内存的ID）
 * @para shmaddr 指定共享内存连接到当前进程中的地址位置，通常设置为NULL，由系统自动分配
 * @para shmflg 共享内存的标志位，通常设置为0
 * @return 成功时，返回共享内存连接的地址
 *          失败时，返回-1，并设置相应的错误码
 *  
 * 该函数用于将共享内存连接到当前进程的地址空间中
 *********************************/

/***********************************
 * @func memcpy
 * @para dest 目标地址
 * @para src 源地址
 * @para n 复制的字节数
 * @return 返回目标地址
 *  
 * 该函数用于将源地址的n个字节复制到目标地址
 *********************************/

/***********************************
 * @func shmdt
 * @para shmaddr 共享内存连接的地址
 * @return 成功时，返回0
 *          失败时，返回-1，并设置相应的错误码
 *  
 * 该函数用于将共享内存从当前进程中分离
 *********************************/

