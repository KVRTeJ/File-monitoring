#include <iostream>

#include "consolefilelog.h"

void ConsoleFileLog::fileExist(const QString &path, const qint64 size) {
    std::cout << "File " << path.toStdString() << " exists and it's size is " << size << std::endl;
}

void ConsoleFileLog::fileChanged(const QString &path, const qint64 size) {
    std::cout << "File " << path.toStdString() << " changed size to " << size << std::endl;
}

void ConsoleFileLog::fileNotExist(const QString &path) {
    std::cout << "File " << path.toStdString() << " does not exist" << std::endl;
}
