#ifndef FILEINFO_H
#define FILEINFO_H

#include "iFileInfo.h"

class FileInfo : public IFileInfo {
public:
    FileInfo(QString path = "", qint64 size = 0, bool isExist = false);
    ~FileInfo() override = default;

    QString getPath() const override {return m_path;}
    qint64 getSize() const  override {return m_size;}

    bool isExist() const override {return m_isExist;}

    bool setPath(QString path) override;
    bool setSize(qint64 size) override;
    bool setExist(bool isExist) override;

private:
    QString m_path = "";
    qint64 m_size = 0;
    bool m_isExist = false;
};

#endif // FILEINFO_H
