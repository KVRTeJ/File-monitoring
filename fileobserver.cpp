#include <iostream>
#include <chrono>
#include <thread>

#include <QFileInfo>
#include <QTextCodec>

#include "fileobserver.h"

FileObserver::FileObserver(const QString &path) {
    m_files.push_back(FileInfo(path));
}

bool FileObserver::add(const QString &path) {
    m_files.push_back(FileInfo(path));
}

bool FileObserver::remove(const QString &path) {
    return false;
}

void FileObserver::run() {
    QFileInfo currentFileInfo;

    for(;;) {
        for(auto it = m_files.begin(); it != m_files.end(); ++it) {
            currentFileInfo.setFile(it->getPath());
            it->setExist(currentFileInfo.exists());
            it->setSize(currentFileInfo.size());
            currentFileInfo.refresh();

            if(it->isExist()) {
                if(it->setExist(currentFileInfo.exists())) {

                } else if(it->setSize(currentFileInfo.size())) {
                    std::cout << "File " << it->getPath().toStdString() << " changed size to " << it->getSize() << std::endl; //TODO: to signal
                } else {
                    std::cout << "File " << it->getPath().toStdString() << " exists and it's size is " << it->getSize() << std::endl; //TODO: to signal
                }
            } else {
                std::cout << "File " << it->getPath().toStdString() << " does not exist" << std::endl; //TODO: to signal
                it->setExist(currentFileInfo.exists());
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
}
