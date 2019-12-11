#include <string>
#include <iostream>
#include <fstream>

void    OutputString(const std::string& msg,
                     std::ostream& out_stream) {
    out_stream<<msg<<std::endl;
}

int     main() {
    std::ofstream ofile("SayHello.txt");
    OutputString("Hello World", std::cout);
    OutputString("Hello World", ofile);

    return 0;
}
