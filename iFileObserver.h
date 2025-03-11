#ifndef IFILEOBSERVER_H
#define IFILEOBSERVER_H

#include <QString>

#include "iFileLog.h"

class IFileObserver {
public:
    virtual ~IFileObserver() = default;

    virtual IFileLog* getLogger() const = 0;
    virtual void setLogger(IFileLog *logger) = 0;

    virtual bool add(const QString &path) = 0;
    virtual bool remove(const QString &path) = 0;

    virtual void check() = 0;
};

#endif // IFILEOBSERVER_H
