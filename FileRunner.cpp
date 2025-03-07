#include <thread>

#include "FileRunner.h"

void FileRunner::run() {
    for(;;) {

        m_loopFunction();

        std::this_thread::sleep_for(m_delay);
    }
}
