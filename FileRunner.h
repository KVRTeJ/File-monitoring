#ifndef FILERUNNER_H
#define FILERUNNER_H

#include "iRunner.h"

class FileRunner : public IRunner {
public:
    ~FileRunner() override = default;

    std::chrono::milliseconds getDelay() const override {return m_delay;}
    void setDelay(std::chrono::milliseconds delay) override {m_delay = delay;}

    void setLoopFunction(std::function<void()> loopFunction) override {m_loopFunction = loopFunction;}
    std::function<void()> getLoopFunction() const override {return m_loopFunction;}

    void run() override;

private:
    std::chrono::milliseconds m_delay = std::chrono::milliseconds(100);
    std::function<void()> m_loopFunction;
};

#endif // FILERUNNER_H
