
#pragma once
#include "TaskBase.hpp"

class DemoTask : public TaskBase {
public:
    DemoTask();

protected:
    void run() override;

private:

    const size_t ssdDigits = 4;

};
