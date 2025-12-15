#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class TaskBase {
public:

    virtual ~TaskBase() = default;

    void start(const char* name, uint32_t stackSize, UBaseType_t priority, BaseType_t core = tskNO_AFFINITY);

protected:
    virtual void run() = 0;

private:
    TaskHandle_t handle = nullptr;

    static void taskEntryPoint(void* param);
};
