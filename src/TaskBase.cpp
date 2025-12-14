
#include "TaskBase.hpp"

void TaskBase::start(const char* name, uint32_t stackSize, UBaseType_t priority, BaseType_t core) {
    xTaskCreatePinnedToCore(&TaskBase::taskEntryPoint, name, stackSize, this, priority, &handle, core);
    return;
}

void TaskBase::taskEntryPoint(void* param) {
    auto* task = static_cast<TaskBase*>(param);
    task->run();
    vTaskDelete(nullptr);

    return;
}
