//#include <UnitTest/unittest.h>

class ASCOPAUnitTests : public commonplat::UnitTest
{
public:

    void SimpleUnitTest();
    void CallNonexistent();

    int runtest(){
        beginTest("AsCoPa Unit tests");
        testCase("SimpleUnitTest");               SimpleUnitTest();
        testCase("CallNonexistent");              CallNonexistent();
        return endTest();
    }
};
