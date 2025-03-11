#ifndef FILEINFO_H
#define FILEINFO_H

#include <QFileInfo>

#include "iFileInfo.h"

class FileInfo : public IFileInfo {
public:
    FileInfo(const QString &path = "");
    ~FileInfo() override = default;

    QString getPath() const override {return m_path;}
    qint64 getSize() const  override {return m_size;}
    Condition getCondition() const override {return m_condition;}

    bool setPath(const QString &path) override;

    bool isExist() const override;

    bool update() override;

private:
    QString m_path = "";
    qint64 m_size = 0;
    Condition m_condition = NONE;

    QFileInfo m_newFileInfo;
};

#endif // FILEINFO_H
