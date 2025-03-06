#ifndef IFILELOG_H
#define IFILELOG_H

#include <QObject>

class IFileLog : QObject {
    Q_OBJECT
public:
    virtual ~IFileLog() = default;
public slots:
    virtual void fileExist(const QString &path, qint64 size) = 0;
    virtual void fileChanged(const QString &path, qint64 size) = 0;
    virtual void fileNotExist(const QString &path) = 0;
};

#endif // IFILELOG_H
