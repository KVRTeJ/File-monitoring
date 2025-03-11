#ifndef IFILEINFO_H
#define IFILEINFO_H

#include <QString>

enum Condition : short {
    NONE = -1,
    FILE_NOT_EXIST = 0,
    FILE_EXIST,
    FILE_CHANGED
};

class IFileInfo {
public:
    virtual ~IFileInfo() = default;

    virtual QString getPath() const = 0;
    virtual qint64 getSize() const = 0;
    virtual Condition getCondition() const = 0;

    virtual bool setPath(const QString &path) = 0;

    virtual bool isExist() const = 0;

    virtual bool update() = 0;
};

#endif // IFILEINFO_H
