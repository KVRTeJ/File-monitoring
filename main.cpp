#include <QCoreApplication>

#include "fileobserver.h"
#include "consolefilelog.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QString path = "C:\\Users\\dmitriy.filimonov\\tmp\\test.txt";
    QString path2 = "C:\\Users\\dmitriy.filimonov\\tmp\\test2.txt";

    ConsoleFileLog cns;
    FileObserver foo(&cns);

    foo.add(path);
    foo.add(path2);

    foo.run();

    return a.exec();
}
