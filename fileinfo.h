#ifndef FILEINFO_H
#define FILEINFO_H

#include "iFileInfo.h"

class FileInfo : public IFileInfo {
public:
    FileInfo(const QString &path = "");
    ~FileInfo() override = default;

    QString getPath() const override {return m_path;}
    qint64 getSize() const  override {return m_size;}
    Condition getCondition() const override {return Condition::NONE;}

    bool setPath(const QString &path) override;

    bool isExist() const override {return m_isExist;}

    bool update() override {return false;}

private:
    QString m_path = "";
    qint64 m_size = 0;
    bool m_isExist = false;
};

#endif // FILEINFO_H
