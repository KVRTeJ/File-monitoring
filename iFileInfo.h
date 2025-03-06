#ifndef IFILEINFO_H
#define IFILEINFO_H

#include <QString>

class IFileInfo {
public:
    virtual ~IFileInfo() = default;

    virtual QString getPath() const = 0;
    virtual qint64 getSize() const = 0;

    virtual bool isExist() const = 0;

    virtual void setPath(QString path) = 0;
};

#endif // IFILEINFO_H
