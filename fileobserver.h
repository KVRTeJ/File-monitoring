#ifndef FILEOBSERVER_H
#define FILEOBSERVER_H

#include "fileinfo.h"
#include "iFileObserver.h"


class FileObserver : public IFileObserver {
public:
    FileObserver(QString path) {}
    ~FileObserver() override = default;

    bool add(const QString &path) override;
    bool remove(const QString &path) override;

    void run() override;


private:
    FileInfo m_file; //TODO: to list
};

#endif // FILEOBSERVER_H
