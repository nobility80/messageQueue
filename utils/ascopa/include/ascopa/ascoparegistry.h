#ifndef ASCOPAREGISTRY_H
#define ASCOPAREGISTRY_H


#include <atomic>
#include <deque>
#include <functional>
#include <mutex>
#include <thread>
#include <map>

class AscopaWorker;

class AscopaAsyncCall
{
public:
    AscopaAsyncCall():func({}){}
    virtual ~AscopaAsyncCall(){}
    std::function<void()> func;
};


class AscopaRegistry
{
public:
    static void registerWorker(const std::string& name, AscopaWorker* worker);

    static void unregisterWorker(const std::string& name);

    static void enqueueCall(const std::string& name, AscopaAsyncCall& call);

    static std::recursive_mutex m_queueLock;

private:
    static std::map<std::string,AscopaWorker*> m_registeredWorkers;

};

#endif
