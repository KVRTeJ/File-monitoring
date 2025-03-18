#include <thread>
#include <chrono>

#include <QCoreApplication>

#include "fileobserver.h"
#include "consolefilelog.h"

#include <iostream>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

#ifdef _WIN32
    QString path = "C:\\Users\\temp\\test.txt";
    QString path2 = "C:\\Users\\temp\\test2.txt";
#elif __APPLE__
    QString path = "/Users/dmitriy/test.md";
    QString path2 = "/Users/dmitriy/test2.md";
#endif

    ConsoleFileLog cns;
    FileObserver& observer = FileObserver::Instance();
    observer.setLogger(&cns);

    observer.add(path);
    observer.add(path2);

    for(;;) {
        observer.check();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return a.exec();
}
