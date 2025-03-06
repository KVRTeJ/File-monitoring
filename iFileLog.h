#ifndef IFILELOG_H
#define IFILELOG_H

#include <QObject>

class IFileLog : QObject {
public slots:
    virtual ~IFileLog() = default;
    void fileExist(qint64 size);
    void fileChanged(qint64 size);
    void fileNotExist();
};

#endif // ILOG_H
