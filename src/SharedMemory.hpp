/*
    Author : Xia tian
    Description : 
        2024.9.21完成：
            1. 该类用于创建共享内存,实现进程间通信                  
            2. 该类提供了连接、断开、删除、读写等功能               
            3. 该类提供了模板函数，可以读写任意类型的数据          
        2024.9.23完成：   
            4. 该类提供了信号量，用于保护共享内存的读写             
            5. 该类提供了异常处理，当读写越界时，会抛出异常          
*/
#pragma once
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <semaphore.h>
#include <fcntl.h> 

class SharedMemory
{
    public:
        SharedMemory(const char *filepath, int len, int key_num);
        ~SharedMemory();

        void* connect();
        void disconnect();
        void remove();
        template <typename T> void write(T *data, int data_num, int offset=0){
            // 检查是否越界
            if(offset + data_num > memory_len){
                throw std::runtime_error("Out of memory range");
                return;
            }
            sem_wait(sem); // 加锁  
            memcpy(beginAddress + offset, data, data_num * sizeof(T));
            sem_post(sem); // 解锁
        };
        template <typename T> void read(T *data, int data_num, int offset=0){
            // 检查是否越界
            if(offset + data_num > memory_len){
                throw std::runtime_error("Out of memory range");
                return;
            }
            sem_wait(sem); // 加锁  
            memcpy(data, beginAddress + offset, data_num * sizeof(T));
            sem_post(sem); // 解锁
        }


    private:
        key_t key;
        int shmid;
        // 起始地址 
        void *beginAddress;
        // 共享内存的大小
        int memory_len;
        // 信号量， 用于保护共享内存的读写
        sem_t *sem;
};
