#include <chrono>
#include <thread>

#include "fileobserver.h"

FileObserver::FileObserver(IFileLog *logger) {
    setLogger(logger);
}

void FileObserver::setLogger(IFileLog *logger) {
    if(!logger)
        m_logger = nullptr;

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

void FileObserver::run() {
    QFileInfo currentFileInfo;

    for(;;) {
        _listLoop(currentFileInfo);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void FileObserver::_listLoop(QFileInfo &currentFileInfo) {
    for(auto it = m_files.begin(); it != m_files.end(); ++it) {
        currentFileInfo.setFile(it->getPath());
        it->setExist(currentFileInfo.exists());

        if(it->isExist()) {
            if(it->setSize(currentFileInfo.size())) {
                emit fileExist(it->getPath(), it->getSize());
            } else {
                emit fileChanged(it->getPath(), it->getSize());
            }
        } else {
            emit fileNotExist(it->getPath());
            it->setSize(0);
            it->setExist(currentFileInfo.exists());
        }
    }
}
