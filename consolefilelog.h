#ifndef CONSOLEFILELOG_H
#define CONSOLEFILELOG_H

#include "iFileLog.h"

class ConsoleFileLog :public IFileLog {
public:
    ConsoleFileLog() = default;
    ~ConsoleFileLog() override = default;

public slots:
    void fileExist(const QString &path, qint64 size) override;
    void fileChanged(const QString &path, qint64 size) override;
    void fileNotExist(const QString &path) override;
};

#endif // CONSOLEFILELOG_H
