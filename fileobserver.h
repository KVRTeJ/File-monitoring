#ifndef FILEOBSERVER_H
#define FILEOBSERVER_H

#include <QList>

#include <QFileInfo>

#include "fileinfo.h"
#include "iFileObserver.h"

class FileObserver : public QObject, public IFileObserver {
    Q_OBJECT
public:
    static FileObserver& Instance();

    FileObserver(const FileObserver &other) = delete;
    IFileLog* getLogger() const override {return m_logger;}
    void setLogger(IFileLog *logger) override;

    bool add(const QString &path) override;
    bool remove(const QString &path) override;

    void check();

    FileObserver& operator = (const FileObserver &other) = delete;
 signals:
    void fileExist(const QString &path, qint64 size);
    void fileChanged(const QString &path, qint64 size);
    void fileNotExist(const QString &path);

private:
    FileObserver(IFileLog *logger = nullptr);
    ~FileObserver() override = default;

private:
    QList<FileInfo> m_files;
    IFileLog *m_logger = nullptr;
};

#endif // FILEOBSERVER_H
