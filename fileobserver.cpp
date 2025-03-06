#include <iostream>
#include <chrono>
#include <thread>

#include <QFileInfo>
#include <QTextCodec>

#include "fileobserver.h"

FileObserver::FileObserver(QString path) {
    m_file.setPath(path);
}



void FileObserver::run() {
    QFileInfo currentFileInfo(m_file.getPath());
    m_file.setExist(currentFileInfo.exists());
    m_file.setSize(currentFileInfo.size());

    for(;;) {
        currentFileInfo.refresh();

        if(m_file.isExist()) {
            if(m_file.setExist(currentFileInfo.exists())) {

            } else if(m_file.setSize(currentFileInfo.size())) {
                std::cout << "File " << m_file.getPath().toStdString() << " changed size to " << m_file.getSize() << std::endl; //TODO: to signal
            } else {
                std::cout << "File " << m_file.getPath().toStdString() << " exists and it's size is " << m_file.getSize() << std::endl; //TODO: to signal
            }
        } else {
            std::cout << "File " << m_file.getPath().toStdString() << " does not exist" << std::endl; //TODO: to signal
            m_file.setExist(currentFileInfo.exists());
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
