#include <thread>
#include <chrono>

#include <QCoreApplication>

#include "fileobserver.h"
#include "consolefilelog.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

#ifdef _WIN32
    QString path = "C:\\Users\\dmitriy.filimonov\\tmp\\test.txt";
    QString path2 = "C:\\Users\\dmitriy.filimonov\\tmp\\test2.txt";
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

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return a.exec();
}
