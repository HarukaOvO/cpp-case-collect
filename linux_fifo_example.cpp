#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <fcntl.h>

const std::string FIFO_NAME("./fifo_test");

void Writer(void) {
    std::cout<<"---- Writer ----"<<std::endl;
    srand(time(NULL));
    int fd = open(FIFO_NAME.c_str(), O_WRONLY);
    if((-1)!=fd) {
        std::cout<<"FIFO open."<<std::endl;
        std::vector<uint8_t> data(16, 0);
        int length;
        for(;;) {
            length = (rand()%16)+1;
            for(auto i=0; i<length; i=i+1) {
                data.at(i) = uint8_t(rand()%256);
            }
            if(write(fd, data.data(), length)!=length) {
                break;
            }
            for(auto i=0; i<length; i=i+1) {
                std::cout<<std::hex<<(int(data.at(i))&0xFF)<<", ";
            }
            std::cout<<std::endl;
        }
        close(fd);
        std::cout<<"FIFO close."<<std::endl;
    }
    std::cout<<"Terminated."<<std::endl;
}

void Reader(void) {
    std::cout<<"---- Reader ----"<<std::endl;
    int fd = open(FIFO_NAME.c_str(), O_RDONLY);
    if((-1)!=fd) {
        std::cout<<"FIFO open."<<std::endl;
        int length;
        uint8_t buffer[16];
        for(;;) {
            length = read(fd, buffer, sizeof(buffer)/sizeof(uint8_t));
            if(length>0) {
                std::vector<uint8_t> data(buffer, buffer+length);
                for(const auto& d: data) {
                    std::cout<<std::hex<<(int(d)&0xFF)<<", ";
                }
                std::cout<<std::endl;
            }
        }
        close(fd);
        std::cout<<"FIFO close."<<std::endl;
    }
    std::cout<<"Terminated."<<std::endl;
}

int main(int argc, char* argv[]) {
    if(argc<2) {
        return (-1);
    }
    if(strcmp(argv[1],"W")==0) {
        Writer();
    }
    if(strcmp(argv[1],"R")==0) {
        Reader();
    }
    return (0);
}
