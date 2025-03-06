#ifndef IFILEOBSERVER_H
#define IFILEOBSERVER_H

#include <QString>

class IFileObserver {
public:
    virtual ~IFileObserver() = default;

    virtual bool add(const QString &path) = 0;
    virtual bool remove(const QString &path) = 0;

    virtual void run() = 0;
};

#endif // IFILEOBSERVER_H
