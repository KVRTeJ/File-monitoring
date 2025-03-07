#ifndef IRUNNER_H
#define IRUNNER_H

#include <chrono>
#include <functional>

class IRunner {
public:
    virtual ~IRunner() = default;

    virtual std::chrono::milliseconds getDelay() const = 0;
    virtual void setDelay(std::chrono::milliseconds delay) = 0;

    virtual void setLoopFunction(std::function<void()> loopFunction) = 0;
    virtual std::function<void()> getLoopFunction() const = 0;

    virtual void run() = 0;
};

#endif // IRUNNER_H
