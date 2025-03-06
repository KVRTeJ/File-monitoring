#include <QFileInfo>

#include <iostream>

#include "fileobserver.h"

FileObserver::FileObserver(QString path) {
    m_file.setPath(path);
}



void FileObserver::run() {
    QFileInfo currentFileInfo(m_file.getPath());
    m_file.setExist(currentFileInfo.exists());
    m_file.setSize(currentFileInfo.size());

    for(;;) {
        if(m_file.isExist()) {
            if(m_file.setSize(currentFileInfo.size())) {
                std::cout << "Изменен размер файла на: " << m_file.getSize() << std::endl; //TODO: to signal
            } else {
                std::cout << "Файл существует, его размер: " << m_file.getSize() << std::endl; //TODO: to signal
            }
        } else {
            std::cout << "Файл не существует" << std::endl; //TODO: to signal
            m_file.setExist(currentFileInfo.exists());
        }
    }
}
