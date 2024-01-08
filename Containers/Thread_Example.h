#ifndef THREAD_EXAMPLE_H
#define THREAD_EXAMPLE_H

#include "../Utils/ShMem.h"
#include "../Utils/ThreadBase.h"
#include <time.h>

namespace NLMT {

class Thread_Example: public ThreadBase
{
public:

    Thread_Example();
    virtual ~Thread_Example();
   
    virtual int run();

    virtual void stopActivity();
    virtual void startActivity(); 

    static void *start(void* param);
   	
protected:

    int is_running;
    
    int THREAD_ALIVE;

private:

    pthread_t thread;

    struct timespec tim, tim2, tim3, tim4;
    
    ShMem *shmem_example;
    
};
}
#endif 
