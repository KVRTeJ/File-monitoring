#include <QCoreApplication>

#include "fileobserver.h"
#include "consolefilelog.h"
#include "FileRunner.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QString path = "C:\\Users\\dmitriy.filimonov\\tmp\\test.txt";
    QString path2 = "C:\\Users\\dmitriy.filimonov\\tmp\\test2.txt";

    ConsoleFileLog cns;
    FileRunner runner;
    FileObserver& observer = FileObserver::Instance();
    observer.setLogger(&cns);
    observer.setRunner(&runner);

    observer.add(path);
    observer.add(path2);

    observer.run();

    return a.exec();
}
