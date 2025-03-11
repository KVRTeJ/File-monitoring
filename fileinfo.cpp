#include <iostream>

#include "fileinfo.h"

FileInfo::FileInfo(const QString &path)
    : m_path(path)
{}

bool FileInfo::setPath(const QString &path) {
    if(m_path == path) {
        return false;
    }

    m_path = path;

    update();

    return true;
}
