#include "fileobserver.h"

FileObserver& FileObserver::Instance() {
    static FileObserver observer;
    return observer;
}

FileObserver::FileObserver(IFileLog *logger) {
    setLogger(logger);
}

void FileObserver::setLogger(IFileLog *logger) {
    if(!logger) {
        m_logger = nullptr;
        return;
    }

    m_logger = logger;
    connect(this, SIGNAL(fileExist(QString,qint64)), m_logger, SLOT(fileExist(QString,qint64)));
    connect(this, SIGNAL(fileChanged(QString,qint64)), m_logger, SLOT(fileChanged(QString,qint64)));
    connect(this, SIGNAL(fileNotExist(QString)), m_logger, SLOT(fileNotExist(QString)));
}

bool FileObserver::add(const QString &path) {
    for(auto it = m_files.begin(); it != m_files.end(); ++it) {
        if(it->getPath() == path)
            return false;
    }

    m_files.push_back(FileInfo(path));

    return true;
}

bool FileObserver::remove(const QString &path) {
    for(auto it = m_files.begin(); it != m_files.end(); ++it) {
        if(it->getPath() == path) {
            m_files.erase(it);
            return true;
        }
    }

    return false;
}

void FileObserver::check() {
    for(auto it = m_files.begin(); it != m_files.end(); ++it) {
        if(it->update()) {
            switch(it->getCondition()) {
            case Condition::FILE_NOT_EXIST:
                emit fileNotExist(it->getPath());
                break;
            case Condition::FILE_EXIST:
                emit fileExist(it->getPath(), it->getSize());
                break;
            case Condition::FILE_CHANGED:
                emit fileChanged(it->getPath(), it->getSize());
                break;
            default:
                break;
            }
        }
    }
}
