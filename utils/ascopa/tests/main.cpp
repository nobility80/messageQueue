#include <log.h>
#include <ascopaunittests.h>
#include <ascopa/ascopa.h>

int main(void){
    mbos::log::SetLogOutput(false,true);
    ASCOPAUnitTests unittests;
    return unittests.runtest();
}
