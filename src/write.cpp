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
    
    float data1 = 1.1;
    float data2 = 2.2;
    float data3 = 3.3;
    float data4 = 4.4;
    float data5 = 5.5;
    float data6 = 6.6;

    sm->write(&data1, 1, 0);
    sm->write(&data2, 1, 4);
    sm->write(&data3, 1, 8);
    sm->write(&data4, 1, 12);
    sm->write(&data5, 1, 16);
    sm->write(&data6, 1, 20);

    sm->disconnect();
    delete sm;
    return 0;
}
