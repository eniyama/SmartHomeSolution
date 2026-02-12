#include "SDV.h"
int fd = 0;
//int fd_frame = 0;
//int i = 1;
char buf[64] = {0,0};
unsigned int temp = 0;
static unsigned int mjb = 3;

SDV::SDV(QObject *parent) : QObject(parent)
{
    fd = open("/tmp/myfifo", O_RDONLY);
   // fd = open("/var/data/myfifo", O_RDONLY);
    if ( fd == -1) {
        perror("open");
        exit(1);
    }
   // fd = 1;
}
/*
unsigned int SDV::sendSpeed()
{
    temp = rand() % 100;
    return temp;
}
*/

unsigned int SDV::sendSpeed()
{
    if(mjb == 3) {
        read(fd, buf, 6);
        mjb=0;
    }
    mjb++;
    temp = static_cast<unsigned int>(buf[0]);//- 48;// - 48;
    //std::cout <<"string is "<<buf <<std::endl;
    //std::cout <<"value is "<<temp <<std::endl;
    if(temp < 100)
        return temp;
    else
        return 50;
}

unsigned int SDV::sendTemp()
{
    unsigned int temp_1 = static_cast<unsigned int>(buf[3]);
    //std::cout <<"value temprature iss is "<<temp_1 <<std::endl;
    //std::cout <<"value temp/4.0f iss is "<<(temp/4.0f) <<std::endl;
    if (temp_1 < 50)
        return temp_1;
    else
        return 30;
}

unsigned int SDV::sendFuel()
{
    unsigned int temp_2 = static_cast<unsigned int>(buf[2]);
    //std::cout <<"value fuel iss is "<<temp_2 <<std::endl;
    if (temp_2 < 100)
        return temp_2;
    else
        return 65;
}

unsigned int SDV::sendIcon()
{
    unsigned int temp_4 = static_cast<unsigned int>(buf[1]);
    //std::cout <<"value fuel iss is "<<temp_4 <<std::endl;
    return temp_4;
}

unsigned int SDV::sendDoor(){
    return static_cast<unsigned int>(buf[4]);
}
