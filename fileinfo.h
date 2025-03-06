#ifndef FILEINFO_H
#define FILEINFO_H

#include <QFileInfo>

#include "iFileInfo.h"

class FileInfo : public IFileInfo {
public:
    FileInfo(QString path = "");
    ~FileInfo() override = default;

    QString getPath() const override {return m_path;}
    qint64 getSize() const  override {return m_size;}

    bool isExist() const override {return m_isExist;}

    void setPath(QString path) override {m_path = path;}

private:
    QString m_path;
    qint64 m_size = 0;
    bool m_isExist = false;
};

#endif // FILEINFO_H
