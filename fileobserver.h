#ifndef FILEOBSERVER_H
#define FILEOBSERVER_H

#include <QList>

#include "fileinfo.h"
#include "iFileObserver.h"


class FileObserver : public IFileObserver {
public:
    FileObserver() = default;
    FileObserver(const QString &path);
    ~FileObserver() override = default;

    bool add(const QString &path) override;
    bool remove(const QString &path) override;

    void run() override;

private:
    QList<FileInfo> m_files;
};

#endif // FILEOBSERVER_H
