#include "beatsaber-hook/shared/utils/utils.h"
#include "custom-types/shared/delegate.hpp"
#include "CustomTypes/Components/MainThreadScheduler.hpp"

DEFINE_TYPE(QuestUI, MainThreadScheduler);

std::vector<std::function<void()>> QuestUI::MainThreadScheduler::scheduledMethods;
std::mutex QuestUI::MainThreadScheduler::scheduledMethodsMutex;
//PersistentSingleton_1<HMMainThreadDispatcher*>::get_instance()->Enqueue(custom_types::MakeDelegate<System::Action*>((std::function<void()>)[=] { }));
void QuestUI::MainThreadScheduler::Update() {
    std::lock_guard<std::mutex> lock(scheduledMethodsMutex);
    if(scheduledMethods.size() > 0) {
        for(std::function<void()> method : scheduledMethods) {
            method();
        }
        scheduledMethods.clear();
    }
}