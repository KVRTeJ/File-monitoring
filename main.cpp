#include <iostream>

#include "fileobserver.h"

int main() {
    QString path = "C:\\Users\\dmitriy.filimonov\\tmp\\test.txt";
    FileObserver foo(path);

    foo.run();
    return 0;
}
