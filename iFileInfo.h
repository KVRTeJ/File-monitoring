#ifndef IFILEINFO_H
#define IFILEINFO_H

#include <QString>

class IFileInfo {
public:
    virtual ~IFileInfo() = default;

    virtual QString getPath() const = 0;
    virtual qint64 getSize() const = 0;

    virtual bool isExist() const = 0;

    virtual bool setPath(const QString &path) = 0;
    virtual bool setSize(qint64 size) = 0;
    virtual bool setExist(bool isExist) = 0;
};

#endif // IFILEINFO_H
