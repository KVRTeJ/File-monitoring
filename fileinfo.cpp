#include "fileinfo.h"

FileInfo::FileInfo(const QString &path)
    : m_path(path)
{
    m_newFileInfo.setFile(m_path);
}

bool FileInfo::setPath(const QString &path) {
    if(m_path == path) {
        return false;
    }

    m_path = path;
    m_newFileInfo.setFile(m_path);

    update();

    return true;
}

bool FileInfo::isExist() const {
    return (m_condition == Condition::FILE_EXIST || m_condition == Condition::FILE_CHANGED);
}

bool FileInfo::update() {
    m_newFileInfo.refresh();

    if(isExist()) {
        if(m_newFileInfo.exists()) {
            if(m_size == m_newFileInfo.size())
                return false;

            m_size = m_newFileInfo.size();
            m_condition = Condition::FILE_CHANGED;
            return true;
        } else {
            m_condition = Condition::FILE_NOT_EXIST;
            return true;
        }
    } else {
        if(m_newFileInfo.exists()) {
            m_condition = Condition::FILE_EXIST;
            return true;
        }

        return false;
    }

    return false;
}
