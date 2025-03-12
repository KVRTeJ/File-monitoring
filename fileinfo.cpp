#include "fileinfo.h"

#include <QDebug>

FileInfo::FileInfo(const QString &path)
    : m_path(path)
{
    m_fileInfoCatcher.setFile(m_path);
}

bool FileInfo::setPath(const QString &path) {
    if(m_path == path) {
        return false;
    }

    m_path = path;
    m_fileInfoCatcher.setFile(m_path);

    update();

    return true;
}

bool FileInfo::isExist() const {
    return (m_condition == Condition::FILE_EXIST || m_condition == Condition::FILE_CHANGED);
}

bool FileInfo::update() {
    m_fileInfoCatcher.refresh();

    if(isExist()) {
        if(m_fileInfoCatcher.exists()) {
            if(m_size == m_fileInfoCatcher.size())
                return false;

            m_size = m_fileInfoCatcher.size();
            m_condition = Condition::FILE_CHANGED;
            return true;
        } else {
            m_size = 0;
            m_condition = Condition::FILE_NOT_EXIST;
            return true;
        }
    } else {
        if(m_fileInfoCatcher.exists()) {
            m_size = m_fileInfoCatcher.size();
            m_condition = Condition::FILE_EXIST;
            return true;
        }

        return false;
    }

    return false;
}
