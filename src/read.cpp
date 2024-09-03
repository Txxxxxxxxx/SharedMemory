#include "SharedMemory.hpp"
#include <cstring>
#include <unistd.h>

const char *FILE_PATH = ".";
const int key_num = 126;
const int len = 4 * 6; // 400 * sizeof(float)

char *mem; // 共享内存的起始地址
SharedMemory *sm;
int main()
{
    try{
        sm = new SharedMemory(FILE_PATH, len, key_num);
        mem = (char*)sm->connect();
    }catch(const std::runtime_error& e)
    {
        std::cerr << "Caught an error: " << e.what() << '\n';
        return 0;
    }
    
    
    float data1, data2, data3, data4, data5, data6;

    sm->read(&data1, 1, 0);
    sm->read(&data2, 1, 4);
    sm->read(&data3, 1, 8);
    sm->read(&data4, 1, 12);
    sm->read(&data5, 1, 16);
    sm->read(&data6, 1, 20);

    printf("data1: %f\n", data1);
    printf("data2: %f\n", data2);
    printf("data3: %f\n", data3);
    printf("data4: %f\n", data4);
    printf("data5: %f\n", data5);
    printf("data6: %f\n", data6);
    
    sm->disconnect();
    delete sm;
    return 0;
}

