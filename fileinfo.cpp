#include <iostream>

#include "fileinfo.h"

FileInfo::FileInfo(QString path)
    : m_path(path)
{

}

QString FileInfo::getPath() const {
    return m_path;
}

qint64 FileInfo::getSize() const {
    m_size = QFileInfo::size(m_path);
}

bool FileInfo::isExist() const ;

void FileInfo::setPath(QString path) ;
