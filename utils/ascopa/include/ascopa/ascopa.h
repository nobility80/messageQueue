#ifndef ASCOPA_H
#define ASCOPA_H

#include <atomic>
#include <deque>
#include <functional>
#include <string>

namespace std {
    class thread;
}

class AscopaAsyncCall;

// derive from this class and implement your Workstep function
class AscopaWorker
{
public:
    // call AscopaWorker constructor from this constructor and give the thread a unique name
    AscopaWorker(const std::string& name);
    virtual ~AscopaWorker();

    // call workerStartup from the outside (e.g. mainthread) to start the thread
    void workerStartup();

    // call workserShutdown from the outside (e.g. mainthread) to shutdown the thread
    void workerShutdown(bool cancelRemainingIncommingCalls);

    // thread name / worker name of this thread
    std::string getWorkerName();

protected:
    // use this to call to another interface
    // CallToWorkerWithName is the name of the other worker
    // func is a function that will be executed in the thread-context of "WorkerWithName"
    void asyncCall(const std::string& CallToWorkerWithName, std::function<void()> func);

    // overwrite this function it will be called infinitely while the worker is running
    virtual void Workstep() = 0;

private:
    void threadRun(void); // called by worker internally

    void enqueue(AscopaAsyncCall& ac); // called by registry internally

    std::string m_name;
    std::atomic_bool m_isRunning;
    std::atomic_bool m_doNotProcessRemainingCalls;
    std::thread* m_thread;
    typedef std::deque<AscopaAsyncCall> CallQueue;
    CallQueue m_callQueue;

    friend class AscopaRegistry;
};



#endif
