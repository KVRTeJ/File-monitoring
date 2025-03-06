#include <iostream>

#include "fileinfo.h"

int main() {

    FileInfo foo("test");

    std::cout << foo.getPath().toStdString() << std::endl;
    foo.setPath("test2");
    std::cout << foo.getPath().toStdString() << std::endl;

    return 0;
}
