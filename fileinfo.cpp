#include <iostream>

#include "fileinfo.h"

FileInfo::FileInfo(QString path)
    : m_path(path)
{
    std::cout << "File Info started. Path - " << m_path.toStdString() << std::endl;
}
