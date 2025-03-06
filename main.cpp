#include <iostream>

#include "fileobserver.h"

int main() {
    QString path = "C:\\Users\\dmitriy.filimonov\\tmp\\test.txt";
    QString path2 = "C:\\Users\\dmitriy.filimonov\\tmp\\test2.txt";
    FileObserver foo;

    foo.add(path);
    foo.add(path2);
    foo.run();
    return 0;
}
