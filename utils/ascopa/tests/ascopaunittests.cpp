#include <ascopaunittests.h>
#include <ascopa/ascopa.h>
#include <Log/log.h>

#include <thread>

//       Component A                                             Component B (m_x,m_y)
//           |                                                       |
//        threadRun                                                  |
//           |->Workstep                                             |
//           | ->asyncCall ( b->receive(..) ) -------->  queue of B  |
//           |                                                       |
//           |                                                     threadRun..( queue front)
//           |                                                       |->receive(x,y){
//                                                                         m_x = x
//                                                                         m_y = y
//           |                                                       |
//           |                                                       |-> Workstep
//

class ComponentInterface
{
public:
    virtual void receivePosition(int64_t x, int64_t y, std::string greetings) = 0;
};

class Component : public AscopaWorker, public ComponentInterface
{
public:
    Component(std::string name)
        :AscopaWorker(name)
        ,m_x(0)
        ,m_y(0)
        ,m_otherComp(nullptr)
    {};
    virtual ~Component(){};

    void setOtherComp(ComponentInterface* otherComp){
        m_otherComp = otherComp;
    }

    // called from outside the component
    // but its executed in this thread
    virtual void receivePosition(int64_t x, int64_t y, std::string msg) override{
        m_x = x;
        m_y = y;
        mbos::log::D("ascopa","receivePosition executed in %s msg=%s", getWorkerName().c_str(), msg.c_str());

        if(getWorkerName() == "B"){
            std::string msgreturn = std::string(" Thank You from ") + getWorkerName();
            asyncCall("A", [this,msgreturn]{ m_otherComp->receivePosition(100,100,msgreturn ); } );
        }
    }

    virtual void Workstep(){
        mbos::log::D("ascopa","Workstep running of %s" , getWorkerName().c_str());

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        if(getWorkerName() == "A"){
            std::string msg = std::string(" greetings from ") + getWorkerName();
            asyncCall("B", [this,msg]{ m_otherComp->receivePosition(99,99,msg ); } );
        }
    };


    int64_t m_x, m_y;
private:
    ComponentInterface* m_otherComp;

};



void ASCOPAUnitTests::SimpleUnitTest()
{
    Component A("A");
    Component B("B");

    A.setOtherComp(&B);
    B.setOtherComp(&A);

    A.workerStartup();
    B.workerStartup();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    B.workerShutdown(false);
    A.workerShutdown(false);
    CHECK(99, B.m_x);
    CHECK(100, A.m_x);
}


void ASCOPAUnitTests::CallNonexistent()
{
    // case 1
    {
        Component A("A");
        A.setOtherComp(nullptr);
        A.workerStartup(); // A will try to call B but B does not exist

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        A.workerShutdown(true);
    }

    // case 2:
    {
        Component* A = new Component("A");
        Component* B = new Component("B");

        A->setOtherComp(B);
        B->setOtherComp(A);

        A->workerStartup();
        B->workerStartup();
        // delete B while A is still trying to send messages
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        //B->workerShutdown(true);
        delete B;

        mbos::log::D("ascopa","B deleted");
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        A->workerShutdown(true);
        delete A;
    }
}

