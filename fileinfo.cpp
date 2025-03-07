#include <iostream>

#include "fileinfo.h"

FileInfo::FileInfo(const QString &path, qint64 size, bool isExist)
    : m_path(path)
    , m_size(size)
    , m_isExist(isExist)
{

}

bool FileInfo::setPath(const QString &path) {
    if(m_path == path) {
        return false;
    }

    m_path = path;

    return true;
}

bool FileInfo::setSize(qint64 size) {
    if(m_size == size) {
        return false;
    }

    m_size = size;

    return true;
}

bool FileInfo::setExist(bool isExist) {
    if(m_isExist == isExist) {
        return false;
    }

    m_isExist = isExist;

    return true;
}
