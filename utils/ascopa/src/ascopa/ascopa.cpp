#include <ascopa/ascopa.h>
#include <ascopa/ascoparegistry.h>

#include <mutex>
#include <thread>

AscopaWorker::AscopaWorker(const std::string& name)
    :m_name(name)
    ,m_isRunning(false)
    ,m_doNotProcessRemainingCalls(false)
    ,m_thread(nullptr)
{
    AscopaRegistry::registerWorker(m_name,this);
}

AscopaWorker::~AscopaWorker()
{
    if(m_thread){
        workerShutdown(true);
    }
    AscopaRegistry::unregisterWorker(m_name);
}

void AscopaWorker::workerStartup()
{
    m_thread = new std::thread([&]() -> void { this->threadRun(); });
    auto handle = m_thread->native_handle();
    pthread_setname_np(handle,m_name.c_str());
}

void AscopaWorker::workerShutdown(bool cancelRemainingIncommingCalls)
{
    m_isRunning = false;
    if(m_thread){ // startup was called and thread is running
        m_thread->join();
        delete m_thread;
        m_thread = nullptr;
    }
}

void AscopaWorker::asyncCall(const std::string& CallToWorkerWithName, std::function<void()> func)
{
    AscopaAsyncCall ac;
    ac.func = func;
    AscopaRegistry::enqueueCall(CallToWorkerWithName,ac);
}

std::string AscopaWorker::getWorkerName(){
    return m_name;
}

void AscopaWorker::enqueue(AscopaAsyncCall& ac)
{
    const std::lock_guard<std::recursive_mutex> lock(AscopaRegistry::m_queueLock);
    m_callQueue.push_back(ac);
}


void AscopaWorker::threadRun(void){
    m_isRunning = true;
    while(m_isRunning){

        Workstep();

        while( m_callQueue.empty() == false ){
            if(m_doNotProcessRemainingCalls == true){
                break;
            }
            AscopaAsyncCall acall;
            bool hasCall = false;
            {
                const std::lock_guard<std::recursive_mutex> lock(AscopaRegistry::m_queueLock);
                hasCall = !m_callQueue.empty();
                if(hasCall){
                    acall = m_callQueue.front();
                    m_callQueue.pop_front();
                }
            }
            if(hasCall){
                if(acall.func){ // callable function is present
                    // execute function in this worker-thread while m_queueLock is NOT pulled
                    acall.func();
                }
            }
        }
    }
    // thread is shutting down
    {
        const std::lock_guard<std::recursive_mutex> lock(AscopaRegistry::m_queueLock);
        m_callQueue.clear();
    }
}
