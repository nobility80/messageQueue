#include <ascopa/ascopa.h>
#include <ascopa/ascoparegistry.h>

#include <map>
#include <mutex>
#include <string>

// initialise
std::recursive_mutex AscopaRegistry::m_queueLock;
std::map<std::string,AscopaWorker*> AscopaRegistry::m_registeredWorkers;


void AscopaRegistry::registerWorker(const std::string& name, AscopaWorker* worker){
    const std::lock_guard<std::recursive_mutex> lock(AscopaRegistry::m_queueLock);
    m_registeredWorkers[name] = worker;
}

void AscopaRegistry::unregisterWorker(const std::string& name){
    const std::lock_guard<std::recursive_mutex> lock(AscopaRegistry::m_queueLock);
    std::map<std::string,AscopaWorker*>::iterator it = m_registeredWorkers.find(name);
    if (it != m_registeredWorkers.end()) {
        m_registeredWorkers.erase(it);
    }
}

void AscopaRegistry::enqueueCall(const std::string& name, AscopaAsyncCall& call){
    const std::lock_guard<std::recursive_mutex> lock(AscopaRegistry::m_queueLock);
    if (m_registeredWorkers.find(name) != m_registeredWorkers.end()) {
        m_registeredWorkers[name]->enqueue(call);
    }
}
